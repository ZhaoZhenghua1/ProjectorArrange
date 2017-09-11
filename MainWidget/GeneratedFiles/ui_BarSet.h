/********************************************************************************
** Form generated from reading UI file 'BarSet.ui'
**
** Created by: Qt User Interface Compiler version 5.6.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_BARSET_H
#define UI_BARSET_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QDialog>
#include <QtWidgets/QDialogButtonBox>
#include <QtWidgets/QDoubleSpinBox>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QVBoxLayout>

QT_BEGIN_NAMESPACE

class Ui_BarDialog
{
public:
    QVBoxLayout *verticalLayout;
    QHBoxLayout *horizontalLayout;
    QLabel *label;
    QDoubleSpinBox *spinboxV;
    QLabel *label_2;
    QLabel *labelV;
    QDialogButtonBox *buttonBox;

    void setupUi(QDialog *BarDialog)
    {
        if (BarDialog->objectName().isEmpty())
            BarDialog->setObjectName(QStringLiteral("BarDialog"));
        BarDialog->resize(255, 76);
        BarDialog->setStyleSheet(QString::fromUtf8("font: 10pt \"\345\276\256\350\275\257\351\233\205\351\273\221\";\n"
"color: rgb(255, 255, 255);"));
        verticalLayout = new QVBoxLayout(BarDialog);
        verticalLayout->setObjectName(QStringLiteral("verticalLayout"));
        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setObjectName(QStringLiteral("horizontalLayout"));
        label = new QLabel(BarDialog);
        label->setObjectName(QStringLiteral("label"));
        label->setMaximumSize(QSize(15, 16777215));

        horizontalLayout->addWidget(label);

        spinboxV = new QDoubleSpinBox(BarDialog);
        spinboxV->setObjectName(QStringLiteral("spinboxV"));
        spinboxV->setButtonSymbols(QAbstractSpinBox::NoButtons);
        spinboxV->setDecimals(7);
        spinboxV->setMaximum(100);

        horizontalLayout->addWidget(spinboxV);

        label_2 = new QLabel(BarDialog);
        label_2->setObjectName(QStringLiteral("label_2"));
        label_2->setMaximumSize(QSize(100, 16777215));

        horizontalLayout->addWidget(label_2);

        labelV = new QLabel(BarDialog);
        labelV->setObjectName(QStringLiteral("labelV"));

        horizontalLayout->addWidget(labelV);


        verticalLayout->addLayout(horizontalLayout);

        buttonBox = new QDialogButtonBox(BarDialog);
        buttonBox->setObjectName(QStringLiteral("buttonBox"));
        buttonBox->setOrientation(Qt::Horizontal);
        buttonBox->setStandardButtons(QDialogButtonBox::Cancel|QDialogButtonBox::Ok);

        verticalLayout->addWidget(buttonBox);


        retranslateUi(BarDialog);
        QObject::connect(buttonBox, SIGNAL(accepted()), BarDialog, SLOT(accept()));
        QObject::connect(buttonBox, SIGNAL(rejected()), BarDialog, SLOT(reject()));

        QMetaObject::connectSlotsByName(BarDialog);
    } // setupUi

    void retranslateUi(QDialog *BarDialog)
    {
        BarDialog->setWindowTitle(QApplication::translate("BarDialog", "Reference Line Setting", 0));
        label->setText(QApplication::translate("BarDialog", "V:", 0));
        label_2->setText(QApplication::translate("BarDialog", "% Value:", 0));
        labelV->setText(QApplication::translate("BarDialog", "0", 0));
    } // retranslateUi

};

namespace Ui {
    class BarDialog: public Ui_BarDialog {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_BARSET_H
