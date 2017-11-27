/********************************************************************************
** Form generated from reading UI file 'CylinderSettings.ui'
**
** Created by: Qt User Interface Compiler version 5.6.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_CYLINDERSETTINGS_H
#define UI_CYLINDERSETTINGS_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QDoubleSpinBox>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QSpinBox>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_Cylinder
{
public:
    QVBoxLayout *verticalLayout_2;
    QVBoxLayout *verticalLayout;
    QHBoxLayout *horizontalLayout_15;
    QLabel *label_24;
    QSpinBox *spinBoxx;
    QHBoxLayout *horizontalLayout_14;
    QLabel *label_23;
    QSpinBox *spinBoxy;
    QHBoxLayout *horizontalLayout_12;
    QLabel *label_21;
    QSpinBox *spinBoxz;
    QHBoxLayout *horizontalLayout_13;
    QLabel *label_22;
    QSpinBox *spinBoxr;
    QHBoxLayout *horizontalLayout_17;
    QLabel *label_26;
    QSpinBox *spinBoxtheta;
    QHBoxLayout *horizontalLayout_18;
    QLabel *label_27;
    QSpinBox *spinBoxdelta;
    QHBoxLayout *horizontalLayout_6;
    QLabel *label_9;
    QDoubleSpinBox *doubleSpinBoxRotateX;
    QLabel *label_10;
    QHBoxLayout *horizontalLayout_9;
    QLabel *label_15;
    QDoubleSpinBox *doubleSpinBoxRotateY;
    QLabel *label_16;
    QHBoxLayout *horizontalLayout_8;
    QLabel *label_13;
    QDoubleSpinBox *doubleSpinBoxRotateZ;
    QLabel *label_14;

    void setupUi(QWidget *Cylinder)
    {
        if (Cylinder->objectName().isEmpty())
            Cylinder->setObjectName(QStringLiteral("Cylinder"));
        Cylinder->resize(400, 300);
        verticalLayout_2 = new QVBoxLayout(Cylinder);
        verticalLayout_2->setObjectName(QStringLiteral("verticalLayout_2"));
        verticalLayout = new QVBoxLayout();
        verticalLayout->setObjectName(QStringLiteral("verticalLayout"));
        horizontalLayout_15 = new QHBoxLayout();
        horizontalLayout_15->setObjectName(QStringLiteral("horizontalLayout_15"));
        label_24 = new QLabel(Cylinder);
        label_24->setObjectName(QStringLiteral("label_24"));

        horizontalLayout_15->addWidget(label_24);

        spinBoxx = new QSpinBox(Cylinder);
        spinBoxx->setObjectName(QStringLiteral("spinBoxx"));
        spinBoxx->setMinimum(-1000000);
        spinBoxx->setMaximum(1000000);

        horizontalLayout_15->addWidget(spinBoxx);


        verticalLayout->addLayout(horizontalLayout_15);

        horizontalLayout_14 = new QHBoxLayout();
        horizontalLayout_14->setObjectName(QStringLiteral("horizontalLayout_14"));
        label_23 = new QLabel(Cylinder);
        label_23->setObjectName(QStringLiteral("label_23"));

        horizontalLayout_14->addWidget(label_23);

        spinBoxy = new QSpinBox(Cylinder);
        spinBoxy->setObjectName(QStringLiteral("spinBoxy"));
        spinBoxy->setMinimum(-1000000);
        spinBoxy->setMaximum(1000000);

        horizontalLayout_14->addWidget(spinBoxy);


        verticalLayout->addLayout(horizontalLayout_14);

        horizontalLayout_12 = new QHBoxLayout();
        horizontalLayout_12->setObjectName(QStringLiteral("horizontalLayout_12"));
        label_21 = new QLabel(Cylinder);
        label_21->setObjectName(QStringLiteral("label_21"));

        horizontalLayout_12->addWidget(label_21);

        spinBoxz = new QSpinBox(Cylinder);
        spinBoxz->setObjectName(QStringLiteral("spinBoxz"));
        spinBoxz->setMinimum(-1000000);
        spinBoxz->setMaximum(1000000);

        horizontalLayout_12->addWidget(spinBoxz);


        verticalLayout->addLayout(horizontalLayout_12);

        horizontalLayout_13 = new QHBoxLayout();
        horizontalLayout_13->setObjectName(QStringLiteral("horizontalLayout_13"));
        label_22 = new QLabel(Cylinder);
        label_22->setObjectName(QStringLiteral("label_22"));

        horizontalLayout_13->addWidget(label_22);

        spinBoxr = new QSpinBox(Cylinder);
        spinBoxr->setObjectName(QStringLiteral("spinBoxr"));
        spinBoxr->setMaximum(1000000);

        horizontalLayout_13->addWidget(spinBoxr);


        verticalLayout->addLayout(horizontalLayout_13);

        horizontalLayout_17 = new QHBoxLayout();
        horizontalLayout_17->setObjectName(QStringLiteral("horizontalLayout_17"));
        label_26 = new QLabel(Cylinder);
        label_26->setObjectName(QStringLiteral("label_26"));

        horizontalLayout_17->addWidget(label_26);

        spinBoxtheta = new QSpinBox(Cylinder);
        spinBoxtheta->setObjectName(QStringLiteral("spinBoxtheta"));
        spinBoxtheta->setMaximum(360);

        horizontalLayout_17->addWidget(spinBoxtheta);


        verticalLayout->addLayout(horizontalLayout_17);

        horizontalLayout_18 = new QHBoxLayout();
        horizontalLayout_18->setObjectName(QStringLiteral("horizontalLayout_18"));
        label_27 = new QLabel(Cylinder);
        label_27->setObjectName(QStringLiteral("label_27"));

        horizontalLayout_18->addWidget(label_27);

        spinBoxdelta = new QSpinBox(Cylinder);
        spinBoxdelta->setObjectName(QStringLiteral("spinBoxdelta"));
        spinBoxdelta->setMaximum(360);

        horizontalLayout_18->addWidget(spinBoxdelta);


        verticalLayout->addLayout(horizontalLayout_18);

        horizontalLayout_6 = new QHBoxLayout();
        horizontalLayout_6->setObjectName(QStringLiteral("horizontalLayout_6"));
        label_9 = new QLabel(Cylinder);
        label_9->setObjectName(QStringLiteral("label_9"));

        horizontalLayout_6->addWidget(label_9);

        doubleSpinBoxRotateX = new QDoubleSpinBox(Cylinder);
        doubleSpinBoxRotateX->setObjectName(QStringLiteral("doubleSpinBoxRotateX"));
        doubleSpinBoxRotateX->setMinimum(-360);
        doubleSpinBoxRotateX->setMaximum(360);
        doubleSpinBoxRotateX->setValue(0);

        horizontalLayout_6->addWidget(doubleSpinBoxRotateX);

        label_10 = new QLabel(Cylinder);
        label_10->setObjectName(QStringLiteral("label_10"));

        horizontalLayout_6->addWidget(label_10);


        verticalLayout->addLayout(horizontalLayout_6);

        horizontalLayout_9 = new QHBoxLayout();
        horizontalLayout_9->setObjectName(QStringLiteral("horizontalLayout_9"));
        label_15 = new QLabel(Cylinder);
        label_15->setObjectName(QStringLiteral("label_15"));

        horizontalLayout_9->addWidget(label_15);

        doubleSpinBoxRotateY = new QDoubleSpinBox(Cylinder);
        doubleSpinBoxRotateY->setObjectName(QStringLiteral("doubleSpinBoxRotateY"));
        doubleSpinBoxRotateY->setMinimum(-360);
        doubleSpinBoxRotateY->setMaximum(360);
        doubleSpinBoxRotateY->setValue(0);

        horizontalLayout_9->addWidget(doubleSpinBoxRotateY);

        label_16 = new QLabel(Cylinder);
        label_16->setObjectName(QStringLiteral("label_16"));

        horizontalLayout_9->addWidget(label_16);


        verticalLayout->addLayout(horizontalLayout_9);

        horizontalLayout_8 = new QHBoxLayout();
        horizontalLayout_8->setObjectName(QStringLiteral("horizontalLayout_8"));
        label_13 = new QLabel(Cylinder);
        label_13->setObjectName(QStringLiteral("label_13"));

        horizontalLayout_8->addWidget(label_13);

        doubleSpinBoxRotateZ = new QDoubleSpinBox(Cylinder);
        doubleSpinBoxRotateZ->setObjectName(QStringLiteral("doubleSpinBoxRotateZ"));
        doubleSpinBoxRotateZ->setMinimum(-360);
        doubleSpinBoxRotateZ->setMaximum(360);
        doubleSpinBoxRotateZ->setValue(0);

        horizontalLayout_8->addWidget(doubleSpinBoxRotateZ);

        label_14 = new QLabel(Cylinder);
        label_14->setObjectName(QStringLiteral("label_14"));

        horizontalLayout_8->addWidget(label_14);


        verticalLayout->addLayout(horizontalLayout_8);


        verticalLayout_2->addLayout(verticalLayout);


        retranslateUi(Cylinder);

        QMetaObject::connectSlotsByName(Cylinder);
    } // setupUi

    void retranslateUi(QWidget *Cylinder)
    {
        Cylinder->setWindowTitle(QApplication::translate("Cylinder", "Form", 0));
        label_24->setText(QApplication::translate("Cylinder", "x:", 0));
        label_23->setText(QApplication::translate("Cylinder", "y:", 0));
        label_21->setText(QApplication::translate("Cylinder", "z:", 0));
        label_22->setText(QApplication::translate("Cylinder", "r:", 0));
        label_26->setText(QApplication::translate("Cylinder", "\316\270", 0));
        label_27->setText(QApplication::translate("Cylinder", "\316\264", 0));
        label_9->setText(QApplication::translate("Cylinder", "\346\227\213\350\275\254x:", 0));
        label_10->setText(QApplication::translate("Cylinder", "\302\260", 0));
        label_15->setText(QApplication::translate("Cylinder", "\346\227\213\350\275\254y:", 0));
        label_16->setText(QApplication::translate("Cylinder", "\302\260", 0));
        label_13->setText(QApplication::translate("Cylinder", "\346\227\213\350\275\254z:", 0));
        label_14->setText(QApplication::translate("Cylinder", "\302\260", 0));
    } // retranslateUi

};

namespace Ui {
    class Cylinder: public Ui_Cylinder {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_CYLINDERSETTINGS_H
