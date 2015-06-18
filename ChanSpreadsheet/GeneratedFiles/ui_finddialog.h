/********************************************************************************
** Form generated from reading UI file 'finddialog.ui'
**
** Created by: Qt User Interface Compiler version 5.4.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_FINDDIALOG_H
#define UI_FINDDIALOG_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QCheckBox>
#include <QtWidgets/QDialog>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_findDialogClass
{
public:
    QWidget *widget;
    QVBoxLayout *verticalLayout;
    QPushButton *m_findPushButton;
    QSpacerItem *verticalSpacer;
    QPushButton *m_closePushButton;
    QWidget *widget1;
    QHBoxLayout *horizontalLayout;
    QLabel *m_findWhatLable;
    QLineEdit *m_findWhatLineEdit;
    QWidget *widget2;
    QVBoxLayout *verticalLayout_2;
    QCheckBox *m_mathcCaseCheckBox;
    QCheckBox *m_searchBackwardCheckBox;

    void setupUi(QDialog *findDialogClass)
    {
        if (findDialogClass->objectName().isEmpty())
            findDialogClass->setObjectName(QStringLiteral("findDialogClass"));
        findDialogClass->resize(529, 168);
        widget = new QWidget(findDialogClass);
        widget->setObjectName(QStringLiteral("widget"));
        widget->setGeometry(QRect(370, 40, 84, 81));
        verticalLayout = new QVBoxLayout(widget);
        verticalLayout->setSpacing(6);
        verticalLayout->setContentsMargins(11, 11, 11, 11);
        verticalLayout->setObjectName(QStringLiteral("verticalLayout"));
        verticalLayout->setContentsMargins(0, 0, 0, 0);
        m_findPushButton = new QPushButton(widget);
        m_findPushButton->setObjectName(QStringLiteral("m_findPushButton"));
        m_findPushButton->setEnabled(false);
        m_findPushButton->setAutoDefault(false);
        m_findPushButton->setDefault(true);

        verticalLayout->addWidget(m_findPushButton);

        verticalSpacer = new QSpacerItem(20, 28, QSizePolicy::Minimum, QSizePolicy::Expanding);

        verticalLayout->addItem(verticalSpacer);

        m_closePushButton = new QPushButton(widget);
        m_closePushButton->setObjectName(QStringLiteral("m_closePushButton"));

        verticalLayout->addWidget(m_closePushButton);

        widget1 = new QWidget(findDialogClass);
        widget1->setObjectName(QStringLiteral("widget1"));
        widget1->setGeometry(QRect(70, 40, 281, 22));
        horizontalLayout = new QHBoxLayout(widget1);
        horizontalLayout->setSpacing(6);
        horizontalLayout->setContentsMargins(11, 11, 11, 11);
        horizontalLayout->setObjectName(QStringLiteral("horizontalLayout"));
        horizontalLayout->setContentsMargins(0, 0, 0, 0);
        m_findWhatLable = new QLabel(widget1);
        m_findWhatLable->setObjectName(QStringLiteral("m_findWhatLable"));

        horizontalLayout->addWidget(m_findWhatLable);

        m_findWhatLineEdit = new QLineEdit(widget1);
        m_findWhatLineEdit->setObjectName(QStringLiteral("m_findWhatLineEdit"));

        horizontalLayout->addWidget(m_findWhatLineEdit);

        widget2 = new QWidget(findDialogClass);
        widget2->setObjectName(QStringLiteral("widget2"));
        widget2->setGeometry(QRect(70, 80, 130, 42));
        verticalLayout_2 = new QVBoxLayout(widget2);
        verticalLayout_2->setSpacing(6);
        verticalLayout_2->setContentsMargins(11, 11, 11, 11);
        verticalLayout_2->setObjectName(QStringLiteral("verticalLayout_2"));
        verticalLayout_2->setContentsMargins(0, 0, 0, 0);
        m_mathcCaseCheckBox = new QCheckBox(widget2);
        m_mathcCaseCheckBox->setObjectName(QStringLiteral("m_mathcCaseCheckBox"));
        m_mathcCaseCheckBox->setChecked(true);

        verticalLayout_2->addWidget(m_mathcCaseCheckBox);

        m_searchBackwardCheckBox = new QCheckBox(widget2);
        m_searchBackwardCheckBox->setObjectName(QStringLiteral("m_searchBackwardCheckBox"));

        verticalLayout_2->addWidget(m_searchBackwardCheckBox);

#ifndef QT_NO_SHORTCUT
        m_findWhatLable->setBuddy(m_findWhatLineEdit);
#endif // QT_NO_SHORTCUT

        retranslateUi(findDialogClass);
        QObject::connect(m_closePushButton, SIGNAL(clicked()), findDialogClass, SLOT(reject()));

        QMetaObject::connectSlotsByName(findDialogClass);
    } // setupUi

    void retranslateUi(QDialog *findDialogClass)
    {
        findDialogClass->setWindowTitle(QApplication::translate("findDialogClass", "findDialog", 0));
        m_findPushButton->setText(QApplication::translate("findDialogClass", "&Find", 0));
        m_closePushButton->setText(QApplication::translate("findDialogClass", "Close", 0));
        m_findWhatLable->setText(QApplication::translate("findDialogClass", "Find &What", 0));
        m_mathcCaseCheckBox->setText(QApplication::translate("findDialogClass", "Match &Case", 0));
        m_searchBackwardCheckBox->setText(QApplication::translate("findDialogClass", "Search &Backward", 0));
    } // retranslateUi

};

namespace Ui {
    class findDialogClass: public Ui_findDialogClass {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_FINDDIALOG_H
