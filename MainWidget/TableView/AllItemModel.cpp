#include <QFile>
#include "AllItemModel.h"
#include "DomItem.h"

const QStringList INVALID_NODE_LST = { "#cdata-section" ,"#comment" ,"#document" ,"#document-fragment" ,"#text" };

AllItemModel::AllItemModel()
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

AllItemModel::~AllItemModel()
{
}

void AllItemModel::setDomData(const QDomElement& data)
{
	m_domData = data;
}

void AllItemModel::dataChanged()
{
	layoutChanged();
}

QString AllItemModel::getValue(const QScriptValue& expression)
{
	QStringList path = expression.toString().split('.');
	path.removeAll("");
	return ::value(path, m_currentData);
}

void AllItemModel::setValue(const QScriptValue& expression, const QString& value)
{
	QStringList path = expression.toString().split('.');
	path.removeAll("");
	::setValue(path, value, m_currentData);
}

QVariant AllItemModel::data(const QModelIndex &index, int role) const
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
		{
			QString eachValue;
			for (QDomElement data = m_domData.firstChildElement("projector"); !data.isNull(); data = data.nextSiblingElement("projector"))
			{
				QString curValue;
				const_cast<AllItemModel*>(this)->m_currentData = data;
				if (elem.attribute("edittype").contains("read;"))
				{
					curValue = m_engine->evaluate(elem.firstChild().nodeValue()).toString();
				}
				else
				{
					curValue =::value(toPath(node), data);
				}
				if (!eachValue.isEmpty() && eachValue != curValue)
				{
					return "...";
				}
				eachValue = curValue;
			}
			return eachValue;
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
	}


	return QVariant();
}

bool AllItemModel::setData(const QModelIndex &index, const QVariant &val, int role)
{
	if (Qt::EditRole&role)
	{
		DomItem *item = static_cast<DomItem*>(index.internalPointer());
		QStringList path = toPath(item->node());

		for (QDomElement data = m_domData.firstChildElement("projector"); !data.isNull(); data = data.nextSiblingElement("projector"))
		{
			m_currentData = data;
			if (value(path, data) == val.toString())
			{
				continue;
			}
			bool ret = ::setValue(path, val.toString(), data);
			if (item->node().toElement().attribute("edittype").contains("write;"))
			{
				m_engine->evaluate(item->node().toElement().firstChild().nodeValue());
			}
			
		}
		emit allItemDataEdited();
		return true;
	}
	else
	{
		return QAbstractItemModel::setData(index, val, role);
	}
}

Qt::ItemFlags AllItemModel::flags(const QModelIndex &index) const
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

QVariant AllItemModel::headerData(int section, Qt::Orientation orientation, int role /*= Qt::DisplayRole*/) const
{
	return QVariant();
}

QModelIndex AllItemModel::index(int row, int column, const QModelIndex &parent /*= QModelIndex()*/) const
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

QModelIndex AllItemModel::parent(const QModelIndex &child) const
{
	if (!child.isValid())
		return QModelIndex();

	DomItem *childItem = static_cast<DomItem*>(child.internalPointer());
	DomItem *parentItem = childItem->parent();

	if (!parentItem || parentItem == rootItem)
		return QModelIndex();

	return createIndex(parentItem->row(), 0, parentItem);
}

int AllItemModel::rowCount(const QModelIndex &parent /*= QModelIndex()*/) const
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

int AllItemModel::columnCount(const QModelIndex &parent /*= QModelIndex()*/) const
{
	return 2;
}
