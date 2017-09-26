/********************************************************************************
** Form generated from reading UI file 'ratio.ui'
**
** Created by: Qt User Interface Compiler version 5.6.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_RATIO_H
#define UI_RATIO_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QDialog>
#include <QtWidgets/QDialogButtonBox>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QSpinBox>
#include <QtWidgets/QVBoxLayout>

QT_BEGIN_NAMESPACE

class Ui_Dialog
{
public:
    QVBoxLayout *verticalLayout_2;
    QVBoxLayout *verticalLayout;
    QHBoxLayout *horizontalLayout_2;
    QLabel *label;
    QSpinBox *spinBoxx;
    QLabel *label_2;
    QSpinBox *spinBoxy;
    QDialogButtonBox *buttonBox;

    void setupUi(QDialog *Dialog)
    {
        if (Dialog->objectName().isEmpty())
            Dialog->setObjectName(QStringLiteral("Dialog"));
        Dialog->resize(343, 71);
        Dialog->setStyleSheet(QStringLiteral("color: rgb(255, 255, 255);"));
        verticalLayout_2 = new QVBoxLayout(Dialog);
        verticalLayout_2->setObjectName(QStringLiteral("verticalLayout_2"));
        verticalLayout = new QVBoxLayout();
        verticalLayout->setObjectName(QStringLiteral("verticalLayout"));
        horizontalLayout_2 = new QHBoxLayout();
        horizontalLayout_2->setObjectName(QStringLiteral("horizontalLayout_2"));
        label = new QLabel(Dialog);
        label->setObjectName(QStringLiteral("label"));
        label->setMaximumSize(QSize(65, 16777215));

        horizontalLayout_2->addWidget(label);

        spinBoxx = new QSpinBox(Dialog);
        spinBoxx->setObjectName(QStringLiteral("spinBoxx"));
        spinBoxx->setMinimum(10);
        spinBoxx->setMaximum(999999);
        spinBoxx->setValue(6000);

        horizontalLayout_2->addWidget(spinBoxx);

        label_2 = new QLabel(Dialog);
        label_2->setObjectName(QStringLiteral("label_2"));
        label_2->setMaximumSize(QSize(8, 16777215));

        horizontalLayout_2->addWidget(label_2);

        spinBoxy = new QSpinBox(Dialog);
        spinBoxy->setObjectName(QStringLiteral("spinBoxy"));
        spinBoxy->setMinimum(10);
        spinBoxy->setMaximum(999999);
        spinBoxy->setValue(2000);

        horizontalLayout_2->addWidget(spinBoxy);


        verticalLayout->addLayout(horizontalLayout_2);

        buttonBox = new QDialogButtonBox(Dialog);
        buttonBox->setObjectName(QStringLiteral("buttonBox"));
        buttonBox->setOrientation(Qt::Horizontal);
        buttonBox->setStandardButtons(QDialogButtonBox::Cancel|QDialogButtonBox::Ok);

        verticalLayout->addWidget(buttonBox);


        verticalLayout_2->addLayout(verticalLayout);


        retranslateUi(Dialog);
        QObject::connect(buttonBox, SIGNAL(accepted()), Dialog, SLOT(accept()));
        QObject::connect(buttonBox, SIGNAL(rejected()), Dialog, SLOT(reject()));

        QMetaObject::connectSlotsByName(Dialog);
    } // setupUi

    void retranslateUi(QDialog *Dialog)
    {
        Dialog->setWindowTitle(QApplication::translate("Dialog", "Screen Size Setting", 0));
        label->setText(QApplication::translate("Dialog", "Screen Size:", 0));
        label_2->setText(QApplication::translate("Dialog", "x", 0));
    } // retranslateUi

};

namespace Ui {
    class Dialog: public Ui_Dialog {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_RATIO_H
