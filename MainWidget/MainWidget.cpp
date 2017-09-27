#include "MainWidget.h"
#include "Clipper.h"
#include <QToolBar>
#include <QRadioButton>
#include <QButtonGroup>
#include <QMenuBar>
#include <QFileDialog>
#include <QStandardPaths>
#include <QStatusBar>
#include <QSplitter>
#include <QGroupBox>
#include <QHBoxLayout>
#include <QFile>
#include <QMessageBox>
#include <QTextStream>
#include <QSettings>
#include <QDesktopServices>
#include <QMimeData>
#include "ui_ratio.h"
#include <thread>
#include "ui_about.h"
#include "TableView/TreeView.h"
#include "TableView/ItemModel.h"
#include "TableView/AllItemModel.h"
#include "TableView/ProjectorDelegate.h"

const QString RADIO_STYLE = R"(
QRadioButton{spacing:0px;}
QRadioButton::indicator{width:50px;height:40px;}
QRadioButton::indicator::unchecked{image:url(%1);}
QRadioButton::indicator::unchecked:hover{image:url(%2);}
QRadioButton::indicator::checked{image:url(%3);}
)";

const QString MENU_STYLE = R"(
QMenu {
    background-color: #535353; /* sets background of the menu */
	color: #ffffff;
    border: 1px solid black;
}
QMenu:disabled{
	color:  rgb(150,150,150);
}
QMenu::item {
    /* sets background of menu item. set this to something non-transparent
        if you want menu color and menu item color to be different */
    background-color: transparent;
}

QMenu::item:selected { /* when user selects item using mouse or keyboard */
    background-color: #3a3a3a;
}
)";

class AboutDialog : public QDialog
{
public:
	AboutDialog(QWidget* parent = nullptr) :QDialog(parent)
	{
		ui.setupUi(this);
	}
	Ui::AboutDialog ui;

};

class WidgetRatio : public QDialog
{
public:
	WidgetRatio(QWidget* parent = nullptr) :QDialog(parent)
	{
		ui.setupUi(this);
	}
	Ui::Dialog ui;
};

const QString TITLE_HEADER = "LightMagic Projector V1.0";
const QString StatusBarStyle = R"(
QStatusBar {
    background-color: rgb(83,83,83);
	color:rgb(255,255,255);
})";

MainWidget::MainWidget(const QString& file)
{
	setAcceptDrops(true);
	setWindowTitle(TITLE_HEADER);
	initMenu();

	QSettings settings("LightMagic", "Projector");
	QSize normalSize = settings.value("geo/size", QSize(1200, 800)).toSize();
	bool maxed = settings.value("geo/maxed").toBool();

	resize(normalSize);
	if (maxed)
	{
		showMaximized();
	}

	QStatusBar* statusBar = this->statusBar();
	statusBar->setStyleSheet(StatusBarStyle);
	statusBar->showMessage(QString("x:0 y:0"));

	m_clipper = new Clipper;
	initToolBarItem();
	connect(m_clipper, &Clipper::mouseTracking, this, &MainWidget::onMouseTracking);
	connect(m_clipper, &Clipper::domDocument, this, &MainWidget::domDocument);

	connect(this, &MainWidget::zoomIn, m_clipper, &Clipper::zoomIn);
	connect(this, &MainWidget::zoomOut, m_clipper, &Clipper::zoomOut);
	connect(this, &MainWidget::setSnap, m_clipper, &Clipper::setSnap);

	QGroupBox* groupBox1 = new QGroupBox;
	QHBoxLayout* layout1 = new QHBoxLayout;
	groupBox1->setLayout(layout1);
	m_itemView = new TreeView;
	m_itemModel = new ItemModel;
	connect(m_clipper, &Clipper::dataChanged, m_itemModel, &ItemModel::dataChanged);
	connect(m_clipper, &Clipper::setCurrentItemData, m_itemModel, &ItemModel::setCurrentItemData);
	
	connect(m_clipper, &Clipper::setCurrentItemData, m_itemView, &TreeView::onSetData);
	connect(m_itemModel, &ItemModel::currentItemDataEdited, m_clipper, &Clipper::currentItemDataEdited);
	m_itemView->setModel(m_itemModel);
	m_itemView->setItemDelegate(new TreeviewDelegate);
	layout1->addWidget(m_itemView);

// 	QGroupBox* groupBox2 = new QGroupBox;
// 	QHBoxLayout* layout2 = new QHBoxLayout;
// 	groupBox2->setLayout(layout2);
// 	m_globalView = new TreeView;
// 	m_globalModel = new AllItemModel;
// 	connect(m_clipper, &Clipper::dataChanged, m_globalModel, &AllItemModel::dataChanged);
// 	connect(m_globalModel, &AllItemModel::allItemDataEdited, m_clipper, &Clipper::allItemDataEdited);
// 	m_globalView->setModel(m_globalModel);
// 	m_globalView->setItemDelegate(new AllItemDelegate);
// 	layout2->addWidget(m_globalView);

	QSplitter* splitter = new QSplitter(Qt::Horizontal);
	splitter->setStyleSheet("QSplitter{background-color: rgb(83, 83, 83);}");
	
	splitter->addWidget(groupBox1);
	splitter->addWidget(m_clipper);
//	splitter->addWidget(groupBox2);
	
	splitter->handle(1)->setStyleSheet("background-color: rgb(22, 22, 22);");
//	splitter->handle(2)->setStyleSheet("background-color: rgb(22, 22, 22);");
	setCentralWidget(splitter);

	setStyleSheet(R"(background-color: rgb(83, 83, 83);color:rgb(255,255,255);)");

	QString fileOpen = file;
	if (!file.isEmpty())
	{
		openFile(file);
	}
	else
	{
		onNew();
	}
}
enum ECREATE_FLAG
{
	eMove,
	e800x600,
	e1024x768,
	e1280x720,
	e1280x800,
	e1920x1080,
	e1920x1200,
	e2048x1080,
	e3840x2160,
	e3840x2400,
	e4096x2160,
	eSelfDef,
	eTape,
};

const QList<std::tuple<QString, int, QString, QString, QString> > RATIOS = {
	{"Guides Tool: Image positioning aid", eMove, ":/arror_normal.png", ":/arror_hover.png" , ":/arror_pressed.png" },
	{"800x600",e800x600, ":/800x600_normal.png" , ":/800x600_hover.png" , ":/800x600_pressed.png" },
	{"1024x768",e1024x768, ":/1024x768_normal.png" , ":/1024x768_hover.png" , ":/1024x768_pressed.png" },
	{"1280x720",e1280x720 , ":/1280x720_normal.png" , ":/1280x720_hover.png" , ":/1280x720_pressed.png" },
	{"1280x800",e1280x800 , ":/1280x800_normal.png" , ":/1280x800_hover.png" , ":/1280x800_pressed.png" },
	{"1920x1080",e1920x1080 , ":/1920x1080_normal.png" , ":/1920x1080_hover.png" , ":/1920x1080_pressed.png" },
	{"1920x1200",e1920x1200 , ":/1920x1200_normal.png" , ":/1920x1200_hover.png" , ":/1920x1200_pressed.png" },
	{"2048x1080",e2048x1080 , ":/2048x1080_normal.png" , ":/2048x1080_hover.png" , ":/2048x1080_pressed.png" },
	{"3840x2160",e3840x2160 , ":/3840x2160_normal.png" , ":/3840x2160_hover.png" , ":/3840x2160_pressed.png" },
	{"3840x2400",e3840x2400 , ":/3840x2400_normal.png" , ":/3840x2400_hover.png" , ":/3840x2400_pressed.png" },
	{"4096x2160",e4096x2160 , ":/4096x2160_normal.png" , ":/4096x2160_hover.png" , ":/4096x2160_pressed.png" },
	{"Self Defining", eSelfDef , ":/selfdef_normal.png" , ":/selfdef_hover.png" , ":/selfdef_pressed.png" },
	{"Tape measure", eTape , ":/tape_normal.png" , ":/tape_hover.png" , ":/tape_pressed.png" } };

QList<std::tuple<QString, int, QString, QString, QString> > PUT_STYLES = {
	{ "Horizontal", Qt::Horizontal , ":/horizontal_normal.png" , ":/horizontal_hover.png" , ":/horizontal_pressed.png"},
	{ "Vertical" , Qt::Vertical , ":/vertical_normal.png" , ":/vertical_hover.png" , ":/vertical_pressed.png" } };

const QString TOOLBAR_STYLE = R"(QToolBar{background-color: rgb(83,83,83);}
QToolTip {
    border: 1px solid white;
    padding: 2px;
    border-radius: 3px;
    opacity: 200;
})";
void initToolBar(QToolBar* toolBar)
{
	QPalette palette;
	palette.setColor(QPalette::Light, QColor(83, 83, 83));
	palette.setColor(QPalette::Midlight, QColor(83, 83, 83));
	palette.setColor(QPalette::Dark, QColor(83, 83, 83));
	palette.setColor(QPalette::Mid, QColor(83, 83, 83));
	palette.setColor(QPalette::Shadow, QColor(83, 83, 83));
	toolBar->setPalette(palette);
	toolBar->setStyleSheet(TOOLBAR_STYLE);
	//toolBar->setIconSize(QSize(50, 40));
}
void MainWidget::initToolBarItem()
{
	QToolBar* toolBarPutStyle = new QToolBar("Put");
	addToolBar(Qt::TopToolBarArea, toolBarPutStyle);
	initToolBar(toolBarPutStyle);
	QButtonGroup* groupPut = new QButtonGroup(this);
	for (const std::tuple<QString, int, QString, QString, QString>& elem : PUT_STYLES)
	{
		QRadioButton* radioBtn = new QRadioButton;
		radioBtn->setToolTip(std::get<0>(elem));
		radioBtn->setStyleSheet(RADIO_STYLE.arg(std::get<2>(elem)).arg(std::get<3>(elem)).arg(std::get<4>(elem)));
		groupPut->addButton(radioBtn, std::get<1>(elem));
		toolBarPutStyle->addWidget(radioBtn);
	}
	groupPut->buttons().first()->setChecked(true);
	connect(groupPut, SIGNAL(buttonClicked(int)), this, SLOT(onSetOrientation(int)));

	QRadioButton* attachBtn = new QRadioButton;
	attachBtn->setToolTip(tr("Snap"));
	attachBtn->setStyleSheet(RADIO_STYLE.arg(":/snap_normal.png").arg(":/snap_hover.png").arg(":/snap_pressed.png"));
	toolBarPutStyle->addWidget(attachBtn);
	connect(attachBtn, &QRadioButton::toggled, this, &MainWidget::setSnap);
	attachBtn->setChecked(true);

	QToolBar* toolBarRatio = new QToolBar("Ratios");
	addToolBar(Qt::TopToolBarArea, toolBarRatio);
	initToolBar(toolBarRatio);
	
	QButtonGroup* groupRatio = new QButtonGroup(this);
	for (const std::tuple<QString, int, QString, QString, QString>& elem : RATIOS)
	{
		QRadioButton* radioBtn = new QRadioButton;
		radioBtn->setToolTip(std::get<0>(elem));
		radioBtn->setStyleSheet(RADIO_STYLE.arg(std::get<2>(elem)).arg(std::get<3>(elem)).arg(std::get<4>(elem)));
		groupRatio->addButton(radioBtn, std::get<1>(elem));
		toolBarRatio->addWidget(radioBtn);
	}
	groupRatio->buttons().first()->setChecked(true);
	connect(groupRatio, SIGNAL(buttonClicked(int)), this, SLOT(onSetRation(int)));
}

void MainWidget::onSetOrientation(int id)
{
	m_clipper->setProRotate((id == Qt::Vertical) ? 90 : 0);
}

void MainWidget::onSetRation(int id)
{
	if (id == eMove)
	{
		m_clipper->setProRatio(QSize());
	}
	else if (id == eSelfDef)
	{
		WidgetRatio wr(this);
		QSize ratio = m_clipper->projectorRatio();
		wr.setWindowTitle(tr("Custom Projector Resolution Setting"));
		wr.ui.label->setText(tr("Projector Resolution:"));
		wr.ui.spinBoxx->setValue(ratio.width());
		wr.ui.spinBoxy->setValue(ratio.height());
		if (QDialog::Accepted == wr.exec())
		{
			m_clipper->setProRatio(QSize(wr.ui.spinBoxx->value(), wr.ui.spinBoxy->value()));
		}
		else
		{
			if (QButtonGroup* p = qobject_cast<QButtonGroup*>(sender()))
			{
				p->buttons().first()->setChecked(true);
			}
			m_clipper->setProRatio(QSize());
		}
	}
	else if (id == eTape)
	{
		m_clipper->setProRatio(QSize(1,0));
	}
	else
	{
		for (const std::tuple<QString, int, QString, QString, QString>& elem : RATIOS)
		{
			if (id == std::get<1>(elem))
			{
				const QString& qsratio = std::get<0>(elem);
				QStringList ratio = qsratio.split('x');
				m_clipper->setProRatio(QSize(ratio[0].toInt(), ratio[1].toInt()));
			}
		}
	}
}

void MainWidget::initMenu()
{
	menuBar()->setStyleSheet(R"(
QMenuBar {
    background-color: rgb(83,83,83);
	color: rgb(255,255,255);
}
QMenuBar:disabled{
	color:  rgb(150,150,150);
}
QMenuBar::item {
    spacing: 3px; /* spacing between menu bar items */
    padding: 4px 8px;
    background: transparent;
    border-radius: 3px;
}

QMenuBar::item:selected { /* when selected using mouse or keyboard */
    background: #6f6f6f;
}

QMenuBar::item:pressed {
    background: #363636;
}
)");

	QMenu* fileMenu = new QMenu(tr("File"));
	fileMenu->setStyleSheet(MENU_STYLE);
	menuBar()->addMenu(fileMenu);

	QAction* pANew = fileMenu->addAction(tr("&New"));
	connect(pANew, &QAction::triggered, this, &MainWidget::onNew);
	pANew->setShortcut(QKeySequence::New);

	QAction* pAOpen = fileMenu->addAction(tr("&Open"));
	connect(pAOpen, &QAction::triggered, this, &MainWidget::onOpen);
	pAOpen->setShortcut(QKeySequence::Open);

	QAction* pAClose = fileMenu->addAction(tr("&Close"));
	connect(pAClose, &QAction::triggered, this, &MainWidget::onClose);
	pAClose->setShortcut(QKeySequence::Close);

	QAction* pASave = fileMenu->addAction(tr("&Save"));
	connect(pASave, &QAction::triggered, this, &MainWidget::onSave);
	pASave->setShortcut(QKeySequence::Save);

	m_recentMenu = fileMenu->addMenu(tr("Recent Files"));
	addRecent();

	QMenu* settingMenu = new QMenu(tr("Settings"));
	settingMenu->setStyleSheet(MENU_STYLE);
	menuBar()->addMenu(settingMenu);
	QAction* pARatio = settingMenu->addAction(tr("Screen Size"));
	connect(pARatio, &QAction::triggered, this, &MainWidget::onSetRatio);
	QAction* pAPixmap = settingMenu->addAction(tr("Image"));
	connect(pAPixmap, &QAction::triggered, this, &MainWidget::onSetPixmap);


	QMenu* helpMenu = new QMenu(tr("Help"));
	menuBar()->addMenu(helpMenu);
	helpMenu->setStyleSheet(MENU_STYLE);
	QAction* pAAbout = helpMenu->addAction(tr("About"));
	connect(pAAbout, &QAction::triggered, this, &MainWidget::onAbout);
	QAction* pAViewHelp = helpMenu->addAction(tr("View Help"));
	connect(pAViewHelp, &QAction::triggered, this, &MainWidget::onViewHelp);

	QAction* pAZoonIn = new QAction(menuBar());
	menuBar()->addAction(pAZoonIn);
	pAZoonIn->setShortcut(QKeySequence::ZoomIn);
	connect(pAZoonIn, &QAction::triggered, this, &MainWidget::zoomIn);

	QAction* pAZoomOut = new QAction(menuBar());
	menuBar()->addAction(pAZoomOut);
	pAZoomOut->setShortcut(QKeySequence::ZoomOut);
	connect(pAZoomOut, &QAction::triggered, this, &MainWidget::zoomOut);
}

MainWidget::~MainWidget()
{
}

void MainWidget::addToRecentFiles(const QString& file)
{
	QSettings setting("LightMagic", "Projector");
	QString recent = setting.value("recent").toString();
	QStringList recents = recent.split(';');
	recents.removeAll("");
	recents.removeDuplicates();
	while (recents.size() >= 10)
	{
		recents.removeLast();
	}
	recents.push_front(file);
	recents.removeDuplicates();
	recent = recents.join(';');
	setting.setValue("recent", recent);
	addRecent();
}

bool MainWidget::dispatchData()  
{
	QDomElement root = m_doc.firstChildElement("root");

	QDomElement areas = root.firstChildElement("projectors");
	
	if (areas.isNull())
	{
		return false;
	}

	m_clipper->setData(areas);
//	m_globalModel->setDomData(areas);

	return true;
}

void MainWidget::openFile(const QString& file)
{
	QDomDocument doc = open(file);
	if (!doc.isNull())
	{
		if (!close())
		{
			return;
		}
	}
		
	m_doc = doc;
	m_emptyDoc.setContent(m_doc.toString());

	if (!dispatchData())
	{
		return;
	}

	m_filename = file;

	setWindowTitle(TITLE_HEADER + " - " + file);

	addToRecentFiles(file);
}

QDomDocument MainWidget::open(const QString& fileName)
{
	QFile file(fileName);
	if (!file.open(QIODevice::ReadOnly))
	{
		errorFile(fileName);
		QMessageBox::information(this, "Error", "Can not open file "+ fileName + ",it will be removed from the recent files!");
		return QDomDocument();
	}

	QString errorMsg;
	int errorLine, errorColumn;
	QDomDocument doc;
	if (!doc.setContent(&file, &errorMsg, &errorLine, &errorColumn))
	{
		errorFile(fileName);
		QMessageBox::information(this, "Error", errorMsg + QString(" errorLine:%1, errorColumn:%2").arg(errorLine).arg(errorColumn));
		return QDomDocument();
	}

	return doc;
}

void MainWidget::onSetPixmap()
{
	QString fileName = QFileDialog::getOpenFileName(this, tr("Set reference picture"), QStandardPaths::writableLocation(QStandardPaths::PicturesLocation), "Images (*.png *.xpm *.jpg);");
	if (!fileName.isEmpty())
	{
		m_clipper->setPixmap(fileName);
	}
}

void MainWidget::onSetRatio()
{
	WidgetRatio wr(this);
	WidgetRatio* pwr = &wr;
	QSize ratio = m_clipper->ratio();
	pwr->ui.spinBoxx->setValue(ratio.width());
	pwr->ui.spinBoxy->setValue(ratio.height());
	if (QDialog::Accepted == pwr->exec())
	{
		m_clipper->setRatio(pwr->ui.spinBoxx->value(), pwr->ui.spinBoxy->value());
	}
}

void MainWidget::onMouseTracking(const QPoint& pos)
{
	QStatusBar* statusBar = this->statusBar();
	statusBar->showMessage(QString("X:%1 Y:%2").arg(pos.x()).arg(pos.y()));
}

void MainWidget::onOpen()
{
	if (!close())
	{
		return;
	}

	QString fileName = QFileDialog::getOpenFileName(this, tr("Open project"), QStandardPaths::writableLocation(QStandardPaths::DocumentsLocation), "Lmpro(*.Lmpro)");
	openFile(fileName);
}

void MainWidget::onClose()
{
	QMainWindow::close();
}

void MainWidget::onSave()
{
	if (!QFile(m_filename).exists())
	{
		QString savefile = QFileDialog::getSaveFileName(this, tr("Save file name"), m_filename, "Lmpro(*.Lmpro)");
		if (savefile.isEmpty())
		{
			return;
		}
		m_filename = savefile;
	}
	
	QFile file(m_filename);

	if (file.open(QIODevice::WriteOnly))
	{
		const int IndentSize = 4;
		QTextStream out(&file);
		m_doc.save(out, IndentSize);
		file.close();
	}

	setWindowTitle(TITLE_HEADER + " - " + m_filename);

	addToRecentFiles(m_filename);
}

void MainWidget::onNew()
{
	if (!close())
	{
		return ;
	}
	m_filename = getAvailableFileName();

	m_doc.clear();

	QDomElement root = m_doc.createElement("root");
	m_doc.appendChild(root);
	QDomElement areas = m_doc.createElement("projectors");
	root.appendChild(areas);

	dispatchData();

	m_emptyDoc.setContent(m_doc.toString());

	setWindowTitle(TITLE_HEADER + " - " + m_filename);
}

void MainWidget::onAbout()
{
	AboutDialog a(this);
	a.exec();
}

void MainWidget::onViewHelp()
{
	QDesktopServices::openUrl(QUrl::fromLocalFile(QCoreApplication::applicationDirPath() + "/Help/LightMagic TrancoderV1.0 Manual.pdf"));
}

QDomDocument MainWidget::domDocument()
{
	return m_doc;
}

void MainWidget::onOpenRecent()
{
	if (QAction* action = qobject_cast<QAction*>(sender()))
	{
		openFile(action->text());
	}
}

void MainWidget::addRecent()
{
	m_recentMenu->clear();
	QSettings settings("LightMagic", "Projector");
	QString recent = settings.value("recent").toString();
	QStringList recentFiles = recent.split(';');
	for (QString file : recentFiles)
	{
		if (!file.isEmpty())
		{
			QAction * action = m_recentMenu->addAction(file);
			connect(action, &QAction::triggered, this, &MainWidget::onOpenRecent);
		}
	}
}

bool operator==(const QDomDocument& l, const QDomDocument& r)
{
	return l.toString() == r.toString();
}

bool MainWidget::close()
{
	if (m_filename.isEmpty() || m_doc == m_emptyDoc)
	{
		return true;
	}

	QString old = m_emptyDoc.toString();
	QString neW = m_doc.toString();

	QFile file(m_filename);
	if (file.exists())
	{
		if (!file.open(QIODevice::ReadOnly))
		{
			return true;
		}

		QDomDocument doc;
		doc.setContent(&file);
		if (m_doc == doc)
		{
			return true;
		}
	}	

	QMessageBox::StandardButton btn = QMessageBox::question(this, tr("Save changes?"), tr("Save changes to \'") + m_filename + tr("\' before closing?"), QMessageBox::StandardButtons(QMessageBox::Yes | QMessageBox::No | QMessageBox::Cancel));
	if (btn == QMessageBox::Yes)
	{
		onSave();
		return true;
	}
	else if (btn == QMessageBox::No)
	{
		return true;
	}
	else if (btn == QMessageBox::Cancel)
	{
		return false;
	}

	return false;
}

//if file is error, remove the recent file 
void MainWidget::errorFile(const QString& file)
{
	QSettings setting("LightMagic", "Projector");
	QString recent = setting.value("recent").toString();
	QStringList recents = recent.split(';');
	recents.removeAll("");
	recents.removeDuplicates();
	recents.removeAll(file);
	recent = recents.join(';');
	setting.setValue("recent", recent);

	addRecent();
}

QString MainWidget::getAvailableFileName() const
{
	int index = 1;
	QString file;
	while (true)
	{
		file = QString("new %1.Lmpro").arg(index);
		if (!QFile(file).exists())
		{
			break;
		}
		++index;
	}
	return file;
}


void MainWidget::closeEvent(QCloseEvent *event)
{
	if (close())
	{
		QSettings settings("LightMagic", "Projector");
		settings.setValue("geo/size", normalGeometry().size());
		settings.setValue("geo/maxed", isMaximized());
		return Base::closeEvent(event);
	}
	else
	{
		event->ignore();
	}
}

void MainWidget::dragEnterEvent(QDragEnterEvent *event)
{
	const QMimeData *mimeData = event->mimeData();
	QStringList formats = mimeData->formats();
	QList<QUrl> urlList = mimeData->urls();
	bool valid = false;
	//判断拖动的文件中是否有有效的媒体文件
	for (int i = 0; i < urlList.size(); ++i)
	{
		QString file = urlList.at(i).toLocalFile();
		if (!file.isEmpty())
		{
			if (0 == QString("Lmpro").compare(QFileInfo(file).suffix(), Qt::CaseInsensitive))
			{
				valid = true;
				break;
			}
		}
	}
	if (valid)
	{
		event->acceptProposedAction();
	}
	else
	{
		event->ignore();
	}
}

void MainWidget::dragLeaveEvent(QDragLeaveEvent *event)
{
	event->accept();
}

void MainWidget::dragMoveEvent(QDragMoveEvent *event)
{
	event->acceptProposedAction();
}

void MainWidget::dropEvent(QDropEvent *event)
{
	QStringList fileLst;
	const QMimeData *mimeData = event->mimeData();
	QStringList formats = mimeData->formats();
	QList<QUrl> urlList = mimeData->urls();
	for (int i = 0; i < urlList.size(); ++i)
	{
		QString file = urlList.at(i).toLocalFile();
		if (!file.isEmpty())
		{
			if (0 == QString("Lmpro").compare(QFileInfo(file).suffix(), Qt::CaseInsensitive))
			{
				openFile(file);
				break;
			}
		}
	}
}
