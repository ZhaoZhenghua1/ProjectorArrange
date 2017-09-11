/********************************************************************************
** Form generated from reading UI file 'PositionWidget.ui'
**
** Created by: Qt User Interface Compiler version 5.6.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_POSITIONWIDGET_H
#define UI_POSITIONWIDGET_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QSpinBox>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_PositionWidget
{
public:
    QHBoxLayout *horizontalLayout_2;
    QHBoxLayout *horizontalLayout;
    QLabel *label;
    QSpinBox *spinBoxx;
    QSpacerItem *horizontalSpacer;
    QLabel *label_2;
    QSpinBox *spinBoxy;

    void setupUi(QWidget *PositionWidget)
    {
        if (PositionWidget->objectName().isEmpty())
            PositionWidget->setObjectName(QStringLiteral("PositionWidget"));
        PositionWidget->resize(222, 40);
        horizontalLayout_2 = new QHBoxLayout(PositionWidget);
        horizontalLayout_2->setObjectName(QStringLiteral("horizontalLayout_2"));
        horizontalLayout_2->setContentsMargins(0, 0, 0, 0);
        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setObjectName(QStringLiteral("horizontalLayout"));
        label = new QLabel(PositionWidget);
        label->setObjectName(QStringLiteral("label"));

        horizontalLayout->addWidget(label);

        spinBoxx = new QSpinBox(PositionWidget);
        spinBoxx->setObjectName(QStringLiteral("spinBoxx"));
        QSizePolicy sizePolicy(QSizePolicy::Minimum, QSizePolicy::Fixed);
        sizePolicy.setHorizontalStretch(1);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(spinBoxx->sizePolicy().hasHeightForWidth());
        spinBoxx->setSizePolicy(sizePolicy);
        spinBoxx->setSizeIncrement(QSize(0, 0));
        spinBoxx->setMinimum(-999999);
        spinBoxx->setMaximum(999999);

        horizontalLayout->addWidget(spinBoxx);

        horizontalSpacer = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout->addItem(horizontalSpacer);

        label_2 = new QLabel(PositionWidget);
        label_2->setObjectName(QStringLiteral("label_2"));

        horizontalLayout->addWidget(label_2);

        spinBoxy = new QSpinBox(PositionWidget);
        spinBoxy->setObjectName(QStringLiteral("spinBoxy"));
        sizePolicy.setHeightForWidth(spinBoxy->sizePolicy().hasHeightForWidth());
        spinBoxy->setSizePolicy(sizePolicy);
        spinBoxy->setSizeIncrement(QSize(1, 0));
        spinBoxy->setMinimum(-999999);
        spinBoxy->setMaximum(999999);

        horizontalLayout->addWidget(spinBoxy);


        horizontalLayout_2->addLayout(horizontalLayout);


        retranslateUi(PositionWidget);

        QMetaObject::connectSlotsByName(PositionWidget);
    } // setupUi

    void retranslateUi(QWidget *PositionWidget)
    {
        PositionWidget->setWindowTitle(QApplication::translate("PositionWidget", "Form", 0));
        label->setText(QApplication::translate("PositionWidget", "X:", 0));
        label_2->setText(QApplication::translate("PositionWidget", "Y:", 0));
    } // retranslateUi

};

namespace Ui {
    class PositionWidget: public Ui_PositionWidget {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_POSITIONWIDGET_H
