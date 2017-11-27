/********************************************************************************
** Form generated from reading UI file 'PlaneSetting.ui'
**
** Created by: Qt User Interface Compiler version 5.6.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_PLANESETTING_H
#define UI_PLANESETTING_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QDoubleSpinBox>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_Plane
{
public:
    QVBoxLayout *verticalLayout_2;
    QVBoxLayout *verticalLayout;
    QHBoxLayout *horizontalLayout_10;
    QLabel *label_18;
    QDoubleSpinBox *doubleSpinBoxDistanceToRealScreen;
    QLabel *label_19;
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

    void setupUi(QWidget *Plane)
    {
        if (Plane->objectName().isEmpty())
            Plane->setObjectName(QStringLiteral("Plane"));
        Plane->resize(692, 482);
        verticalLayout_2 = new QVBoxLayout(Plane);
        verticalLayout_2->setObjectName(QStringLiteral("verticalLayout_2"));
        verticalLayout = new QVBoxLayout();
        verticalLayout->setObjectName(QStringLiteral("verticalLayout"));
        horizontalLayout_10 = new QHBoxLayout();
        horizontalLayout_10->setObjectName(QStringLiteral("horizontalLayout_10"));
        label_18 = new QLabel(Plane);
        label_18->setObjectName(QStringLiteral("label_18"));

        horizontalLayout_10->addWidget(label_18);

        doubleSpinBoxDistanceToRealScreen = new QDoubleSpinBox(Plane);
        doubleSpinBoxDistanceToRealScreen->setObjectName(QStringLiteral("doubleSpinBoxDistanceToRealScreen"));
        doubleSpinBoxDistanceToRealScreen->setMaximum(1e+15);
        doubleSpinBoxDistanceToRealScreen->setValue(2000);

        horizontalLayout_10->addWidget(doubleSpinBoxDistanceToRealScreen);

        label_19 = new QLabel(Plane);
        label_19->setObjectName(QStringLiteral("label_19"));

        horizontalLayout_10->addWidget(label_19);


        verticalLayout->addLayout(horizontalLayout_10);

        horizontalLayout_6 = new QHBoxLayout();
        horizontalLayout_6->setObjectName(QStringLiteral("horizontalLayout_6"));
        label_9 = new QLabel(Plane);
        label_9->setObjectName(QStringLiteral("label_9"));

        horizontalLayout_6->addWidget(label_9);

        doubleSpinBoxRotateX = new QDoubleSpinBox(Plane);
        doubleSpinBoxRotateX->setObjectName(QStringLiteral("doubleSpinBoxRotateX"));
        doubleSpinBoxRotateX->setMaximum(360);
        doubleSpinBoxRotateX->setValue(90);

        horizontalLayout_6->addWidget(doubleSpinBoxRotateX);

        label_10 = new QLabel(Plane);
        label_10->setObjectName(QStringLiteral("label_10"));

        horizontalLayout_6->addWidget(label_10);


        verticalLayout->addLayout(horizontalLayout_6);

        horizontalLayout_9 = new QHBoxLayout();
        horizontalLayout_9->setObjectName(QStringLiteral("horizontalLayout_9"));
        label_15 = new QLabel(Plane);
        label_15->setObjectName(QStringLiteral("label_15"));

        horizontalLayout_9->addWidget(label_15);

        doubleSpinBoxRotateY = new QDoubleSpinBox(Plane);
        doubleSpinBoxRotateY->setObjectName(QStringLiteral("doubleSpinBoxRotateY"));
        doubleSpinBoxRotateY->setMaximum(360);
        doubleSpinBoxRotateY->setValue(90);

        horizontalLayout_9->addWidget(doubleSpinBoxRotateY);

        label_16 = new QLabel(Plane);
        label_16->setObjectName(QStringLiteral("label_16"));

        horizontalLayout_9->addWidget(label_16);


        verticalLayout->addLayout(horizontalLayout_9);

        horizontalLayout_8 = new QHBoxLayout();
        horizontalLayout_8->setObjectName(QStringLiteral("horizontalLayout_8"));
        label_13 = new QLabel(Plane);
        label_13->setObjectName(QStringLiteral("label_13"));

        horizontalLayout_8->addWidget(label_13);

        doubleSpinBoxRotateZ = new QDoubleSpinBox(Plane);
        doubleSpinBoxRotateZ->setObjectName(QStringLiteral("doubleSpinBoxRotateZ"));
        doubleSpinBoxRotateZ->setMaximum(360);
        doubleSpinBoxRotateZ->setValue(0);

        horizontalLayout_8->addWidget(doubleSpinBoxRotateZ);

        label_14 = new QLabel(Plane);
        label_14->setObjectName(QStringLiteral("label_14"));

        horizontalLayout_8->addWidget(label_14);


        verticalLayout->addLayout(horizontalLayout_8);


        verticalLayout_2->addLayout(verticalLayout);


        retranslateUi(Plane);

        QMetaObject::connectSlotsByName(Plane);
    } // setupUi

    void retranslateUi(QWidget *Plane)
    {
        Plane->setWindowTitle(QApplication::translate("Plane", "Form", 0));
        label_18->setText(QApplication::translate("Plane", "\350\267\235\346\212\225\345\275\261\346\234\272\350\267\235\347\246\273", 0));
        label_19->setText(QApplication::translate("Plane", "mm", 0));
        label_9->setText(QApplication::translate("Plane", "\346\227\213\350\275\254x:", 0));
        label_10->setText(QApplication::translate("Plane", "\302\260", 0));
        label_15->setText(QApplication::translate("Plane", "\346\227\213\350\275\254y:", 0));
        label_16->setText(QApplication::translate("Plane", "\302\260", 0));
        label_13->setText(QApplication::translate("Plane", "\346\227\213\350\275\254z:", 0));
        label_14->setText(QApplication::translate("Plane", "\302\260", 0));
    } // retranslateUi

};

namespace Ui {
    class Plane: public Ui_Plane {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_PLANESETTING_H
