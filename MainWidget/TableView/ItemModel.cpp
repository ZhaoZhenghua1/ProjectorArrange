#include <QFile>
#include "ItemModel.h"
#include "DomItem.h"

const QStringList INVALID_NODE_LST = { "#cdata-section" ,"#comment" ,"#document" ,"#document-fragment" ,"#text" };

ItemModel::ItemModel()
{
	QFile file(":/projectorpattern.xml");
	if (file.open(QIODevice::ReadOnly))
	{
		m_domDocConfig.setContent(&file);
		file.close();
	}
	rootItem = new DomItem(m_domDocConfig.firstChildElement("projector"), 0);

	m_engine = new QScriptEngine(this);

	m_data = m_engine->newQObject(this, QScriptEngine::QtOwnership, QScriptEngine::ExcludeSuperClassContents);
	m_engine->globalObject().setProperty("data", m_data);
}


ItemModel::~ItemModel()
{
	delete rootItem;
}

void ItemModel::dataChanged()
{
	layoutChanged();
}

QString ItemModel::getValue(const QScriptValue& expression)
{
	QStringList path = expression.toString().split('.');
	path.removeAll("");
	return ::value(path, currentItemData());
}

void ItemModel::setValue(const QScriptValue& expression, const QString& value)
{
	QStringList path = expression.toString().split('.');
	path.removeAll("");
	::setValue(path, value, currentItemData());
}

QVariant ItemModel::data(const QModelIndex &index, int role) const
{
	if (!index.isValid())
		return QVariant();

	DomItem *item = static_cast<DomItem*>(index.internalPointer());

	QDomNode node = item->node();
	QDomElement elem = node.toElement();
	//显示tooptip
	if (Qt::ToolTipRole == role)
	{
		return elem.attribute("des");
	}
	//编辑和显示
	else if (Qt::EditRole == role || Qt::DisplayRole == role)
	{
		switch (index.column())
		{
		case 0:
			return elem.attribute("name");
		case 1:
			if (elem.attribute("edittype").contains("read;"))
			{
				return m_engine->evaluate(elem.firstChild().nodeValue()).toString();
			}
			else
			{
				return value(toPath(node), currentItemData());
			}
		default:
			return QVariant();
		}
	}
	//编辑类型
	else if (E_EDIT_TYPE_RULL == role)
	{
		return elem.attribute("edittype");
	}
	//值范围
	else if (E_EDIT_RANGE_RULL == role)
	{
		return elem.attribute("range");
	}
	else if (Qt::TextColorRole == role)
	{
		//可编辑项为白色字体
		if (elem.attribute("edittype") == "calres")
		{
	//		return QVariant(QColor(Qt::gray));
		}
		//不可编辑项为灰色字体
		else
		{
		//	return QVariant(QColor(Qt::white));
		}
	}
	else if (Qt::FontRole == role)
	{
// 		if (!elem.hasAttribute("edittype"))
// 		{
// 			return QVariant(QFont("微软雅黑", 11, 75));
// 		}
// 		else
// 		{
// 			return QVariant(QFont("微软雅黑", 10));
// 		}
	}




	return QVariant();
}

bool ItemModel::setData(const QModelIndex &index, const QVariant &val, int role) 
{
	if (Qt::EditRole&role)
	{
		DomItem *item = static_cast<DomItem*>(index.internalPointer());
		QStringList path = toPath(item->node());
		if (value(path, currentItemData()) == val.toString())
		{
			return true;
		}
		bool ret = ::setValue(path, val.toString(), currentItemData());
		if (item->node().toElement().attribute("edittype").contains("write;"))
		{
			m_engine->evaluate(item->node().toElement().firstChild().nodeValue());
		}
		emit currentItemDataEdited();
		return ret;
	}
	else
	{
 		return QAbstractItemModel::setData(index, val, role);
	}
}

Qt::ItemFlags ItemModel::flags(const QModelIndex &index) const 
{
	if (!index.isValid())
		return 0;

	if (index.column() == 1)
	{
		return QAbstractItemModel::flags(index) | Qt::ItemIsEditable;
	}
	else
	{
		return QAbstractItemModel::flags(index);
	}
}

QVariant ItemModel::headerData(int section, Qt::Orientation orientation, int role /*= Qt::DisplayRole*/) const 
{
	return QVariant();
}

QModelIndex ItemModel::index(int row, int column, const QModelIndex &parent /*= QModelIndex()*/) const 
{
	if (!hasIndex(row, column, parent))
		return QModelIndex();

	DomItem *parentItem;

	if (!parent.isValid())
	{
		parentItem = rootItem;
	}
	else
		parentItem = static_cast<DomItem*>(parent.internalPointer());
	//! [7]

	//! [8]
	DomItem *childItem = parentItem->child(row);
	if (childItem)
		return createIndex(row, column, childItem);
	else
		return QModelIndex();
}

QModelIndex ItemModel::parent(const QModelIndex &child) const 
{
	if (!child.isValid())
		return QModelIndex();

	DomItem *childItem = static_cast<DomItem*>(child.internalPointer());
	DomItem *parentItem = childItem->parent();

	if (!parentItem || parentItem == rootItem)
		return QModelIndex();

	return createIndex(parentItem->row(), 0, parentItem);
}

int ItemModel::rowCount(const QModelIndex &parent /*= QModelIndex()*/) const 
{
	if (parent.column() > 0)
		return 0;

	DomItem *parentItem;

	if (!parent.isValid())
		parentItem = rootItem;
	else
		parentItem = static_cast<DomItem*>(parent.internalPointer());
	
	if (!parentItem)
		return 0;
	
	QString nodename = parentItem->node().nodeName();

	QDomNodeList nodeLst = parentItem->node().childNodes();

	int count = nodeLst.count();
	for (int i = 0; i < nodeLst.count(); ++i)
	{
		if (INVALID_NODE_LST.contains(nodeLst.at(i).nodeName()))
		{
			--count;
		}
	}
	return count;
}

int ItemModel::columnCount(const QModelIndex &parent /*= QModelIndex()*/) const 
{
	return 2;
}

QStringList toPath(const QDomNode& node)
{
	QDomNode nodeIt = node;
	QStringList nodeLst;
	while (!nodeIt.isNull())
	{
		nodeLst.push_back(nodeIt.nodeName());
		nodeIt = nodeIt.parentNode();
	}
	std::reverse(nodeLst.begin(), nodeLst.end());
	nodeLst.removeFirst();
	return nodeLst;
}

QString value(const QStringList& path, const QDomElement& data)
{
	QDomNode domElem = data;
	if (data.nodeName() != path.first())
	{
		return "";
	}
	for (QStringList::const_iterator ite = path.cbegin() + 1; ite != path.cend() && !domElem.isNull(); ++ite)
	{
		domElem = domElem.firstChildElement(*ite);
	}

	return domElem.toElement().text();
}

bool setValue(const QStringList& path, const QString& value, QDomElement& data)
{
	QDomNode domElem = data;
	if (data.nodeName() != path.first())
	{
		return false;
	}
	for (QStringList::const_iterator ite = path.cbegin() + 1; ite != path.cend() && !domElem.isNull(); ++ite)
	{
		domElem = domElem.firstChildElement(*ite);
	}
	if (domElem.isNull())
	{
		return false;
	}

	domElem.firstChild().setNodeValue(value);
	return true;
}