/********************************************************************************
** Form generated from reading UI file 'BallSettings.ui'
**
** Created by: Qt User Interface Compiler version 5.6.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_BALLSETTINGS_H
#define UI_BALLSETTINGS_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QSpinBox>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_Ball
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
    QHBoxLayout *horizontalLayout_16;
    QLabel *label_25;
    QSpinBox *spinBoxphi;
    QHBoxLayout *horizontalLayout_18;
    QLabel *label_27;
    QSpinBox *spinBoxdelta;

    void setupUi(QWidget *Ball)
    {
        if (Ball->objectName().isEmpty())
            Ball->setObjectName(QStringLiteral("Ball"));
        Ball->resize(597, 300);
        verticalLayout_2 = new QVBoxLayout(Ball);
        verticalLayout_2->setObjectName(QStringLiteral("verticalLayout_2"));
        verticalLayout = new QVBoxLayout();
        verticalLayout->setObjectName(QStringLiteral("verticalLayout"));
        horizontalLayout_15 = new QHBoxLayout();
        horizontalLayout_15->setObjectName(QStringLiteral("horizontalLayout_15"));
        label_24 = new QLabel(Ball);
        label_24->setObjectName(QStringLiteral("label_24"));

        horizontalLayout_15->addWidget(label_24);

        spinBoxx = new QSpinBox(Ball);
        spinBoxx->setObjectName(QStringLiteral("spinBoxx"));
        spinBoxx->setMinimum(-1000000);
        spinBoxx->setMaximum(1000000);

        horizontalLayout_15->addWidget(spinBoxx);


        verticalLayout->addLayout(horizontalLayout_15);

        horizontalLayout_14 = new QHBoxLayout();
        horizontalLayout_14->setObjectName(QStringLiteral("horizontalLayout_14"));
        label_23 = new QLabel(Ball);
        label_23->setObjectName(QStringLiteral("label_23"));

        horizontalLayout_14->addWidget(label_23);

        spinBoxy = new QSpinBox(Ball);
        spinBoxy->setObjectName(QStringLiteral("spinBoxy"));
        spinBoxy->setMinimum(-1000000);
        spinBoxy->setMaximum(1000000);

        horizontalLayout_14->addWidget(spinBoxy);


        verticalLayout->addLayout(horizontalLayout_14);

        horizontalLayout_12 = new QHBoxLayout();
        horizontalLayout_12->setObjectName(QStringLiteral("horizontalLayout_12"));
        label_21 = new QLabel(Ball);
        label_21->setObjectName(QStringLiteral("label_21"));

        horizontalLayout_12->addWidget(label_21);

        spinBoxz = new QSpinBox(Ball);
        spinBoxz->setObjectName(QStringLiteral("spinBoxz"));
        spinBoxz->setMinimum(-1000000);
        spinBoxz->setMaximum(1000000);
        spinBoxz->setValue(3000);

        horizontalLayout_12->addWidget(spinBoxz);


        verticalLayout->addLayout(horizontalLayout_12);

        horizontalLayout_13 = new QHBoxLayout();
        horizontalLayout_13->setObjectName(QStringLiteral("horizontalLayout_13"));
        label_22 = new QLabel(Ball);
        label_22->setObjectName(QStringLiteral("label_22"));

        horizontalLayout_13->addWidget(label_22);

        spinBoxr = new QSpinBox(Ball);
        spinBoxr->setObjectName(QStringLiteral("spinBoxr"));
        spinBoxr->setMaximum(1000000);
        spinBoxr->setValue(1000);

        horizontalLayout_13->addWidget(spinBoxr);


        verticalLayout->addLayout(horizontalLayout_13);

        horizontalLayout_17 = new QHBoxLayout();
        horizontalLayout_17->setObjectName(QStringLiteral("horizontalLayout_17"));
        label_26 = new QLabel(Ball);
        label_26->setObjectName(QStringLiteral("label_26"));

        horizontalLayout_17->addWidget(label_26);

        spinBoxtheta = new QSpinBox(Ball);
        spinBoxtheta->setObjectName(QStringLiteral("spinBoxtheta"));
        spinBoxtheta->setMaximum(360);

        horizontalLayout_17->addWidget(spinBoxtheta);


        verticalLayout->addLayout(horizontalLayout_17);

        horizontalLayout_16 = new QHBoxLayout();
        horizontalLayout_16->setObjectName(QStringLiteral("horizontalLayout_16"));
        label_25 = new QLabel(Ball);
        label_25->setObjectName(QStringLiteral("label_25"));

        horizontalLayout_16->addWidget(label_25);

        spinBoxphi = new QSpinBox(Ball);
        spinBoxphi->setObjectName(QStringLiteral("spinBoxphi"));
        spinBoxphi->setMaximum(360);

        horizontalLayout_16->addWidget(spinBoxphi);


        verticalLayout->addLayout(horizontalLayout_16);

        horizontalLayout_18 = new QHBoxLayout();
        horizontalLayout_18->setObjectName(QStringLiteral("horizontalLayout_18"));
        label_27 = new QLabel(Ball);
        label_27->setObjectName(QStringLiteral("label_27"));

        horizontalLayout_18->addWidget(label_27);

        spinBoxdelta = new QSpinBox(Ball);
        spinBoxdelta->setObjectName(QStringLiteral("spinBoxdelta"));
        spinBoxdelta->setMaximum(360);

        horizontalLayout_18->addWidget(spinBoxdelta);


        verticalLayout->addLayout(horizontalLayout_18);


        verticalLayout_2->addLayout(verticalLayout);


        retranslateUi(Ball);

        QMetaObject::connectSlotsByName(Ball);
    } // setupUi

    void retranslateUi(QWidget *Ball)
    {
        Ball->setWindowTitle(QApplication::translate("Ball", "Form", 0));
        label_24->setText(QApplication::translate("Ball", "x:", 0));
        label_23->setText(QApplication::translate("Ball", "y:", 0));
        label_21->setText(QApplication::translate("Ball", "z:", 0));
        label_22->setText(QApplication::translate("Ball", "r:", 0));
        label_26->setText(QApplication::translate("Ball", "\316\270", 0));
        label_25->setText(QApplication::translate("Ball", "\317\206", 0));
        label_27->setText(QApplication::translate("Ball", "\316\264", 0));
    } // retranslateUi

};

namespace Ui {
    class Ball: public Ui_Ball {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_BALLSETTINGS_H
