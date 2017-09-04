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

const QString RADIO_STYLE = R"(
QRadioButton{spacing:0px;}
QRadioButton::indicator{width:31px;height:24px;}
QRadioButton::indicator::unchecked{image:url(%1);}
QRadioButton::indicator::checked{image:url(%2);}
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
		connect(ui.labelUrl, &QLabel::linkActivated, [](const QString& url) {
			QDesktopServices::openUrl(QUrl(url));
		});
	}
	Ui::AboutDialog ui;

};

const QString TITLE_HEADER = "LightMagic TransCoder V1.0";
MainWidget::MainWidget(const QString& file)
{
	setAcceptDrops(true);
	setWindowTitle(TITLE_HEADER);

	QSettings settings("LightMagic", "TransCoder");
	QSize normalSize = settings.value("geo/size", QSize(1200, 800)).toSize();
	bool maxed = settings.value("geo/maxed").toBool();

	resize(normalSize);
	if (maxed)
	{
		showMaximized();
	}

	QStatusBar* statusBar = this->statusBar();
	statusBar->setStyleSheet(R"(
QStatusBar {
    background-color: rgb(83,83,83);
	color:rgb(255,255,255);
}
)");
	statusBar->showMessage(QString("x:0 y:0"));

	m_clipper = new Clipper;
	connect(m_clipper, &Clipper::mouseTracking, this, &MainWidget::onMouseTracking);
	connect(m_clipper, &Clipper::createElement, this, &MainWidget::createElement);

	connect(this, &MainWidget::zoomIn, m_clipper, &Clipper::zoomIn);
	connect(this, &MainWidget::zoomOut, m_clipper, &Clipper::zoomOut);

	QToolBar* toolBar = new QToolBar("tools");

	QPalette palette;
	palette.setColor(QPalette::Light, QColor(83, 83, 83));
	palette.setColor(QPalette::Midlight, QColor(83, 83, 83));
	palette.setColor(QPalette::Dark, QColor(83, 83, 83));
	palette.setColor(QPalette::Mid, QColor(83, 83, 83));
	palette.setColor(QPalette::Shadow, QColor(83, 83, 83));
	toolBar->setPalette(palette);

	toolBar->setStyleSheet(R"(QToolBar{background-color: rgb(83,83,83);}
QToolTip {
    border: 1px solid white;
    padding: 2px;
    border-radius: 3px;
    opacity: 200;
}
)");
	toolBar->setIconSize(QSize(31,24));
	addToolBar(Qt::LeftToolBarArea, toolBar);

	QRadioButton* selLine = new QRadioButton;
	selLine->setToolTip(tr("Guides Tool: Image positioning aid"));
	connect(selLine, &QRadioButton::toggled, m_clipper, &Clipper::setLineEnabled);
	selLine->setChecked(true);
	selLine->setStyleSheet(RADIO_STYLE.arg(":/arror_normal.png").arg(":/arror_pressed.png"));
	QRadioButton* selRect = new QRadioButton;
	selRect->setToolTip(tr("Rectangle Select Tool: Select a rectangular region"));
	connect(selRect, &QRadioButton::toggled, m_clipper, &Clipper::setRectEnabled);
	selRect->setStyleSheet(RADIO_STYLE.arg(":/rect_normal.png").arg(":/rect_pressed.png"));
	QButtonGroup* group = new QButtonGroup(this);
	group->addButton(selLine);
	group->addButton(selRect);

	toolBar->addWidget(selLine);
	toolBar->addWidget(selRect);

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
	QAction* pARatio = settingMenu->addAction(tr("Resolution"));
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

	QGroupBox* groupBox = new QGroupBox;
	QHBoxLayout* layout = new QHBoxLayout;
	groupBox->setLayout(layout);

	QSplitter* splitter = new QSplitter(Qt::Vertical);
	splitter->setStyleSheet("QSplitter{background-color: rgb(83, 83, 83);}");
	splitter->addWidget(m_clipper);
	splitter->addWidget(groupBox);
	splitter->handle(1)->setStyleSheet("background-color: rgb(22, 22, 22);");
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


MainWidget::~MainWidget()
{
}

void MainWidget::addToRecentFiles(const QString& file)
{
	QSettings setting("LightMagic", "TransCoder");
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

	QDomElement settings = root.firstChildElement("settings");
	QDomElement areas = root.firstChildElement("areas");
	
	if (areas.isNull() || settings.isNull())
	{
		return false;
	}

	m_clipper->setData(areas);

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

class WidgetRatio : public QDialog
{
public:
	WidgetRatio(QWidget* parent = nullptr):QDialog(parent)
	{
		ui.setupUi(this);
	}
	Ui::Dialog ui;
};

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

	QString fileName = QFileDialog::getOpenFileName(this, tr("Open project"), QStandardPaths::writableLocation(QStandardPaths::DocumentsLocation), "Lmcoder(*.Lmcoder)");
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
		QString savefile = QFileDialog::getSaveFileName(this, tr("Save file name"), m_filename, "Lmcoder(*.Lmcoder)");
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
	QDomElement areas = m_doc.createElement("areas");
	root.appendChild(areas);
	QDomElement settings = m_doc.createElement("settings");
	root.appendChild(settings);
	QDomElement input = m_doc.createElement("input");
	settings.appendChild(input);
	QDomElement framerate = m_doc.createElement("framerate");
	settings.appendChild(framerate);
	QDomElement audio = m_doc.createElement("audio");
	settings.appendChild(audio);
	QDomElement timeRange = m_doc.createElement("timeRange");
	settings.appendChild(timeRange);
	QDomElement threads = m_doc.createElement("threads");
	threads.setAttribute("value", std::thread::hardware_concurrency() * 3 >> 2);
	settings.appendChild(threads);
	QDomElement vcodec = m_doc.createElement("vcodec");
	settings.appendChild(vcodec);
	QDomElement pixfmt = m_doc.createElement("pixfmt");
	settings.appendChild(pixfmt);
	QDomElement preset = m_doc.createElement("preset");
	settings.appendChild(preset);
	QDomElement gop = m_doc.createElement("gop");
	gop.setAttribute("value", 25);
	settings.appendChild(gop);

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

QDomElement MainWidget::createElement(const QString& name)
{
	QDomElement ret = m_doc.createElement(name);
	Q_ASSERT(!ret.isNull());
	return ret;
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
	QSettings settings("LightMagic", "TransCoder");
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
	QSettings setting("LightMagic", "TransCoder");
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
		file = QString("new %1.Lmcoder").arg(index);
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
		QSettings settings("LightMagic", "TransCoder");
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
			if (0 == QString("Lmcoder").compare(QFileInfo(file).suffix(), Qt::CaseInsensitive))
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
			if (0 == QString("Lmcoder").compare(QFileInfo(file).suffix(), Qt::CaseInsensitive))
			{
				openFile(file);
				break;
			}
		}
	}
}
