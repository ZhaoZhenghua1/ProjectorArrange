/****************************************************************************
**
** Copyright (C) 2015 The Qt Company Ltd.
** Contact: http://www.qt.io/licensing/
**
** This file is part of the examples of the Qt Toolkit.
**
** $QT_BEGIN_LICENSE:BSD$
** You may use this file under the terms of the BSD license as follows:
**
** "Redistribution and use in source and binary forms, with or without
** modification, are permitted provided that the following conditions are
** met:
**   * Redistributions of source code must retain the above copyright
**     notice, this list of conditions and the following disclaimer.
**   * Redistributions in binary form must reproduce the above copyright
**     notice, this list of conditions and the following disclaimer in
**     the documentation and/or other materials provided with the
**     distribution.
**   * Neither the name of The Qt Company Ltd nor the names of its
**     contributors may be used to endorse or promote products derived
**     from this software without specific prior written permission.
**
**
** THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
** "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
** LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR
** A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT
** OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL,
** SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT
** LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
** DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY
** THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
** (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
** OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE."
**
** $QT_END_LICENSE$
**
****************************************************************************/

/*
    delegate.cpp

    A delegate that allows the user to change integer values from the model
    using a spin box widget.
*/

#include "ProjectorDelegate.h"
#include "ItemModel.h"
#include <QSpinBox>
#include <QComboBox>
#include <QPainter>
#include <QLineEdit>
#include <QTreeView>
#include "RotatePropertyWidget.h"
#include "PositionWidget.h"
#include "DomItem.h"

const QString EDIT_TYPE_INT = "INT";
const QString EDIT_TYPE_FLOAT = "FLOAT";
const QString EDIT_TYPE_ENUM = "ENUM";
//! [0]
TreeviewDelegate::TreeviewDelegate(QObject *parent)
    : QStyledItemDelegate(parent)
{
}

//! [0]

//! [1]
QWidget *TreeviewDelegate::createEditor(QWidget *parent,
    const QStyleOptionViewItem &/* option */,
    const QModelIndex & index ) const
{
	//只有第一列才可以编辑
	const int VALUE_COL = 1;
	if (index.column() != VALUE_COL)
	{
		return nullptr;
	}
	//根据编辑类型创建控件
	QString editType = index.model()->data(index, E_EDIT_TYPE_RULL).toString();
	QString editRange = index.model()->data(index, E_EDIT_RANGE_RULL).toString();
	if (editType.contains("int;"))
	{
		QSpinBox *editor = new QSpinBox(parent);
		editor->setStyleSheet("color: rgb(255, 255, 255);");
		connect(editor, SIGNAL(valueChanged(int)), this, SLOT(onValueChanged()));
		editor->setFrame(false);
		QStringList range = editRange.split('~');
		if (!range.empty())
		{
			editor->setMinimum(range.first().toInt());
			editor->setMaximum(range.last().toInt());
		}
		editor->setFont(index.model()->data(index, Qt::FontRole).value<QFont>());
		return editor;
	}
	else if (editType.contains("float;"))
	{
		QDoubleSpinBox *editor = new QDoubleSpinBox(parent);
		editor->setStyleSheet("color: rgb(255, 255, 255);");
		editor->setDecimals(2);
		connect(editor, SIGNAL(valueChanged(double)), this, SLOT(onValueChanged()));
		editor->setFrame(false);
		QStringList range = editRange.split('~');
		if (!range.empty())
		{
			editor->setMinimum(range.first().toInt());
			editor->setMaximum(range.last().toInt());
		}
		editor->setFont(index.model()->data(index, Qt::FontRole).value<QFont>());
		return editor;
	}
	else if (editType.contains("enum;"))
	{
		QComboBox* editor = new QComboBox(parent);
		editor->setStyleSheet("color: rgb(255, 255, 255);");
		connect(editor, SIGNAL(currentIndexChanged(int)), this, SLOT(onValueChanged()));
		editor->setFrame(false);
		QStringList range = editRange.split(';');
		range.removeAll("");
		if (!range.empty())
		{
			editor->addItems(range);
		}
		editor->setFont(index.model()->data(index, Qt::FontRole).value<QFont>());
		return editor;
	}
	else if (editType.contains("string;"))
	{
		QLineEdit* editor = new QLineEdit(parent);
		connect(editor, SIGNAL(textChanged(const QString &)), this, SLOT(onValueChanged()));
		return editor;
	}
	else if (editType.contains("putstyle;"))
	{
		RotatePropertyWidget* editor = new RotatePropertyWidget(parent);
		connect(editor, SIGNAL(dataChanged()), this, SLOT(onValueChanged()));
		return editor;
	}
	else if (editType.contains("position;"))
	{
		PositionWidget* editor = new PositionWidget(parent);
		connect(editor, SIGNAL(dataChanged()), this, SLOT(onValueChanged()));
		return editor;
	}
	else
	{
		return nullptr;
	}
}

void TreeviewDelegate::closeEditor(QWidget *editor, QAbstractItemDelegate::EndEditHint hint /* = NoHint */)
{
	QStyledItemDelegate::closeEditor(editor, hint);
}

void TreeviewDelegate::destroyEditor(QWidget *editor, const QModelIndex &index) const
{
	QStyledItemDelegate::destroyEditor(editor, index);
}

//! [1]

//! [2]
void TreeviewDelegate::setEditorData(QWidget *editor,
                                    const QModelIndex &index) const
{
    QVariant value = index.model()->data(index, Qt::EditRole);

	if (QSpinBox *spinBox = qobject_cast<QSpinBox*>(editor))
	{
		spinBox->setValue(value.toInt());
	}
	else if (QDoubleSpinBox *spinBox = qobject_cast<QDoubleSpinBox*>(editor))
	{
		spinBox->setValue(value.toDouble());
	}
	else if (QComboBox* combobox = qobject_cast<QComboBox*>(editor))
	{
		combobox->setCurrentIndex(combobox->findText(value.toString()));
	}
	else if (QLineEdit* lineedit = qobject_cast<QLineEdit*>(editor))
	{
		lineedit->setText(value.toString());
	}
	else if (RotatePropertyWidget* rotateWidget = qobject_cast<RotatePropertyWidget*>(editor))
	{
		rotateWidget->setData(value.toString());
	}
	else if (PositionWidget* positionWidget = qobject_cast<PositionWidget*>(editor))
	{
		positionWidget->setData(value.toString());
	}

}
//! [2]

//! [3]
void TreeviewDelegate::setModelData(QWidget *editor, QAbstractItemModel *model,
                                   const QModelIndex &index) const
{
	QVariant value;
	if (QSpinBox *spinBox = qobject_cast<QSpinBox*>(editor))
	{
		//spinBox->interpretText();
		value = spinBox->value();
	}
	else if (QDoubleSpinBox *spinBox = qobject_cast<QDoubleSpinBox*>(editor))
	{
		value = spinBox->text();
	}
	else if (QComboBox* combobox = qobject_cast<QComboBox*>(editor))
	{
		value = combobox->currentText();
	}
	else if (QLineEdit* lineEdit = qobject_cast<QLineEdit*>(editor))
	{
		value = lineEdit->text();
	}
	else if (RotatePropertyWidget* rotateWidget = qobject_cast<RotatePropertyWidget*>(editor))
	{
		value = rotateWidget->data();
	}
	else if (PositionWidget* positionWidget = qobject_cast<PositionWidget*>(editor))
	{
		value = positionWidget->data();
	}
    model->setData(index, value, Qt::EditRole);
}
//! [3]

//! [4]
void TreeviewDelegate::updateEditorGeometry(QWidget *editor,
    const QStyleOptionViewItem &option, const QModelIndex &/* index */) const
{
    editor->setGeometry(option.rect);
}

void TreeviewDelegate::paint(QPainter *painter, const QStyleOptionViewItem &option, const QModelIndex &index) const 
{
	QStyledItemDelegate::paint(painter, option, index);
	QWidget* parent = const_cast<QWidget*>(option.widget);
	QTreeView* treeView = qobject_cast<QTreeView*>(parent);
	if (QWidget* widget = createEditor(treeView->viewport(), option, index))
	{
		setEditorData(widget, index);
		updateEditorGeometry(widget, option, index);
		QPixmap map = widget->grab();
		QRect rectMap = option.rect;
		painter->drawPixmap(rectMap, map, map.rect());
		widget->deleteLater();
	}
}

//实时刷新
void TreeviewDelegate::onValueChanged()
{
	commitData(qobject_cast<QWidget*>(sender()));
}

//! [4]

QWidget * AllItemDelegate::createEditor(QWidget *parent, const QStyleOptionViewItem &option, const QModelIndex &index) const 
{
	if (!index.isValid())
		return nullptr;

	//名称和位置 不能编辑
	if (index.row() == 0 || index.row() == 1)
	{
		return nullptr;
	}
	
	return TreeviewDelegate::createEditor(parent, option, index);
}

void AllItemDelegate::paint(QPainter *painter, const QStyleOptionViewItem &option, const QModelIndex &index) const 
{
	QStyledItemDelegate::paint(painter, option, index);
	QWidget* parent = const_cast<QWidget*>(option.widget);
	QTreeView* treeView = qobject_cast<QTreeView*>(parent);
	if (index.model()->data(index, Qt::EditRole).toString() == "...")
	{
		return;
	}
	if (QWidget* widget = createEditor(treeView->viewport(), option, index))
	{
		setEditorData(widget, index);
		updateEditorGeometry(widget, option, index);
		QPixmap map = widget->grab();
		QRect rectMap = option.rect;
		painter->drawPixmap(rectMap, map, map.rect());
		widget->deleteLater();
	}
}
