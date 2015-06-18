/********************************************************************************
** Form generated from reading UI file 'gotocelldialog.ui'
**
** Created by: Qt User Interface Compiler version 5.4.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_GOTOCELLDIALOG_H
#define UI_GOTOCELLDIALOG_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QDialog>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_goToCellDialogClass
{
public:
    QWidget *layoutWidget;
    QHBoxLayout *horizontalLayout;
    QLabel *m_cellLocationTextLabel;
    QLineEdit *m_cellLocationLineEdit;
    QWidget *layoutWidget1;
    QHBoxLayout *horizontalLayout_2;
    QPushButton *m_okPushButton;
    QSpacerItem *horizontalSpacer;
    QPushButton *m_cancelPushButton;

    void setupUi(QDialog *goToCellDialogClass)
    {
        if (goToCellDialogClass->objectName().isEmpty())
            goToCellDialogClass->setObjectName(QStringLiteral("goToCellDialogClass"));
        goToCellDialogClass->resize(520, 158);
        layoutWidget = new QWidget(goToCellDialogClass);
        layoutWidget->setObjectName(QStringLiteral("layoutWidget"));
        layoutWidget->setGeometry(QRect(70, 40, 371, 22));
        horizontalLayout = new QHBoxLayout(layoutWidget);
        horizontalLayout->setSpacing(6);
        horizontalLayout->setContentsMargins(11, 11, 11, 11);
        horizontalLayout->setObjectName(QStringLiteral("horizontalLayout"));
        horizontalLayout->setContentsMargins(0, 0, 0, 0);
        m_cellLocationTextLabel = new QLabel(layoutWidget);
        m_cellLocationTextLabel->setObjectName(QStringLiteral("m_cellLocationTextLabel"));

        horizontalLayout->addWidget(m_cellLocationTextLabel);

        m_cellLocationLineEdit = new QLineEdit(layoutWidget);
        m_cellLocationLineEdit->setObjectName(QStringLiteral("m_cellLocationLineEdit"));

        horizontalLayout->addWidget(m_cellLocationLineEdit);

        layoutWidget1 = new QWidget(goToCellDialogClass);
        layoutWidget1->setObjectName(QStringLiteral("layoutWidget1"));
        layoutWidget1->setGeometry(QRect(130, 100, 241, 27));
        horizontalLayout_2 = new QHBoxLayout(layoutWidget1);
        horizontalLayout_2->setSpacing(6);
        horizontalLayout_2->setContentsMargins(11, 11, 11, 11);
        horizontalLayout_2->setObjectName(QStringLiteral("horizontalLayout_2"));
        horizontalLayout_2->setContentsMargins(0, 0, 0, 0);
        m_okPushButton = new QPushButton(layoutWidget1);
        m_okPushButton->setObjectName(QStringLiteral("m_okPushButton"));
        m_okPushButton->setEnabled(false);
        m_okPushButton->setAutoDefault(false);
        m_okPushButton->setDefault(true);

        horizontalLayout_2->addWidget(m_okPushButton);

        horizontalSpacer = new QSpacerItem(48, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_2->addItem(horizontalSpacer);

        m_cancelPushButton = new QPushButton(layoutWidget1);
        m_cancelPushButton->setObjectName(QStringLiteral("m_cancelPushButton"));

        horizontalLayout_2->addWidget(m_cancelPushButton);

#ifndef QT_NO_SHORTCUT
        m_cellLocationTextLabel->setBuddy(m_cellLocationLineEdit);
#endif // QT_NO_SHORTCUT

        retranslateUi(goToCellDialogClass);
        QObject::connect(m_cancelPushButton, SIGNAL(clicked()), goToCellDialogClass, SLOT(reject()));
        QObject::connect(m_okPushButton, SIGNAL(clicked()), goToCellDialogClass, SLOT(accept()));

        QMetaObject::connectSlotsByName(goToCellDialogClass);
    } // setupUi

    void retranslateUi(QDialog *goToCellDialogClass)
    {
        goToCellDialogClass->setWindowTitle(QApplication::translate("goToCellDialogClass", "goToCellDialog", 0));
        m_cellLocationTextLabel->setText(QApplication::translate("goToCellDialogClass", "&Cell Location", 0));
        m_okPushButton->setText(QApplication::translate("goToCellDialogClass", "Ok", 0));
        m_cancelPushButton->setText(QApplication::translate("goToCellDialogClass", "Cancel", 0));
    } // retranslateUi

};

namespace Ui {
    class goToCellDialogClass: public Ui_goToCellDialogClass {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_GOTOCELLDIALOG_H
