/********************************************************************************
** Form generated from reading UI file 'projector.ui'
**
** Created by: Qt User Interface Compiler version 5.6.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_PROJECTOR_H
#define UI_PROJECTOR_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QSpinBox>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QTabWidget>
#include <QtWidgets/QToolBar>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_ProjectorClass
{
public:
    QWidget *centralWidget;
    QHBoxLayout *horizontalLayout_2;
    QWidget *widget;
    QVBoxLayout *verticalLayout_4;
    QHBoxLayout *horizontalLayout_5;
    QLabel *label_13;
    QSpinBox *protopleftLength;
    QSpacerItem *horizontalSpacer_9;
    QLabel *label_14;
    QSpinBox *protoprightLength;
    QSpacerItem *horizontalSpacer_10;
    QLabel *label_15;
    QSpinBox *prohorWidth;
    QHBoxLayout *horizontalLayout_4;
    QLabel *label_11;
    QSpinBox *probottomleftLength;
    QSpacerItem *horizontalSpacer_2;
    QLabel *label_2;
    QSpinBox *rotate;
    QSpacerItem *horizontalSpacer_3;
    QLabel *label_12;
    QSpinBox *proverWidth;
    QVBoxLayout *verticalLayout_2;
    QTabWidget *tabWidget;
    QWidget *plane;
    QVBoxLayout *verticalLayout_3;
    QVBoxLayout *verticalLayout;
    QHBoxLayout *horizontalLayout;
    QLabel *label;
    QSpinBox *topleftLength;
    QSpacerItem *horizontalSpacer;
    QHBoxLayout *horizontalLayout_3;
    QLabel *label_3;
    QSpinBox *bottomleftLength;
    QSpacerItem *horizontalSpacer_5;
    QLabel *label_5;
    QSpinBox *bottomrightLength;
    QWidget *cylinder;
    QWidget *ball;
    QMenuBar *menuBar;
    QToolBar *mainToolBar;
    QStatusBar *statusBar;

    void setupUi(QMainWindow *ProjectorClass)
    {
        if (ProjectorClass->objectName().isEmpty())
            ProjectorClass->setObjectName(QStringLiteral("ProjectorClass"));
        ProjectorClass->resize(504, 243);
        centralWidget = new QWidget(ProjectorClass);
        centralWidget->setObjectName(QStringLiteral("centralWidget"));
        horizontalLayout_2 = new QHBoxLayout(centralWidget);
        horizontalLayout_2->setSpacing(6);
        horizontalLayout_2->setContentsMargins(11, 11, 11, 11);
        horizontalLayout_2->setObjectName(QStringLiteral("horizontalLayout_2"));
        widget = new QWidget(centralWidget);
        widget->setObjectName(QStringLiteral("widget"));
        verticalLayout_4 = new QVBoxLayout(widget);
        verticalLayout_4->setSpacing(6);
        verticalLayout_4->setContentsMargins(11, 11, 11, 11);
        verticalLayout_4->setObjectName(QStringLiteral("verticalLayout_4"));
        horizontalLayout_5 = new QHBoxLayout();
        horizontalLayout_5->setSpacing(6);
        horizontalLayout_5->setObjectName(QStringLiteral("horizontalLayout_5"));
        label_13 = new QLabel(widget);
        label_13->setObjectName(QStringLiteral("label_13"));

        horizontalLayout_5->addWidget(label_13);

        protopleftLength = new QSpinBox(widget);
        protopleftLength->setObjectName(QStringLiteral("protopleftLength"));
        protopleftLength->setMinimum(1);
        protopleftLength->setMaximum(10000000);
        protopleftLength->setValue(1580);

        horizontalLayout_5->addWidget(protopleftLength);

        horizontalSpacer_9 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_5->addItem(horizontalSpacer_9);

        label_14 = new QLabel(widget);
        label_14->setObjectName(QStringLiteral("label_14"));

        horizontalLayout_5->addWidget(label_14);

        protoprightLength = new QSpinBox(widget);
        protoprightLength->setObjectName(QStringLiteral("protoprightLength"));
        protoprightLength->setMinimum(1);
        protoprightLength->setMaximum(10000000);
        protoprightLength->setValue(1570);

        horizontalLayout_5->addWidget(protoprightLength);

        horizontalSpacer_10 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_5->addItem(horizontalSpacer_10);

        label_15 = new QLabel(widget);
        label_15->setObjectName(QStringLiteral("label_15"));

        horizontalLayout_5->addWidget(label_15);

        prohorWidth = new QSpinBox(widget);
        prohorWidth->setObjectName(QStringLiteral("prohorWidth"));
        prohorWidth->setMinimum(1);
        prohorWidth->setMaximum(10000000);
        prohorWidth->setValue(760);

        horizontalLayout_5->addWidget(prohorWidth);


        verticalLayout_4->addLayout(horizontalLayout_5);

        horizontalLayout_4 = new QHBoxLayout();
        horizontalLayout_4->setSpacing(6);
        horizontalLayout_4->setObjectName(QStringLiteral("horizontalLayout_4"));
        label_11 = new QLabel(widget);
        label_11->setObjectName(QStringLiteral("label_11"));

        horizontalLayout_4->addWidget(label_11);

        probottomleftLength = new QSpinBox(widget);
        probottomleftLength->setObjectName(QStringLiteral("probottomleftLength"));
        probottomleftLength->setMinimum(1);
        probottomleftLength->setMaximum(10000000);
        probottomleftLength->setValue(1440);

        horizontalLayout_4->addWidget(probottomleftLength);

        horizontalSpacer_2 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_4->addItem(horizontalSpacer_2);

        label_2 = new QLabel(widget);
        label_2->setObjectName(QStringLiteral("label_2"));

        horizontalLayout_4->addWidget(label_2);

        rotate = new QSpinBox(widget);
        rotate->setObjectName(QStringLiteral("rotate"));
        rotate->setMinimum(-89);
        rotate->setMaximum(89);
        rotate->setValue(0);

        horizontalLayout_4->addWidget(rotate);

        horizontalSpacer_3 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_4->addItem(horizontalSpacer_3);

        label_12 = new QLabel(widget);
        label_12->setObjectName(QStringLiteral("label_12"));

        horizontalLayout_4->addWidget(label_12);

        proverWidth = new QSpinBox(widget);
        proverWidth->setObjectName(QStringLiteral("proverWidth"));
        proverWidth->setMinimum(1);
        proverWidth->setMaximum(10000000);
        proverWidth->setValue(572);

        horizontalLayout_4->addWidget(proverWidth);


        verticalLayout_4->addLayout(horizontalLayout_4);

        verticalLayout_2 = new QVBoxLayout();
        verticalLayout_2->setSpacing(6);
        verticalLayout_2->setObjectName(QStringLiteral("verticalLayout_2"));
        tabWidget = new QTabWidget(widget);
        tabWidget->setObjectName(QStringLiteral("tabWidget"));
        plane = new QWidget();
        plane->setObjectName(QStringLiteral("plane"));
        verticalLayout_3 = new QVBoxLayout(plane);
        verticalLayout_3->setSpacing(6);
        verticalLayout_3->setContentsMargins(11, 11, 11, 11);
        verticalLayout_3->setObjectName(QStringLiteral("verticalLayout_3"));
        verticalLayout = new QVBoxLayout();
        verticalLayout->setSpacing(6);
        verticalLayout->setObjectName(QStringLiteral("verticalLayout"));
        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setSpacing(6);
        horizontalLayout->setObjectName(QStringLiteral("horizontalLayout"));
        label = new QLabel(plane);
        label->setObjectName(QStringLiteral("label"));

        horizontalLayout->addWidget(label);

        topleftLength = new QSpinBox(plane);
        topleftLength->setObjectName(QStringLiteral("topleftLength"));
        topleftLength->setMinimum(1);
        topleftLength->setMaximum(10000000);
        topleftLength->setValue(1500);

        horizontalLayout->addWidget(topleftLength);

        horizontalSpacer = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout->addItem(horizontalSpacer);


        verticalLayout->addLayout(horizontalLayout);

        horizontalLayout_3 = new QHBoxLayout();
        horizontalLayout_3->setSpacing(6);
        horizontalLayout_3->setObjectName(QStringLiteral("horizontalLayout_3"));
        label_3 = new QLabel(plane);
        label_3->setObjectName(QStringLiteral("label_3"));

        horizontalLayout_3->addWidget(label_3);

        bottomleftLength = new QSpinBox(plane);
        bottomleftLength->setObjectName(QStringLiteral("bottomleftLength"));
        bottomleftLength->setMinimum(1);
        bottomleftLength->setMaximum(10000000);
        bottomleftLength->setValue(1380);

        horizontalLayout_3->addWidget(bottomleftLength);

        horizontalSpacer_5 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_3->addItem(horizontalSpacer_5);

        label_5 = new QLabel(plane);
        label_5->setObjectName(QStringLiteral("label_5"));

        horizontalLayout_3->addWidget(label_5);

        bottomrightLength = new QSpinBox(plane);
        bottomrightLength->setObjectName(QStringLiteral("bottomrightLength"));
        bottomrightLength->setMinimum(1);
        bottomrightLength->setMaximum(10000000);
        bottomrightLength->setValue(1870);

        horizontalLayout_3->addWidget(bottomrightLength);


        verticalLayout->addLayout(horizontalLayout_3);


        verticalLayout_3->addLayout(verticalLayout);

        tabWidget->addTab(plane, QString());
        cylinder = new QWidget();
        cylinder->setObjectName(QStringLiteral("cylinder"));
        tabWidget->addTab(cylinder, QString());
        ball = new QWidget();
        ball->setObjectName(QStringLiteral("ball"));
        tabWidget->addTab(ball, QString());

        verticalLayout_2->addWidget(tabWidget);


        verticalLayout_4->addLayout(verticalLayout_2);


        horizontalLayout_2->addWidget(widget);

        ProjectorClass->setCentralWidget(centralWidget);
        menuBar = new QMenuBar(ProjectorClass);
        menuBar->setObjectName(QStringLiteral("menuBar"));
        menuBar->setGeometry(QRect(0, 0, 504, 21));
        ProjectorClass->setMenuBar(menuBar);
        mainToolBar = new QToolBar(ProjectorClass);
        mainToolBar->setObjectName(QStringLiteral("mainToolBar"));
        ProjectorClass->addToolBar(Qt::TopToolBarArea, mainToolBar);
        statusBar = new QStatusBar(ProjectorClass);
        statusBar->setObjectName(QStringLiteral("statusBar"));
        ProjectorClass->setStatusBar(statusBar);

        retranslateUi(ProjectorClass);

        tabWidget->setCurrentIndex(0);


        QMetaObject::connectSlotsByName(ProjectorClass);
    } // setupUi

    void retranslateUi(QMainWindow *ProjectorClass)
    {
        ProjectorClass->setWindowTitle(QApplication::translate("ProjectorClass", "Projector", 0));
        label_13->setText(QApplication::translate("ProjectorClass", "\345\267\246\344\270\212\344\276\247\351\225\277\345\272\246", 0));
        label_14->setText(QApplication::translate("ProjectorClass", "\345\217\263\344\270\212\344\276\247\351\225\277\345\272\246", 0));
        label_15->setText(QApplication::translate("ProjectorClass", "\346\260\264\345\271\263\346\212\225\345\275\261\345\256\275\345\272\246", 0));
        label_11->setText(QApplication::translate("ProjectorClass", "\345\267\246\344\270\213\344\276\247\351\225\277\345\272\246", 0));
        label_2->setText(QApplication::translate("ProjectorClass", "\347\273\225Z\346\227\213\350\275\254", 0));
        label_12->setText(QApplication::translate("ProjectorClass", "\345\236\202\347\233\264\346\212\225\345\275\261\345\256\275\345\272\246", 0));
        label->setText(QApplication::translate("ProjectorClass", "\345\267\246\344\270\212\344\276\247\351\225\277\345\272\246", 0));
        label_3->setText(QApplication::translate("ProjectorClass", "\345\267\246\344\270\213\344\276\247\351\225\277\345\272\246", 0));
        label_5->setText(QApplication::translate("ProjectorClass", "\345\217\263\344\270\213\344\276\247\351\225\277\345\272\246", 0));
        tabWidget->setTabText(tabWidget->indexOf(plane), QApplication::translate("ProjectorClass", "\345\271\263\351\235\242", 0));
        tabWidget->setTabText(tabWidget->indexOf(cylinder), QApplication::translate("ProjectorClass", "\346\237\261\351\235\242", 0));
        tabWidget->setTabText(tabWidget->indexOf(ball), QApplication::translate("ProjectorClass", "\347\220\203\351\235\242", 0));
    } // retranslateUi

};

namespace Ui {
    class ProjectorClass: public Ui_ProjectorClass {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_PROJECTOR_H
