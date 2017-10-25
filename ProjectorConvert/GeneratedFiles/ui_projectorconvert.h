/********************************************************************************
** Form generated from reading UI file 'projectorconvert.ui'
**
** Created by: Qt User Interface Compiler version 5.6.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_PROJECTORCONVERT_H
#define UI_PROJECTORCONVERT_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QToolBar>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_ProjectorConvertClass
{
public:
    QMenuBar *menuBar;
    QToolBar *mainToolBar;
    QWidget *centralWidget;
    QStatusBar *statusBar;

    void setupUi(QMainWindow *ProjectorConvertClass)
    {
        if (ProjectorConvertClass->objectName().isEmpty())
            ProjectorConvertClass->setObjectName(QStringLiteral("ProjectorConvertClass"));
        ProjectorConvertClass->resize(600, 400);
        menuBar = new QMenuBar(ProjectorConvertClass);
        menuBar->setObjectName(QStringLiteral("menuBar"));
        ProjectorConvertClass->setMenuBar(menuBar);
        mainToolBar = new QToolBar(ProjectorConvertClass);
        mainToolBar->setObjectName(QStringLiteral("mainToolBar"));
        ProjectorConvertClass->addToolBar(mainToolBar);
        centralWidget = new QWidget(ProjectorConvertClass);
        centralWidget->setObjectName(QStringLiteral("centralWidget"));
        ProjectorConvertClass->setCentralWidget(centralWidget);
        statusBar = new QStatusBar(ProjectorConvertClass);
        statusBar->setObjectName(QStringLiteral("statusBar"));
        ProjectorConvertClass->setStatusBar(statusBar);

        retranslateUi(ProjectorConvertClass);

        QMetaObject::connectSlotsByName(ProjectorConvertClass);
    } // setupUi

    void retranslateUi(QMainWindow *ProjectorConvertClass)
    {
        ProjectorConvertClass->setWindowTitle(QApplication::translate("ProjectorConvertClass", "ProjectorConvert", 0));
    } // retranslateUi

};

namespace Ui {
    class ProjectorConvertClass: public Ui_ProjectorConvertClass {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_PROJECTORCONVERT_H
