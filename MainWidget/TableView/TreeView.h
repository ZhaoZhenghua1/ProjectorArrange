#pragma once
#include <QTreeView>

class TreeView : public QTreeView
{
	Q_OBJECT
	typedef QTreeView Base;
public:
	TreeView(QWidget *parent = nullptr);
	~TreeView();
public slots:
void onSetData();
protected:
//	virtual void closeEditor(QWidget *editor, QAbstractItemDelegate::EndEditHint hint)override;
	virtual void mousePressEvent(QMouseEvent *event);
	virtual void mouseDoubleClickEvent(QMouseEvent *event);
	virtual void focusOutEvent(QFocusEvent *event);
private:
	bool m_bInDoubleClick = false;
};

