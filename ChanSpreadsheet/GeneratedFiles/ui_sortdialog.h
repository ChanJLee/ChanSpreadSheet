/********************************************************************************
** Form generated from reading UI file 'sortdialog.ui'
**
** Created by: Qt User Interface Compiler version 5.4.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_SORTDIALOG_H
#define UI_SORTDIALOG_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QDialog>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QGroupBox>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_sortDialogClass
{
public:
    QGroupBox *m_primaryKeyGroupBox;
    QGridLayout *gridLayout;
    QLabel *m_primaryKeyColumnLabel;
    QComboBox *m_primaryKeyColumnComboBox;
    QSpacerItem *horizontalSpacer;
    QLabel *m_primaryKeyOrderLabel;
    QComboBox *m_primaryKeyOrderComboBox;
    QSpacerItem *horizontalSpacer_4;
    QGroupBox *m_secondaryKeyGroupBox;
    QGridLayout *gridLayout_2;
    QLabel *m_primaryKeyColumnLabel_2;
    QComboBox *m_secondaryKeyColumnComboBox;
    QSpacerItem *horizontalSpacer_2;
    QLabel *m_primaryKeyOrderLabel_2;
    QComboBox *m_secondaryKeyOrderComboBox;
    QSpacerItem *horizontalSpacer_5;
    QGroupBox *m_tertiaryKeyGroupBox;
    QGridLayout *gridLayout_3;
    QLabel *m_primaryKeyColumnLabel_3;
    QComboBox *m_tertiaryKeyColumnComboBox;
    QSpacerItem *horizontalSpacer_3;
    QLabel *m_primaryKeyOrderLabel_3;
    QComboBox *m_tertiaryKeyOrderComboBox;
    QSpacerItem *horizontalSpacer_6;
    QWidget *widget;
    QVBoxLayout *verticalLayout;
    QPushButton *m_okPushButton;
    QPushButton *m_cancelPushButton;
    QSpacerItem *verticalSpacer;
    QPushButton *m_morePushButton;

    void setupUi(QDialog *sortDialogClass)
    {
        if (sortDialogClass->objectName().isEmpty())
            sortDialogClass->setObjectName(QStringLiteral("sortDialogClass"));
        sortDialogClass->resize(448, 519);
        m_primaryKeyGroupBox = new QGroupBox(sortDialogClass);
        m_primaryKeyGroupBox->setObjectName(QStringLiteral("m_primaryKeyGroupBox"));
        m_primaryKeyGroupBox->setGeometry(QRect(40, 50, 211, 111));
        gridLayout = new QGridLayout(m_primaryKeyGroupBox);
        gridLayout->setSpacing(6);
        gridLayout->setContentsMargins(11, 11, 11, 11);
        gridLayout->setObjectName(QStringLiteral("gridLayout"));
        m_primaryKeyColumnLabel = new QLabel(m_primaryKeyGroupBox);
        m_primaryKeyColumnLabel->setObjectName(QStringLiteral("m_primaryKeyColumnLabel"));

        gridLayout->addWidget(m_primaryKeyColumnLabel, 0, 0, 1, 1);

        m_primaryKeyColumnComboBox = new QComboBox(m_primaryKeyGroupBox);
        m_primaryKeyColumnComboBox->setObjectName(QStringLiteral("m_primaryKeyColumnComboBox"));

        gridLayout->addWidget(m_primaryKeyColumnComboBox, 0, 1, 1, 1);

        horizontalSpacer = new QSpacerItem(84, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        gridLayout->addItem(horizontalSpacer, 0, 2, 1, 2);

        m_primaryKeyOrderLabel = new QLabel(m_primaryKeyGroupBox);
        m_primaryKeyOrderLabel->setObjectName(QStringLiteral("m_primaryKeyOrderLabel"));

        gridLayout->addWidget(m_primaryKeyOrderLabel, 1, 0, 1, 1);

        m_primaryKeyOrderComboBox = new QComboBox(m_primaryKeyGroupBox);
        m_primaryKeyOrderComboBox->setObjectName(QStringLiteral("m_primaryKeyOrderComboBox"));

        gridLayout->addWidget(m_primaryKeyOrderComboBox, 1, 1, 1, 2);

        horizontalSpacer_4 = new QSpacerItem(47, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        gridLayout->addItem(horizontalSpacer_4, 1, 3, 1, 1);

        m_secondaryKeyGroupBox = new QGroupBox(sortDialogClass);
        m_secondaryKeyGroupBox->setObjectName(QStringLiteral("m_secondaryKeyGroupBox"));
        m_secondaryKeyGroupBox->setGeometry(QRect(40, 210, 211, 111));
        gridLayout_2 = new QGridLayout(m_secondaryKeyGroupBox);
        gridLayout_2->setSpacing(6);
        gridLayout_2->setContentsMargins(11, 11, 11, 11);
        gridLayout_2->setObjectName(QStringLiteral("gridLayout_2"));
        m_primaryKeyColumnLabel_2 = new QLabel(m_secondaryKeyGroupBox);
        m_primaryKeyColumnLabel_2->setObjectName(QStringLiteral("m_primaryKeyColumnLabel_2"));

        gridLayout_2->addWidget(m_primaryKeyColumnLabel_2, 0, 0, 1, 1);

        m_secondaryKeyColumnComboBox = new QComboBox(m_secondaryKeyGroupBox);
        m_secondaryKeyColumnComboBox->setObjectName(QStringLiteral("m_secondaryKeyColumnComboBox"));

        gridLayout_2->addWidget(m_secondaryKeyColumnComboBox, 0, 1, 1, 1);

        horizontalSpacer_2 = new QSpacerItem(84, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        gridLayout_2->addItem(horizontalSpacer_2, 0, 2, 1, 2);

        m_primaryKeyOrderLabel_2 = new QLabel(m_secondaryKeyGroupBox);
        m_primaryKeyOrderLabel_2->setObjectName(QStringLiteral("m_primaryKeyOrderLabel_2"));

        gridLayout_2->addWidget(m_primaryKeyOrderLabel_2, 1, 0, 1, 1);

        m_secondaryKeyOrderComboBox = new QComboBox(m_secondaryKeyGroupBox);
        m_secondaryKeyOrderComboBox->setObjectName(QStringLiteral("m_secondaryKeyOrderComboBox"));

        gridLayout_2->addWidget(m_secondaryKeyOrderComboBox, 1, 1, 1, 2);

        horizontalSpacer_5 = new QSpacerItem(47, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        gridLayout_2->addItem(horizontalSpacer_5, 1, 3, 1, 1);

        m_tertiaryKeyGroupBox = new QGroupBox(sortDialogClass);
        m_tertiaryKeyGroupBox->setObjectName(QStringLiteral("m_tertiaryKeyGroupBox"));
        m_tertiaryKeyGroupBox->setGeometry(QRect(40, 360, 211, 111));
        gridLayout_3 = new QGridLayout(m_tertiaryKeyGroupBox);
        gridLayout_3->setSpacing(6);
        gridLayout_3->setContentsMargins(11, 11, 11, 11);
        gridLayout_3->setObjectName(QStringLiteral("gridLayout_3"));
        m_primaryKeyColumnLabel_3 = new QLabel(m_tertiaryKeyGroupBox);
        m_primaryKeyColumnLabel_3->setObjectName(QStringLiteral("m_primaryKeyColumnLabel_3"));

        gridLayout_3->addWidget(m_primaryKeyColumnLabel_3, 0, 0, 1, 1);

        m_tertiaryKeyColumnComboBox = new QComboBox(m_tertiaryKeyGroupBox);
        m_tertiaryKeyColumnComboBox->setObjectName(QStringLiteral("m_tertiaryKeyColumnComboBox"));

        gridLayout_3->addWidget(m_tertiaryKeyColumnComboBox, 0, 1, 1, 1);

        horizontalSpacer_3 = new QSpacerItem(84, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        gridLayout_3->addItem(horizontalSpacer_3, 0, 2, 1, 2);

        m_primaryKeyOrderLabel_3 = new QLabel(m_tertiaryKeyGroupBox);
        m_primaryKeyOrderLabel_3->setObjectName(QStringLiteral("m_primaryKeyOrderLabel_3"));

        gridLayout_3->addWidget(m_primaryKeyOrderLabel_3, 1, 0, 1, 1);

        m_tertiaryKeyOrderComboBox = new QComboBox(m_tertiaryKeyGroupBox);
        m_tertiaryKeyOrderComboBox->setObjectName(QStringLiteral("m_tertiaryKeyOrderComboBox"));

        gridLayout_3->addWidget(m_tertiaryKeyOrderComboBox, 1, 1, 1, 2);

        horizontalSpacer_6 = new QSpacerItem(47, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        gridLayout_3->addItem(horizontalSpacer_6, 1, 3, 1, 1);

        widget = new QWidget(sortDialogClass);
        widget->setObjectName(QStringLiteral("widget"));
        widget->setGeometry(QRect(310, 50, 77, 131));
        verticalLayout = new QVBoxLayout(widget);
        verticalLayout->setSpacing(6);
        verticalLayout->setContentsMargins(11, 11, 11, 11);
        verticalLayout->setObjectName(QStringLiteral("verticalLayout"));
        verticalLayout->setContentsMargins(0, 0, 0, 0);
        m_okPushButton = new QPushButton(widget);
        m_okPushButton->setObjectName(QStringLiteral("m_okPushButton"));

        verticalLayout->addWidget(m_okPushButton);

        m_cancelPushButton = new QPushButton(widget);
        m_cancelPushButton->setObjectName(QStringLiteral("m_cancelPushButton"));

        verticalLayout->addWidget(m_cancelPushButton);

        verticalSpacer = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

        verticalLayout->addItem(verticalSpacer);

        m_morePushButton = new QPushButton(widget);
        m_morePushButton->setObjectName(QStringLiteral("m_morePushButton"));
        m_morePushButton->setCheckable(true);
        m_morePushButton->setAutoDefault(false);

        verticalLayout->addWidget(m_morePushButton);


        retranslateUi(sortDialogClass);
        QObject::connect(m_okPushButton, SIGNAL(clicked()), sortDialogClass, SLOT(accept()));
        QObject::connect(m_cancelPushButton, SIGNAL(clicked()), sortDialogClass, SLOT(close()));
        QObject::connect(m_morePushButton, SIGNAL(toggled(bool)), m_secondaryKeyGroupBox, SLOT(setVisible(bool)));
        QObject::connect(m_morePushButton, SIGNAL(toggled(bool)), m_tertiaryKeyGroupBox, SLOT(setVisible(bool)));

        QMetaObject::connectSlotsByName(sortDialogClass);
    } // setupUi

    void retranslateUi(QDialog *sortDialogClass)
    {
        sortDialogClass->setWindowTitle(QApplication::translate("sortDialogClass", "sortDialog", 0));
        m_primaryKeyGroupBox->setTitle(QApplication::translate("sortDialogClass", "&Primary Key", 0));
        m_primaryKeyColumnLabel->setText(QApplication::translate("sortDialogClass", "Column:", 0));
        m_primaryKeyColumnComboBox->clear();
        m_primaryKeyColumnComboBox->insertItems(0, QStringList()
         << QApplication::translate("sortDialogClass", "None", 0)
        );
        m_primaryKeyOrderLabel->setText(QApplication::translate("sortDialogClass", "Order:", 0));
        m_primaryKeyOrderComboBox->clear();
        m_primaryKeyOrderComboBox->insertItems(0, QStringList()
         << QApplication::translate("sortDialogClass", "Ascending", 0)
         << QApplication::translate("sortDialogClass", "Descending", 0)
        );
        m_secondaryKeyGroupBox->setTitle(QApplication::translate("sortDialogClass", "&Secondary Key", 0));
        m_primaryKeyColumnLabel_2->setText(QApplication::translate("sortDialogClass", "Column:", 0));
        m_secondaryKeyColumnComboBox->clear();
        m_secondaryKeyColumnComboBox->insertItems(0, QStringList()
         << QApplication::translate("sortDialogClass", "None", 0)
        );
        m_primaryKeyOrderLabel_2->setText(QApplication::translate("sortDialogClass", "Order:", 0));
        m_secondaryKeyOrderComboBox->clear();
        m_secondaryKeyOrderComboBox->insertItems(0, QStringList()
         << QApplication::translate("sortDialogClass", "Ascending", 0)
         << QApplication::translate("sortDialogClass", "Descending", 0)
        );
        m_tertiaryKeyGroupBox->setTitle(QApplication::translate("sortDialogClass", "&Tertiary Key", 0));
        m_primaryKeyColumnLabel_3->setText(QApplication::translate("sortDialogClass", "Column:", 0));
        m_tertiaryKeyColumnComboBox->clear();
        m_tertiaryKeyColumnComboBox->insertItems(0, QStringList()
         << QApplication::translate("sortDialogClass", "None", 0)
        );
        m_primaryKeyOrderLabel_3->setText(QApplication::translate("sortDialogClass", "Order:", 0));
        m_tertiaryKeyOrderComboBox->clear();
        m_tertiaryKeyOrderComboBox->insertItems(0, QStringList()
         << QApplication::translate("sortDialogClass", "Ascending", 0)
         << QApplication::translate("sortDialogClass", "Descending", 0)
        );
        m_okPushButton->setText(QApplication::translate("sortDialogClass", "&Ok", 0));
        m_cancelPushButton->setText(QApplication::translate("sortDialogClass", "Cancel", 0));
        m_morePushButton->setText(QApplication::translate("sortDialogClass", "&More", 0));
    } // retranslateUi

};

namespace Ui {
    class sortDialogClass: public Ui_sortDialogClass {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_SORTDIALOG_H
