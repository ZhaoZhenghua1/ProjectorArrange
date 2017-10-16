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
#include <QPainter>
#include <QPixmapCache>
#include <QStringBuilder>
#include <QToolButton>
#include "ui_about.h"
#include "TableView/TreeView.h"
#include "TableView/ItemModel.h"
#include "TableView/AllItemModel.h"
#include "TableView/ProjectorDelegate.h"
#include "RadioToolButton.h"

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

const QString TITLE_HEADER = "LightMagic Projection Sketch2D V1.0";
const QString StatusBarStyle = R"(
QStatusBar {
    background-color: rgb(83,83,83);
	color:rgb(255,255,255);
})";

void registerMap(const QString& map)
{
	QPixmap mappath = ":/" + map + ".png";
	QPixmap hoverPath = ":/hover.png";
	QPixmap pressedPath = ":/pressed.png";

	QPixmap *normalMap = new QPixmap(50, 40);
	normalMap->fill(QColor(83, 83, 83));
	QPainter painter(normalMap);
	painter.drawPixmap(normalMap->rect().adjusted(9, 4, -9, -4), mappath, mappath.rect());
	normalMap->save(map + "_normal.png");

	QPixmap *hoverMap = new QPixmap(50, 40);
	QLinearGradient hoverGradient;
	hoverGradient.setColorAt(0, QColor(117, 117, 117));
	hoverGradient.setColorAt(1, QColor(98, 98, 98));
	QBrush brush(hoverGradient); 
	QPainter painterHover(hoverMap);
	painterHover.fillRect(hoverMap->rect(), brush);
	painterHover.drawPixmap(hoverMap->rect().adjusted(9, 4, -9, -4), mappath, mappath.rect());
	painterHover.drawPixmap(hoverMap->rect(), hoverPath, hoverPath.rect());
	hoverMap->save(map + "_hover.png");
	
	QPixmap *pressedMap = new QPixmap(50, 40);
	{
		QLinearGradient pressedGradient;
		pressedGradient.setColorAt(0, QColor(63, 63, 63));
		pressedGradient.setColorAt(1, QColor(55, 55, 55));
		QBrush brush(pressedGradient);
		QPainter painterPressed(pressedMap);
		painterPressed.fillRect(pressedMap->rect(), brush);
		painterPressed.drawPixmap(pressedMap->rect().adjusted(9, 4, -9, -4), mappath, mappath.rect());
		painterPressed.drawPixmap(pressedMap->rect(), pressedPath, pressedPath.rect());
		pressedMap->save(map + "_pressed.png");
	}

}

MainWidget::MainWidget(const QString& file)
{
// 	registerMap("brightness");
// 	registerMap("vertical");
 //	registerMap("collineation");


	setAcceptDrops(true);
	setWindowTitle(TITLE_HEADER);
	initMenu();

	QSettings settings("LightMagic", "Lmps2d");
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
	connect(this, &MainWidget::showEffect, m_clipper, &Clipper::showEffect);
	
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
	m_itemView->setColumnWidth(0, 180);
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
	{"Select Mode", eMove, ":/arror_normal.png", ":/arror_hover.png" , ":/arror_pressed.png" }
	,{"800x600",e800x600, ":/800x600_normal.png" , ":/800x600_hover.png" , ":/800x600_pressed.png" }
	,{"1024x768",e1024x768, ":/1024x768_normal.png" , ":/1024x768_hover.png" , ":/1024x768_pressed.png" }
	,{"1280x720",e1280x720 , ":/1280x720_normal.png" , ":/1280x720_hover.png" , ":/1280x720_pressed.png" }
	,{"1280x800",e1280x800 , ":/1280x800_normal.png" , ":/1280x800_hover.png" , ":/1280x800_pressed.png" }
	,{"1920x1080",e1920x1080 , ":/1920x1080_normal.png" , ":/1920x1080_hover.png" , ":/1920x1080_pressed.png" }
	,{"1920x1200",e1920x1200 , ":/1920x1200_normal.png" , ":/1920x1200_hover.png" , ":/1920x1200_pressed.png" }
	,{"2048x1080",e2048x1080 , ":/2048x1080_normal.png" , ":/2048x1080_hover.png" , ":/2048x1080_pressed.png" }
	,{"3840x2160",e3840x2160 , ":/3840x2160_normal.png" , ":/3840x2160_hover.png" , ":/3840x2160_pressed.png" }
	,{"3840x2400",e3840x2400 , ":/3840x2400_normal.png" , ":/3840x2400_hover.png" , ":/3840x2400_pressed.png" }
	,{"4096x2160",e4096x2160 , ":/4096x2160_normal.png" , ":/4096x2160_hover.png" , ":/4096x2160_pressed.png" }
	,{"Self Defining", eSelfDef , ":/selfdef_normal.png" , ":/selfdef_hover.png" , ":/selfdef_pressed.png" }
//	,{"Tape measure", eTape , ":/tape_normal.png" , ":/tape_hover.png" , ":/tape_pressed.png" } 
};

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
	QToolBar* toolBarPutStyle = new QToolBar("Put Style");
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
	attachBtn->setStyleSheet(RADIO_STYLE.arg(":/collineation_normal.png").arg(":/collineation_hover.png").arg(":/collineation_pressed.png"));
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
	connect(groupRatio, SIGNAL(buttonToggled(int , bool )), this, SLOT(onSetRation(int, bool)));

	RadioToolButton* btnTape = new RadioToolButton;
	m_radioToolBtn = btnTape;
	toolBarRatio->addWidget(btnTape);
	groupRatio->addButton(btnTape->radioButton(), eTape);
	connect(btnTape, &RadioToolButton::rtBtnToggled, [groupRatio, this]() {
		onSetRation(groupRatio->id(m_radioToolBtn->radioButton()), true);
	});

	QToolBar* toolBarEffect = new QToolBar("Distribution Diagram");
	addToolBar(Qt::TopToolBarArea, toolBarEffect);
	initToolBar(toolBarEffect);
	QRadioButton* brightness = new QRadioButton;
	brightness->setToolTip(tr("Brightness distribution diagram"));
	brightness->setStyleSheet(RADIO_STYLE.arg(":/brightness_normal.png").arg(":/brightness_hover.png").arg(":/brightness_pressed.png"));
	brightness->setAutoExclusive(false);
	toolBarEffect->addWidget(brightness);
	connect(brightness, SIGNAL(toggled(bool)), this, SLOT(onShowEffect(bool)));
	m_effectBtns[0] = brightness;

	QRadioButton* pixdensity = new QRadioButton;
	pixdensity->setToolTip(tr("Pix density distribution diagram"));
	pixdensity->setStyleSheet(RADIO_STYLE.arg(":/pixdensity_normal.png").arg(":/pixdensity_hover.png").arg(":/pixdensity_pressed.png"));
	pixdensity->setAutoExclusive(false);
	toolBarEffect->addWidget(pixdensity);
	m_effectBtns[1] = pixdensity;
	connect(pixdensity, SIGNAL(toggled(bool)), this, SLOT(onShowEffect(bool)));
	
}

void MainWidget::onSetOrientation(int id)
{
	m_clipper->setProRotate((id == Qt::Vertical) ? 90 : 0);
}

void MainWidget::onSetRation(int id, bool checked)
{
	if (!checked)
	{
		return;
	}
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
		switch (m_radioToolBtn->tapeMode())
		{
		case RadioToolButton::ePix:
			m_clipper->setProRatio(QSize(0, 1));
			break;
		case  RadioToolButton::eDistance:
			m_clipper->setProRatio(QSize(1, 0));
			break;
		}
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

void MainWidget::onShowEffect(bool checked)
{
	QObject* sender = this->sender();
	if (checked)
	{
		bool firstChecked = sender == m_effectBtns[0];
		m_effectBtns[0]->setChecked(firstChecked);
		m_effectBtns[1]->setChecked(!firstChecked);
	}
	int type = (m_effectBtns[0]->isChecked() ? 1 : 0) | (m_effectBtns[1]->isChecked() ? 2 : 0);
	showEffect(type);
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
//	QAction* pAViewHelp = helpMenu->addAction(tr("View Help"));
//	connect(pAViewHelp, &QAction::triggered, this, &MainWidget::onViewHelp);

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
	QSettings setting("LightMagic", "Lmps2d");
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

	this->setData(root);
	m_clipper->setData(areas);
//	m_globalModel->setDomData(areas);

	return true;
}

void MainWidget::setData(const QDomElement& data)
{
	QString pixmappath = data.attribute("pixmap");
	m_clipper->setPixmap(pixmappath);
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
		QDomElement root = m_doc.firstChildElement("root");
		root.setAttribute("pixmap", fileName);
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

	QString fileName = QFileDialog::getOpenFileName(this, tr("Open project"), QStandardPaths::writableLocation(QStandardPaths::DocumentsLocation), "Lmps2d(*.Lmps2d)");
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
		QString savefile = QFileDialog::getSaveFileName(this, tr("Save file name"), m_filename, "Lmps2d(*.Lmps2d)");
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

	m_emptyDoc.setContent(m_doc.toString());

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
	QDesktopServices::openUrl(QUrl::fromLocalFile(QCoreApplication::applicationDirPath() + "/Help/LightMagic ProjectorV1.0 Manual.pdf"));
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
	QSettings settings("LightMagic", "Lmps2d");
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
	QSettings setting("LightMagic", "Lmps2d");
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
		file = QString("new %1.Lmps2d").arg(index);
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
		QSettings settings("LightMagic", "Lmps2d");
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
			if (0 == QString("Lmps2d").compare(QFileInfo(file).suffix(), Qt::CaseInsensitive))
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
			if (0 == QString("Lmps2d").compare(QFileInfo(file).suffix(), Qt::CaseInsensitive))
			{
				openFile(file);
				break;
			}
		}
	}
}
