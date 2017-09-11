#pragma once
#include <QTreeView>

class TreeView : public QTreeView
{
	typedef QTreeView Base;
public:
	TreeView(QWidget *parent = nullptr);
	~TreeView();
};

