/********************************************************************************
** Form generated from reading UI file 'about.ui'
**
** Created by: Qt User Interface Compiler version 5.6.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_ABOUT_H
#define UI_ABOUT_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QDialog>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QPushButton>

QT_BEGIN_NAMESPACE

class Ui_AboutDialog
{
public:
    QPushButton *pushButton;
    QLabel *labelUrl;
    QLabel *label;
    QLabel *label_2;

    void setupUi(QDialog *AboutDialog)
    {
        if (AboutDialog->objectName().isEmpty())
            AboutDialog->setObjectName(QStringLiteral("AboutDialog"));
        AboutDialog->resize(398, 132);
        AboutDialog->setMinimumSize(QSize(398, 132));
        AboutDialog->setMaximumSize(QSize(398, 132));
        AboutDialog->setStyleSheet(QLatin1String("color: rgb(255, 255, 255);\n"
"background-color: rgb(83,83, 83);"));
        AboutDialog->setModal(false);
        pushButton = new QPushButton(AboutDialog);
        pushButton->setObjectName(QStringLiteral("pushButton"));
        pushButton->setGeometry(QRect(300, 87, 75, 23));
        labelUrl = new QLabel(AboutDialog);
        labelUrl->setObjectName(QStringLiteral("labelUrl"));
        labelUrl->setGeometry(QRect(138, 31, 183, 22));
        label = new QLabel(AboutDialog);
        label->setObjectName(QStringLiteral("label"));
        label->setGeometry(QRect(26, 11, 110, 110));
        label->setMinimumSize(QSize(110, 110));
        label->setStyleSheet(QStringLiteral("image: url(:/logo.png);"));
        label_2 = new QLabel(AboutDialog);
        label_2->setObjectName(QStringLiteral("label_2"));
        label_2->setGeometry(QRect(138, 50, 171, 20));

        retranslateUi(AboutDialog);
        QObject::connect(pushButton, SIGNAL(clicked()), AboutDialog, SLOT(close()));

        QMetaObject::connectSlotsByName(AboutDialog);
    } // setupUi

    void retranslateUi(QDialog *AboutDialog)
    {
        AboutDialog->setWindowTitle(QApplication::translate("AboutDialog", "About", 0));
        pushButton->setText(QApplication::translate("AboutDialog", "OK", 0));
        labelUrl->setText(QApplication::translate("AboutDialog", "<html><head/><body><p>LightMagic TransCoder V1.0 </p></body></html>", 0));
        label->setText(QString());
        label_2->setText(QApplication::translate("AboutDialog", "www.lightmagictech.com", 0));
    } // retranslateUi

};

namespace Ui {
    class AboutDialog: public Ui_AboutDialog {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_ABOUT_H
