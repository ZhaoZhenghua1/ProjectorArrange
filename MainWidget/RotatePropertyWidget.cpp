#include <QCheckBox>
#include <QComboBox>
#include <QSpinBox>
#include <QHBoxLayout>
#include "RotatePropertyWidget.h"

RotatePropertyWidget::RotatePropertyWidget(QWidget* parent):QWidget(parent)
{
	m_container = new QWidget;
	m_checkBox = new QCheckBox(tr("Free Rotate"));
	m_checkBox->setTristate(false);
	connect(m_checkBox, SIGNAL(stateChanged(int)), this, SLOT(onStateChanged(int)));
	m_combox = new QComboBox;
	m_spinbox = new QSpinBox;
	void (QComboBox::* pComboxDataChanged)(int) = &QComboBox::currentIndexChanged;
	void (QSpinBox::* pSpinboxDataChanged)(int) = &QSpinBox::valueChanged;
	connect(m_combox, pComboxDataChanged, this, &RotatePropertyWidget::dataChanged);
	connect(m_spinbox, pSpinboxDataChanged, this, &RotatePropertyWidget::dataChanged);
	m_spinbox->setRange(0, 359);
	QHBoxLayout* layout = new QHBoxLayout;
	layout->setContentsMargins(0, 0, 0, 0);
	setLayout(layout);
	layout->addWidget(m_container);
	layout->addWidget(m_checkBox);

	QHBoxLayout* containerLayout = new QHBoxLayout;
	containerLayout->setContentsMargins(0, 0, 0, 0);
	m_container->setLayout(containerLayout);
	containerLayout->addWidget(m_combox);
	containerLayout->addWidget(m_spinbox);
}

RotatePropertyWidget::~RotatePropertyWidget()
{
}

void RotatePropertyWidget::setData(const QString& data)
{
	QStringList values = data.split(';');
	m_checkBox->setChecked(values.size() >= 2 ? values[1].toInt() : false);
	onStateChanged(m_checkBox->checkState());
}

QString RotatePropertyWidget::data()
{
	if (m_checkBox->isChecked())
	{
		return QString("%1;1;").arg(m_spinbox->value());
	}
	else
	{
		int rotate = 0;
		if (m_combox->currentText() == "Horizontal")
		{
			rotate = 0;
		}
		else if (m_combox->currentText() == "Vertical")
		{
			rotate = 90;
		}
		else
		{
			rotate = m_combox->currentText().toInt();
		}
		return QString("%1;0;").arg(rotate);
	}
}

void RotatePropertyWidget::onStateChanged(int state)
{
	bool freeRotate = state == Qt::Checked;
	m_spinbox->setVisible(freeRotate);
	m_combox->setVisible(!freeRotate);
	if (state != Qt::Checked)
	{
		QStringList items;
		if (0 == m_spinbox->value())
		{
			items = QStringList({ "Horizontal", "Vertical" });
		}
		else if (90 == m_spinbox->value())
		{
			items = QStringList({ "Vertical", "Horizontal" });
		}
		else
		{
			items = QStringList({m_spinbox->text(),  "Horizontal", "Vertical" });
		}
		m_combox->clear();
		m_combox->addItems(items);
	}
	else
	{
		int rotate = 0;
		if (m_combox->currentText() == "Vertical")
		{
			rotate = 90;
		}
		else
		{
			rotate = m_combox->currentText().toInt();
		}
		m_spinbox->setValue(rotate);
	}
	dataChanged();
}
