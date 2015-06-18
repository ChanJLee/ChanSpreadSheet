/********************************************************************************
** Form generated from reading UI file 'chanspreadsheet.ui'
**
** Created by: Qt User Interface Compiler version 5.4.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_CHANSPREADSHEET_H
#define UI_CHANSPREADSHEET_H

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

class Ui_ChanSpreadsheetClass
{
public:
    QMenuBar *menuBar;
    QToolBar *mainToolBar;
    QWidget *centralWidget;
    QStatusBar *statusBar;

    void setupUi(QMainWindow *ChanSpreadsheetClass)
    {
        if (ChanSpreadsheetClass->objectName().isEmpty())
            ChanSpreadsheetClass->setObjectName(QStringLiteral("ChanSpreadsheetClass"));
        ChanSpreadsheetClass->resize(600, 400);
        menuBar = new QMenuBar(ChanSpreadsheetClass);
        menuBar->setObjectName(QStringLiteral("menuBar"));
        ChanSpreadsheetClass->setMenuBar(menuBar);
        mainToolBar = new QToolBar(ChanSpreadsheetClass);
        mainToolBar->setObjectName(QStringLiteral("mainToolBar"));
        ChanSpreadsheetClass->addToolBar(mainToolBar);
        centralWidget = new QWidget(ChanSpreadsheetClass);
        centralWidget->setObjectName(QStringLiteral("centralWidget"));
        ChanSpreadsheetClass->setCentralWidget(centralWidget);
        statusBar = new QStatusBar(ChanSpreadsheetClass);
        statusBar->setObjectName(QStringLiteral("statusBar"));
        ChanSpreadsheetClass->setStatusBar(statusBar);

        retranslateUi(ChanSpreadsheetClass);

        QMetaObject::connectSlotsByName(ChanSpreadsheetClass);
    } // setupUi

    void retranslateUi(QMainWindow *ChanSpreadsheetClass)
    {
        ChanSpreadsheetClass->setWindowTitle(QApplication::translate("ChanSpreadsheetClass", "ChanSpreadsheet", 0));
    } // retranslateUi

};

namespace Ui {
    class ChanSpreadsheetClass: public Ui_ChanSpreadsheetClass {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_CHANSPREADSHEET_H
