#include <QRadioButton>
#include <QMenu>
#include "RadioToolButton.h"


const QString TOOLBUTTON_STYLE1 = R"(
QToolButton{spacing:0px;}
QToolButton{width:50px;height:40px;}
QToolButton::unchecked{image:url(%1);}
QToolButton::unchecked:hover{image:url(%2);}
QToolButton::checked{image:url(%3);}
)";

const QString TOOLBUTTON_STYLE = R"(
	QToolButton { /* all types of tool button */
	border: 0px solid #8f8f91;
	width:40px;height:40px;
    background-image: url(%1);
}

QToolButton[popupMode="1"] { /* only for MenuButtonPopup */
    padding-right: 10px; /* make way for the popup button */
}

QToolButton:hover {
    background-image: url(%2);
}
QToolButton:pressed {
    background-image: url(%3);
}

/* the subcontrols below are used only in the MenuButtonPopup mode */
QToolButton::menu-button {
//    border: 2px solid gray;
//    border-top-right-radius: 6px;
//    border-bottom-right-radius: 6px;
    /* 16px width + 4px for border = 20px allocated above */
    width: 10px;
}

QToolButton::menu-arrow {
    image: url(:/downArrow.png);
}

QToolButton::menu-arrow:open {
 //   top: 1px; left: 1px; /* shift it a bit */
}
)";

const QString MENU_STYLE = R"(
QMenu {
    background-color: #535353; /* sets background of the menu */
	color: #ffffff;
    border: 1px solid black;
}
QMenu:disabled{
	color:  rgb(150,150,150);
}
QMenu::item {
    /* sets background of menu item. set this to something non-transparent
        if you want menu color and menu item color to be different */
    background-color: transparent;
}

QMenu::item:selected { /* when user selects item using mouse or keyboard */
    background-color: #3a3a3a;
}
)";

RadioToolButton::RadioToolButton()
{
	connect(this, &QAbstractButton::clicked, this, &RadioToolButton::onToolButtonClicked);
	setPopupMode(QToolButton::MenuButtonPopup);
	setStyleSheet(TOOLBUTTON_STYLE.arg(":/tape_normal.png").arg(":/tape_hover.png").arg(":/tape_pressed.png"));
	setToolTip(m_mode == eDistance ? "Distance Tape" : "Pix Tape");

	QMenu* tapeMenu = new QMenu("Tape type");
	connect(tapeMenu, &QMenu::triggered, this, &RadioToolButton::onMenuTriggered);
	tapeMenu->setStyleSheet(MENU_STYLE);
	QAction* defAction = tapeMenu->addAction("Distance tape");
	defAction->setData(QVariant(eDistance));
	tapeMenu->addAction("Pix tape")->setData(QVariant(ePix));
	setMenu(tapeMenu);

	m_radioBtn = new QRadioButton;
	connect(m_radioBtn, &QRadioButton::toggled, this, &RadioToolButton::onRadioButtonToggled);
}


RadioToolButton::~RadioToolButton()
{
}

void RadioToolButton::onToolButtonClicked()
{
	m_radioBtn->setChecked(true);
}

void RadioToolButton::onRadioButtonToggled(bool checked)
{
	if (checked)
	{
		setStyleSheet(TOOLBUTTON_STYLE.arg(":/tape_pressed.png").arg(":/tape_pressed.png").arg(":/tape_pressed.png"));
	}
	else
	{
		setStyleSheet(TOOLBUTTON_STYLE.arg(":/tape_normal.png").arg(":/tape_hover.png").arg(":/tape_pressed.png"));
	}
}

void RadioToolButton::onMenuTriggered(QAction* action)
{
	m_mode = RadioToolButton::TapeMode(action->data().toInt());
	setToolTip(m_mode == eDistance ? "Distance Tape" : "Pix Tape");
	onToolButtonClicked();
	emit rtBtnToggled();
}
