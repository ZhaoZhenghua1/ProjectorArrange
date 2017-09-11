#include "AllItemModel.h"

AllItemModel::AllItemModel()
{
}

AllItemModel::~AllItemModel()
{
}

QVariant AllItemModel::data(const QModelIndex &index, int role) const
{
	return QVariant();
}

bool AllItemModel::setData(const QModelIndex &index, const QVariant &value, int role)
{
	return QAbstractItemModel::setData(index, value, role);
}

Qt::ItemFlags AllItemModel::flags(const QModelIndex &index) const
{
	return QAbstractItemModel::flags(index);
}

QVariant AllItemModel::headerData(int section, Qt::Orientation orientation, int role /*= Qt::DisplayRole*/) const
{
	return QVariant();
}

QModelIndex AllItemModel::index(int row, int column, const QModelIndex &parent /*= QModelIndex()*/) const
{
	return QModelIndex();
}

QModelIndex AllItemModel::parent(const QModelIndex &child) const
{
	return QModelIndex();
}

int AllItemModel::rowCount(const QModelIndex &parent /*= QModelIndex()*/) const
{
	return 1;
}

int AllItemModel::columnCount(const QModelIndex &parent /*= QModelIndex()*/) const
{
	return 2;
}
