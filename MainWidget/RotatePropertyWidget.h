#pragma once
#include <QWidget>

class QComboBox;
class QSpinBox;
class QCheckBox;

class RotatePropertyWidget : public QWidget
{
	Q_OBJECT
public:
	RotatePropertyWidget(QWidget* parent = nullptr);
	~RotatePropertyWidget();
	void setData(const QString& data);
	QString data();
signals:
	void dataChanged();
private slots:
void onStateChanged(int state);
private:
	QComboBox* m_combox = nullptr;
	QSpinBox* m_spinbox = nullptr;
	QCheckBox* m_checkBox = nullptr;
	QWidget* m_container = nullptr;
};

