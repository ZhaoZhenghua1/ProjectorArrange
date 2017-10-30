/********************************************************************************
** Form generated from reading UI file 'RealScreen.ui'
**
** Created by: Qt User Interface Compiler version 5.6.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_REALSCREEN_H
#define UI_REALSCREEN_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QWidget>
#include "mapwidget.h"

QT_BEGIN_NAMESPACE

class Ui_RealScreen
{
public:
    QHBoxLayout *horizontalLayout_2;
    MapWidget *widget_2;

    void setupUi(QWidget *RealScreen)
    {
        if (RealScreen->objectName().isEmpty())
            RealScreen->setObjectName(QStringLiteral("RealScreen"));
        RealScreen->resize(562, 359);
        horizontalLayout_2 = new QHBoxLayout(RealScreen);
        horizontalLayout_2->setObjectName(QStringLiteral("horizontalLayout_2"));
        widget_2 = new MapWidget(RealScreen);
        widget_2->setObjectName(QStringLiteral("widget_2"));
        QSizePolicy sizePolicy(QSizePolicy::Preferred, QSizePolicy::Preferred);
        sizePolicy.setHorizontalStretch(1);
        sizePolicy.setVerticalStretch(1);
        sizePolicy.setHeightForWidth(widget_2->sizePolicy().hasHeightForWidth());
        widget_2->setSizePolicy(sizePolicy);
        widget_2->setMinimumSize(QSize(100, 0));

        horizontalLayout_2->addWidget(widget_2);


        retranslateUi(RealScreen);

        QMetaObject::connectSlotsByName(RealScreen);
    } // setupUi

    void retranslateUi(QWidget *RealScreen)
    {
        RealScreen->setWindowTitle(QApplication::translate("RealScreen", "RealScreen", 0));
    } // retranslateUi

};

namespace Ui {
    class RealScreen: public Ui_RealScreen {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_REALSCREEN_H
