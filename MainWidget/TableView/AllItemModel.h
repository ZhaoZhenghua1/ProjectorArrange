#pragma once
#include <QAbstractItemModel>
#include <QDomElement>
#include "ItemModel.h"

class AllItemModel : public QAbstractItemModel
{
	Q_OBJECT
public:
	AllItemModel();
	~AllItemModel();

	void setDomData(const QDomElement& data);
signals:
	void allItemDataEdited() const;
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
	QDomElement m_domData;
	QDomElement m_currentData;
	QScriptValue m_data;
	QScriptEngine* m_engine = nullptr;
};

