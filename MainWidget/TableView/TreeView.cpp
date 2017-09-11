#include "TreeView.h"
#include "ProjectorDelegate.h"

TreeView::TreeView(QWidget *parent):Base(parent)
{
	setHeaderHidden(true);
	setItemDelegate(new TreeviewDelegate);
}


TreeView::~TreeView()
{
}
