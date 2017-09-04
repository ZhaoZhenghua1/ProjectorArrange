#pragma once
#include <QMainWindow>
#include <QDomDocument>

class Clipper;
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
	QDomElement createElement(const QString& name);
	void onOpenRecent();
signals:
	void zoomIn();
	void zoomOut();
private:
	void addRecent();
	bool close();
	void errorFile(const QString& file);
	QString getAvailableFileName()const;
	void addToRecentFiles(const QString& file);
	bool dispatchData();
protected:
	virtual void closeEvent(QCloseEvent *event)override;
	virtual void dragEnterEvent(QDragEnterEvent *event);
	virtual void dragLeaveEvent(QDragLeaveEvent *event);
	virtual void dragMoveEvent(QDragMoveEvent *event);
	virtual void dropEvent(QDropEvent *event);
private:
	Clipper* m_clipper = nullptr;
	QString m_filename;
	QDomDocument m_doc;
	QDomDocument m_emptyDoc;
	QMenu* m_recentMenu = nullptr;
};

