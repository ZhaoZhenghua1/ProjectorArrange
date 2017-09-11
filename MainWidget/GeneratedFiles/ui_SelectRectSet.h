/********************************************************************************
** Form generated from reading UI file 'SelectRectSet.ui'
**
** Created by: Qt User Interface Compiler version 5.6.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_SELECTRECTSET_H
#define UI_SELECTRECTSET_H

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
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QVBoxLayout>

QT_BEGIN_NAMESPACE

class Ui_SelectAreaDialog
{
public:
    QVBoxLayout *verticalLayout_2;
    QVBoxLayout *verticalLayout;
    QHBoxLayout *horizontalLayout;
    QLabel *label_13;
    QLineEdit *index;
    QHBoxLayout *horizontalLayout_2;
    QLabel *label;
    QDoubleSpinBox *spinboxL;
    QLabel *label_2;
    QLabel *labelLValue;
    QHBoxLayout *horizontalLayout_3;
    QLabel *label_6;
    QDoubleSpinBox *spinboxR;
    QLabel *label_5;
    QLabel *labelRValue;
    QHBoxLayout *horizontalLayout_4;
    QLabel *label_9;
    QDoubleSpinBox *spinboxT;
    QLabel *label_8;
    QLabel *labelTValue;
    QHBoxLayout *horizontalLayout_5;
    QLabel *label_12;
    QDoubleSpinBox *spinboxB;
    QLabel *label_11;
    QLabel *labelBValue;
    QDialogButtonBox *buttonBox;

    void setupUi(QDialog *SelectAreaDialog)
    {
        if (SelectAreaDialog->objectName().isEmpty())
            SelectAreaDialog->setObjectName(QStringLiteral("SelectAreaDialog"));
        SelectAreaDialog->resize(375, 202);
        SelectAreaDialog->setStyleSheet(QString::fromUtf8("font: 10pt \"\345\276\256\350\275\257\351\233\205\351\273\221\";\n"
"color: rgb(255, 255, 255);"));
        verticalLayout_2 = new QVBoxLayout(SelectAreaDialog);
        verticalLayout_2->setObjectName(QStringLiteral("verticalLayout_2"));
        verticalLayout = new QVBoxLayout();
        verticalLayout->setObjectName(QStringLiteral("verticalLayout"));
        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setObjectName(QStringLiteral("horizontalLayout"));
        label_13 = new QLabel(SelectAreaDialog);
        label_13->setObjectName(QStringLiteral("label_13"));
        label_13->setMinimumSize(QSize(55, 0));
        label_13->setMaximumSize(QSize(40, 16777215));

        horizontalLayout->addWidget(label_13);

        index = new QLineEdit(SelectAreaDialog);
        index->setObjectName(QStringLiteral("index"));

        horizontalLayout->addWidget(index);


        verticalLayout->addLayout(horizontalLayout);

        horizontalLayout_2 = new QHBoxLayout();
        horizontalLayout_2->setObjectName(QStringLiteral("horizontalLayout_2"));
        label = new QLabel(SelectAreaDialog);
        label->setObjectName(QStringLiteral("label"));
        label->setMinimumSize(QSize(55, 0));
        label->setMaximumSize(QSize(1000, 16777215));

        horizontalLayout_2->addWidget(label);

        spinboxL = new QDoubleSpinBox(SelectAreaDialog);
        spinboxL->setObjectName(QStringLiteral("spinboxL"));
        QSizePolicy sizePolicy(QSizePolicy::Minimum, QSizePolicy::Fixed);
        sizePolicy.setHorizontalStretch(1);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(spinboxL->sizePolicy().hasHeightForWidth());
        spinboxL->setSizePolicy(sizePolicy);
        spinboxL->setButtonSymbols(QAbstractSpinBox::NoButtons);
        spinboxL->setDecimals(7);
        spinboxL->setMaximum(100);

        horizontalLayout_2->addWidget(spinboxL);

        label_2 = new QLabel(SelectAreaDialog);
        label_2->setObjectName(QStringLiteral("label_2"));
        label_2->setMinimumSize(QSize(40, 0));
        label_2->setMaximumSize(QSize(100, 16777215));

        horizontalLayout_2->addWidget(label_2);

        labelLValue = new QLabel(SelectAreaDialog);
        labelLValue->setObjectName(QStringLiteral("labelLValue"));
        QSizePolicy sizePolicy1(QSizePolicy::Preferred, QSizePolicy::Preferred);
        sizePolicy1.setHorizontalStretch(1);
        sizePolicy1.setVerticalStretch(0);
        sizePolicy1.setHeightForWidth(labelLValue->sizePolicy().hasHeightForWidth());
        labelLValue->setSizePolicy(sizePolicy1);

        horizontalLayout_2->addWidget(labelLValue);


        verticalLayout->addLayout(horizontalLayout_2);

        horizontalLayout_3 = new QHBoxLayout();
        horizontalLayout_3->setObjectName(QStringLiteral("horizontalLayout_3"));
        label_6 = new QLabel(SelectAreaDialog);
        label_6->setObjectName(QStringLiteral("label_6"));
        label_6->setMinimumSize(QSize(55, 0));
        label_6->setMaximumSize(QSize(1000, 16777215));

        horizontalLayout_3->addWidget(label_6);

        spinboxR = new QDoubleSpinBox(SelectAreaDialog);
        spinboxR->setObjectName(QStringLiteral("spinboxR"));
        sizePolicy.setHeightForWidth(spinboxR->sizePolicy().hasHeightForWidth());
        spinboxR->setSizePolicy(sizePolicy);
        spinboxR->setButtonSymbols(QAbstractSpinBox::NoButtons);
        spinboxR->setDecimals(7);
        spinboxR->setMaximum(100);

        horizontalLayout_3->addWidget(spinboxR);

        label_5 = new QLabel(SelectAreaDialog);
        label_5->setObjectName(QStringLiteral("label_5"));
        label_5->setMinimumSize(QSize(40, 0));
        label_5->setMaximumSize(QSize(100, 16777215));

        horizontalLayout_3->addWidget(label_5);

        labelRValue = new QLabel(SelectAreaDialog);
        labelRValue->setObjectName(QStringLiteral("labelRValue"));
        sizePolicy1.setHeightForWidth(labelRValue->sizePolicy().hasHeightForWidth());
        labelRValue->setSizePolicy(sizePolicy1);

        horizontalLayout_3->addWidget(labelRValue);


        verticalLayout->addLayout(horizontalLayout_3);

        horizontalLayout_4 = new QHBoxLayout();
        horizontalLayout_4->setObjectName(QStringLiteral("horizontalLayout_4"));
        label_9 = new QLabel(SelectAreaDialog);
        label_9->setObjectName(QStringLiteral("label_9"));
        label_9->setMinimumSize(QSize(55, 0));
        label_9->setMaximumSize(QSize(1000, 16777215));

        horizontalLayout_4->addWidget(label_9);

        spinboxT = new QDoubleSpinBox(SelectAreaDialog);
        spinboxT->setObjectName(QStringLiteral("spinboxT"));
        sizePolicy.setHeightForWidth(spinboxT->sizePolicy().hasHeightForWidth());
        spinboxT->setSizePolicy(sizePolicy);
        spinboxT->setButtonSymbols(QAbstractSpinBox::NoButtons);
        spinboxT->setDecimals(7);
        spinboxT->setMaximum(100);

        horizontalLayout_4->addWidget(spinboxT);

        label_8 = new QLabel(SelectAreaDialog);
        label_8->setObjectName(QStringLiteral("label_8"));
        label_8->setMinimumSize(QSize(40, 0));
        label_8->setMaximumSize(QSize(100, 16777215));

        horizontalLayout_4->addWidget(label_8);

        labelTValue = new QLabel(SelectAreaDialog);
        labelTValue->setObjectName(QStringLiteral("labelTValue"));
        sizePolicy1.setHeightForWidth(labelTValue->sizePolicy().hasHeightForWidth());
        labelTValue->setSizePolicy(sizePolicy1);

        horizontalLayout_4->addWidget(labelTValue);


        verticalLayout->addLayout(horizontalLayout_4);

        horizontalLayout_5 = new QHBoxLayout();
        horizontalLayout_5->setObjectName(QStringLiteral("horizontalLayout_5"));
        label_12 = new QLabel(SelectAreaDialog);
        label_12->setObjectName(QStringLiteral("label_12"));
        label_12->setMinimumSize(QSize(55, 0));
        label_12->setMaximumSize(QSize(1000, 16777215));

        horizontalLayout_5->addWidget(label_12);

        spinboxB = new QDoubleSpinBox(SelectAreaDialog);
        spinboxB->setObjectName(QStringLiteral("spinboxB"));
        sizePolicy.setHeightForWidth(spinboxB->sizePolicy().hasHeightForWidth());
        spinboxB->setSizePolicy(sizePolicy);
        spinboxB->setButtonSymbols(QAbstractSpinBox::NoButtons);
        spinboxB->setDecimals(7);
        spinboxB->setMaximum(100);

        horizontalLayout_5->addWidget(spinboxB);

        label_11 = new QLabel(SelectAreaDialog);
        label_11->setObjectName(QStringLiteral("label_11"));
        label_11->setMinimumSize(QSize(40, 0));
        label_11->setMaximumSize(QSize(100, 16777215));

        horizontalLayout_5->addWidget(label_11);

        labelBValue = new QLabel(SelectAreaDialog);
        labelBValue->setObjectName(QStringLiteral("labelBValue"));
        sizePolicy1.setHeightForWidth(labelBValue->sizePolicy().hasHeightForWidth());
        labelBValue->setSizePolicy(sizePolicy1);

        horizontalLayout_5->addWidget(labelBValue);


        verticalLayout->addLayout(horizontalLayout_5);


        verticalLayout_2->addLayout(verticalLayout);

        buttonBox = new QDialogButtonBox(SelectAreaDialog);
        buttonBox->setObjectName(QStringLiteral("buttonBox"));
        buttonBox->setStyleSheet(QStringLiteral(""));
        buttonBox->setOrientation(Qt::Horizontal);
        buttonBox->setStandardButtons(QDialogButtonBox::Cancel|QDialogButtonBox::Ok);

        verticalLayout_2->addWidget(buttonBox);


        retranslateUi(SelectAreaDialog);
        QObject::connect(buttonBox, SIGNAL(accepted()), SelectAreaDialog, SLOT(accept()));
        QObject::connect(buttonBox, SIGNAL(rejected()), SelectAreaDialog, SLOT(reject()));

        QMetaObject::connectSlotsByName(SelectAreaDialog);
    } // setupUi

    void retranslateUi(QDialog *SelectAreaDialog)
    {
        SelectAreaDialog->setWindowTitle(QApplication::translate("SelectAreaDialog", "Area Setting", 0));
        label_13->setText(QApplication::translate("SelectAreaDialog", "Indexing:", 0));
        label->setText(QApplication::translate("SelectAreaDialog", "Left:", 0));
        label_2->setText(QApplication::translate("SelectAreaDialog", "%  Value:", 0));
        labelLValue->setText(QApplication::translate("SelectAreaDialog", "0", 0));
        label_6->setText(QApplication::translate("SelectAreaDialog", "Right:", 0));
        label_5->setText(QApplication::translate("SelectAreaDialog", "%  Value:", 0));
        labelRValue->setText(QApplication::translate("SelectAreaDialog", "0", 0));
        label_9->setText(QApplication::translate("SelectAreaDialog", "Top:", 0));
        label_8->setText(QApplication::translate("SelectAreaDialog", "%  Value:", 0));
        labelTValue->setText(QApplication::translate("SelectAreaDialog", "0", 0));
        label_12->setText(QApplication::translate("SelectAreaDialog", "Bottom:", 0));
        label_11->setText(QApplication::translate("SelectAreaDialog", "%  Value:", 0));
        labelBValue->setText(QApplication::translate("SelectAreaDialog", "0", 0));
    } // retranslateUi

};

namespace Ui {
    class SelectAreaDialog: public Ui_SelectAreaDialog {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_SELECTRECTSET_H
