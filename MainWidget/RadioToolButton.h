#pragma once
#include <QToolButton>

class QRadioButton;
class RadioToolButton : public QToolButton
{
	Q_OBJECT
public:
	enum TapeMode
	{
		eDistance,ePix,
	};
public:
	RadioToolButton();
	~RadioToolButton();
public:
	QRadioButton* radioButton() { return m_radioBtn; }
	TapeMode tapeMode() { return m_mode; }
signals:
	void rtBtnToggled();
public slots :
	void onToolButtonClicked();
	void onRadioButtonToggled(bool checked);
	void onMenuTriggered(QAction* action);
private:
	QRadioButton* m_radioBtn = nullptr;
	TapeMode m_mode = eDistance;
};

