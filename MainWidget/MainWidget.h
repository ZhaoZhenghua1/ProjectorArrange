#pragma once
#include <QMainWindow>
#include <QDomDocument>

class Clipper;
class TreeView;
class ItemModel;
class AllItemModel;
class QRadioButton;
class RadioToolButton;
class MainWidget : public QMainWindow
{
	typedef QMainWindow Base;
	Q_OBJECT
public:
	MainWidget(const QString& file);
	~MainWidget();

	void openFile(const QString& file);
	QDomDocument  open(const QString& file);
public slots:
	void onSetPixmap();
	void onSetRatio();
	void onMouseTracking(const QPoint& pos);
	void onOpen();
	void onClose();
	void onSave();
	void onNew();
	void onAbout();
	void onViewHelp();
	QDomDocument domDocument();
	void onOpenRecent();
signals:
	void zoomIn();
	void zoomOut();
	void setSnap(bool);
	void showEffect(int type);
private:
	void addRecent();
	bool close();
	void errorFile(const QString& file);
	QString getAvailableFileName()const;
	void addToRecentFiles(const QString& file);
	bool dispatchData();
	void initToolBarItem();
	void initMenu();
	void setData(const QDomElement& data);
private slots:
void onSetOrientation(int id);
void onSetRation(int id, bool checked);
void onShowEffect(bool);
protected:
	virtual void closeEvent(QCloseEvent *event)override;
	virtual void dragEnterEvent(QDragEnterEvent *event);
	virtual void dragLeaveEvent(QDragLeaveEvent *event);
	virtual void dragMoveEvent(QDragMoveEvent *event);
	virtual void dropEvent(QDropEvent *event);
private:
	Clipper* m_clipper = nullptr;
	TreeView* m_itemView = nullptr;
	ItemModel* m_itemModel = nullptr;
	TreeView* m_globalView = nullptr;
	AllItemModel* m_globalModel = nullptr;

	QString m_filename;
	QDomDocument m_doc;
	QDomDocument m_emptyDoc;
	QMenu* m_recentMenu = nullptr;
	QRadioButton *m_effectBtns[2] = { nullptr };
	RadioToolButton* m_radioToolBtn = nullptr;
};

