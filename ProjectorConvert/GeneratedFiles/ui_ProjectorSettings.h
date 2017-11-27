/********************************************************************************
** Form generated from reading UI file 'ProjectorSettings.ui'
**
** Created by: Qt User Interface Compiler version 5.6.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_PROJECTORSETTINGS_H
#define UI_PROJECTORSETTINGS_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QDoubleSpinBox>
#include <QtWidgets/QGroupBox>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QSpinBox>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>
#include "mapwidget.h"

QT_BEGIN_NAMESPACE

class Ui_Projector
{
public:
    QHBoxLayout *horizontalLayout_2;
    QHBoxLayout *horizontalLayout;
    MapWidget *widgetProjector;
    QHBoxLayout *horizontalLayout_10;
    QHBoxLayout *layout_2;
    QVBoxLayout *verticalLayout;
    QHBoxLayout *horizontalLayout_13;
    QLabel *label_10;
    QHBoxLayout *horizontalLayout_12;
    QLabel *label_8;
    QDoubleSpinBox *doubleSpinBoxScreenWidth;
    QLabel *label_9;
    QHBoxLayout *horizontalLayout_14;
    QLabel *label_17;
    QDoubleSpinBox *doubleSpinBoxScreenHeight;
    QLabel *label_18;
    QHBoxLayout *horizontalLayout_15;
    QLabel *label_19;
    QDoubleSpinBox *doubleSpinBoxDistanceToScreen;
    QLabel *label_21;
    QHBoxLayout *horizontalLayout_11;
    QLabel *label_7;
    QSpinBox *spinBoxDisBelow;
    QLabel *label_12;
    QHBoxLayout *horizontalLayout_9;
    QLabel *label_20;
    QSpinBox *spinBoxDisMid;
    QLabel *label_11;
    QHBoxLayout *horizontalLayout_4;
    QLabel *label_3;
    QComboBox *comboBox;
    QGroupBox *groupBox;
    QHBoxLayout *horizontalLayout_8;
    QHBoxLayout *layout;

    void setupUi(QWidget *Projector)
    {
        if (Projector->objectName().isEmpty())
            Projector->setObjectName(QStringLiteral("Projector"));
        Projector->resize(939, 643);
        horizontalLayout_2 = new QHBoxLayout(Projector);
        horizontalLayout_2->setObjectName(QStringLiteral("horizontalLayout_2"));
        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setObjectName(QStringLiteral("horizontalLayout"));
        widgetProjector = new MapWidget(Projector);
        widgetProjector->setObjectName(QStringLiteral("widgetProjector"));
        QSizePolicy sizePolicy(QSizePolicy::Preferred, QSizePolicy::Preferred);
        sizePolicy.setHorizontalStretch(1);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(widgetProjector->sizePolicy().hasHeightForWidth());
        widgetProjector->setSizePolicy(sizePolicy);
        horizontalLayout_10 = new QHBoxLayout(widgetProjector);
        horizontalLayout_10->setObjectName(QStringLiteral("horizontalLayout_10"));
        layout_2 = new QHBoxLayout();
        layout_2->setObjectName(QStringLiteral("layout_2"));

        horizontalLayout_10->addLayout(layout_2);


        horizontalLayout->addWidget(widgetProjector);

        verticalLayout = new QVBoxLayout();
        verticalLayout->setObjectName(QStringLiteral("verticalLayout"));
        horizontalLayout_13 = new QHBoxLayout();
        horizontalLayout_13->setObjectName(QStringLiteral("horizontalLayout_13"));
        label_10 = new QLabel(Projector);
        label_10->setObjectName(QStringLiteral("label_10"));

        horizontalLayout_13->addWidget(label_10);


        verticalLayout->addLayout(horizontalLayout_13);

        horizontalLayout_12 = new QHBoxLayout();
        horizontalLayout_12->setObjectName(QStringLiteral("horizontalLayout_12"));
        label_8 = new QLabel(Projector);
        label_8->setObjectName(QStringLiteral("label_8"));

        horizontalLayout_12->addWidget(label_8);

        doubleSpinBoxScreenWidth = new QDoubleSpinBox(Projector);
        doubleSpinBoxScreenWidth->setObjectName(QStringLiteral("doubleSpinBoxScreenWidth"));
        doubleSpinBoxScreenWidth->setMaximum(1e+15);
        doubleSpinBoxScreenWidth->setValue(800);

        horizontalLayout_12->addWidget(doubleSpinBoxScreenWidth);

        label_9 = new QLabel(Projector);
        label_9->setObjectName(QStringLiteral("label_9"));

        horizontalLayout_12->addWidget(label_9);


        verticalLayout->addLayout(horizontalLayout_12);

        horizontalLayout_14 = new QHBoxLayout();
        horizontalLayout_14->setObjectName(QStringLiteral("horizontalLayout_14"));
        label_17 = new QLabel(Projector);
        label_17->setObjectName(QStringLiteral("label_17"));

        horizontalLayout_14->addWidget(label_17);

        doubleSpinBoxScreenHeight = new QDoubleSpinBox(Projector);
        doubleSpinBoxScreenHeight->setObjectName(QStringLiteral("doubleSpinBoxScreenHeight"));
        doubleSpinBoxScreenHeight->setMaximum(1e+15);
        doubleSpinBoxScreenHeight->setValue(600);

        horizontalLayout_14->addWidget(doubleSpinBoxScreenHeight);

        label_18 = new QLabel(Projector);
        label_18->setObjectName(QStringLiteral("label_18"));

        horizontalLayout_14->addWidget(label_18);


        verticalLayout->addLayout(horizontalLayout_14);

        horizontalLayout_15 = new QHBoxLayout();
        horizontalLayout_15->setObjectName(QStringLiteral("horizontalLayout_15"));
        label_19 = new QLabel(Projector);
        label_19->setObjectName(QStringLiteral("label_19"));

        horizontalLayout_15->addWidget(label_19);

        doubleSpinBoxDistanceToScreen = new QDoubleSpinBox(Projector);
        doubleSpinBoxDistanceToScreen->setObjectName(QStringLiteral("doubleSpinBoxDistanceToScreen"));
        doubleSpinBoxDistanceToScreen->setMaximum(1e+15);
        doubleSpinBoxDistanceToScreen->setValue(2000);

        horizontalLayout_15->addWidget(doubleSpinBoxDistanceToScreen);

        label_21 = new QLabel(Projector);
        label_21->setObjectName(QStringLiteral("label_21"));

        horizontalLayout_15->addWidget(label_21);


        verticalLayout->addLayout(horizontalLayout_15);

        horizontalLayout_11 = new QHBoxLayout();
        horizontalLayout_11->setObjectName(QStringLiteral("horizontalLayout_11"));
        label_7 = new QLabel(Projector);
        label_7->setObjectName(QStringLiteral("label_7"));

        horizontalLayout_11->addWidget(label_7);

        spinBoxDisBelow = new QSpinBox(Projector);
        spinBoxDisBelow->setObjectName(QStringLiteral("spinBoxDisBelow"));
        spinBoxDisBelow->setMinimum(-100000);
        spinBoxDisBelow->setMaximum(100000);

        horizontalLayout_11->addWidget(spinBoxDisBelow);

        label_12 = new QLabel(Projector);
        label_12->setObjectName(QStringLiteral("label_12"));

        horizontalLayout_11->addWidget(label_12);


        verticalLayout->addLayout(horizontalLayout_11);

        horizontalLayout_9 = new QHBoxLayout();
        horizontalLayout_9->setObjectName(QStringLiteral("horizontalLayout_9"));
        label_20 = new QLabel(Projector);
        label_20->setObjectName(QStringLiteral("label_20"));

        horizontalLayout_9->addWidget(label_20);

        spinBoxDisMid = new QSpinBox(Projector);
        spinBoxDisMid->setObjectName(QStringLiteral("spinBoxDisMid"));
        spinBoxDisMid->setMinimum(-100000);
        spinBoxDisMid->setMaximum(100000);

        horizontalLayout_9->addWidget(spinBoxDisMid);

        label_11 = new QLabel(Projector);
        label_11->setObjectName(QStringLiteral("label_11"));

        horizontalLayout_9->addWidget(label_11);


        verticalLayout->addLayout(horizontalLayout_9);

        horizontalLayout_4 = new QHBoxLayout();
        horizontalLayout_4->setObjectName(QStringLiteral("horizontalLayout_4"));
        label_3 = new QLabel(Projector);
        label_3->setObjectName(QStringLiteral("label_3"));

        horizontalLayout_4->addWidget(label_3);

        comboBox = new QComboBox(Projector);
        comboBox->setObjectName(QStringLiteral("comboBox"));

        horizontalLayout_4->addWidget(comboBox);


        verticalLayout->addLayout(horizontalLayout_4);

        groupBox = new QGroupBox(Projector);
        groupBox->setObjectName(QStringLiteral("groupBox"));
        QSizePolicy sizePolicy1(QSizePolicy::Preferred, QSizePolicy::Preferred);
        sizePolicy1.setHorizontalStretch(0);
        sizePolicy1.setVerticalStretch(1);
        sizePolicy1.setHeightForWidth(groupBox->sizePolicy().hasHeightForWidth());
        groupBox->setSizePolicy(sizePolicy1);
        groupBox->setSizeIncrement(QSize(0, 0));
        horizontalLayout_8 = new QHBoxLayout(groupBox);
        horizontalLayout_8->setObjectName(QStringLiteral("horizontalLayout_8"));
        layout = new QHBoxLayout();
        layout->setObjectName(QStringLiteral("layout"));

        horizontalLayout_8->addLayout(layout);


        verticalLayout->addWidget(groupBox);


        horizontalLayout->addLayout(verticalLayout);


        horizontalLayout_2->addLayout(horizontalLayout);


        retranslateUi(Projector);

        QMetaObject::connectSlotsByName(Projector);
    } // setupUi

    void retranslateUi(QWidget *Projector)
    {
        Projector->setWindowTitle(QApplication::translate("Projector", "Form", 0));
        label_10->setText(QApplication::translate("Projector", "\346\212\225\345\275\261\346\234\272\345\217\202\346\225\260", 0));
        label_8->setText(QApplication::translate("Projector", "\345\261\217\345\271\225\345\256\275\345\272\246", 0));
        label_9->setText(QApplication::translate("Projector", "mm", 0));
        label_17->setText(QApplication::translate("Projector", "\345\261\217\345\271\225\351\253\230\345\272\246", 0));
        label_18->setText(QApplication::translate("Projector", "mm", 0));
        label_19->setText(QApplication::translate("Projector", "\350\267\235\345\261\217\345\271\225\350\267\235\347\246\273", 0));
        label_21->setText(QApplication::translate("Projector", "mm", 0));
        label_7->setText(QApplication::translate("Projector", "\346\212\225\345\275\261\346\234\272\344\270\213\346\262\277\345\210\260\345\261\217\345\271\225\344\270\213\346\262\277\350\267\235\347\246\273", 0));
        label_12->setText(QApplication::translate("Projector", "mm", 0));
        label_20->setText(QApplication::translate("Projector", "\346\212\225\345\275\261\346\234\272\344\270\255\351\227\264\345\210\260\345\261\217\345\271\225\344\270\255\351\227\264\350\267\235\347\246\273", 0));
        label_11->setText(QApplication::translate("Projector", "mm", 0));
        label_3->setText(QApplication::translate("Projector", "\346\212\225\345\275\261\347\261\273\345\236\213", 0));
        comboBox->clear();
        comboBox->insertItems(0, QStringList()
         << QApplication::translate("Projector", "\347\220\203\351\235\242", 0)
         << QApplication::translate("Projector", "\345\271\263\351\235\242", 0)
         << QApplication::translate("Projector", "\346\237\261\351\235\242", 0)
        );
        groupBox->setTitle(QApplication::translate("Projector", "\345\217\202\346\225\260", 0));
    } // retranslateUi

};

namespace Ui {
    class Projector: public Ui_Projector {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_PROJECTORSETTINGS_H
