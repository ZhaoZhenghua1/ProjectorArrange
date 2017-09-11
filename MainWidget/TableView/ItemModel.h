#pragma once
#include <QAbstractItemModel>
#include <QDomElement>
#include <QScriptEngine>
#include <QScriptable>

enum
{
	//编辑类型，每种编辑类型对应相应的控件
	E_EDIT_TYPE_RULL = Qt::UserRole + 1,
	//值的范围
	E_EDIT_RANGE_RULL = Qt::UserRole + 2,
};
class DomItem;
class ItemModel : public QAbstractItemModel
{
	Q_OBJECT
public:
	ItemModel();
	~ItemModel();
signals:
	QDomElement currentItemData() const;
	void currentItemDataEdited() const;
public slots:
	void dataChanged();
public slots:
	QString getValue(const QScriptValue& expression);
	void setValue(const QScriptValue& expression, const QString& value);
protected:
	QVariant data(const QModelIndex &index, int role) const Q_DECL_OVERRIDE;
	virtual bool setData(const QModelIndex &index, const QVariant &value, int role) Q_DECL_OVERRIDE;
	Qt::ItemFlags flags(const QModelIndex &index) const Q_DECL_OVERRIDE;
	QVariant headerData(int section, Qt::Orientation orientation,
		int role = Qt::DisplayRole) const Q_DECL_OVERRIDE;
	QModelIndex index(int row, int column,
		const QModelIndex &parent = QModelIndex()) const Q_DECL_OVERRIDE;
	QModelIndex parent(const QModelIndex &child) const Q_DECL_OVERRIDE;
	int rowCount(const QModelIndex &parent = QModelIndex()) const Q_DECL_OVERRIDE;
	int columnCount(const QModelIndex &parent = QModelIndex()) const Q_DECL_OVERRIDE;
private:
	DomItem *rootItem = nullptr;
	QDomDocument m_domDocConfig;
	QScriptValue m_data;
	QScriptEngine* m_engine = nullptr;
};

QStringList toPath(const QDomNode& node);
QString value(const QStringList& path, const QDomElement& data);
bool setValue(const QStringList& path, const QString& value, QDomElement& data);
