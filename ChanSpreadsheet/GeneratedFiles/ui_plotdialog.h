/********************************************************************************
** Form generated from reading UI file 'plotdialog.ui'
**
** Created by: Qt User Interface Compiler version 5.4.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_PLOTDIALOG_H
#define UI_PLOTDIALOG_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QDialog>
#include <QtWidgets/QGroupBox>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_plotDialogClass
{
public:
	QWidget*			layoutWidget;
	QVBoxLayout*		verticalLayout;
	QPushButton*		m_okPushButton;
	QSpacerItem*		verticalSpacer;
	QPushButton*		m_cancelPushButton;
	QWidget*			layoutWidget1;
	QVBoxLayout*		verticalLayout_2;
	QGroupBox*			m_positionGroupBox;
	QLabel*	 			m_xLabel;
	QLabel*				m_yLabel;
	QComboBox*			m_xComboBox;
	QComboBox*			m_yComboBox;
	QGroupBox*			groupBox;
	QLineEdit*			m_yTitleLineEdit;
	QLineEdit*			m_xTitleLineEdit;
	QLabel* 			m_xTitleLabel;
	QLabel* 			m_yTitleLabel;
	QLineEdit*			m_chartTitleLineEdit;
	QLabel*				m_chartTitleLabel;

	void setupUi(QDialog *plotDialogClass)
	{
		if (plotDialogClass->objectName().isEmpty())
			plotDialogClass->setObjectName(QStringLiteral("plotDialogClass"));
		plotDialogClass->resize(515, 331);
		layoutWidget = new QWidget(plotDialogClass);
		layoutWidget->setObjectName(QStringLiteral("layoutWidget"));
		layoutWidget->setGeometry(QRect(400, 50, 77, 71));
		verticalLayout = new QVBoxLayout(layoutWidget);
		verticalLayout->setSpacing(6);
		verticalLayout->setContentsMargins(11, 11, 11, 11);
		verticalLayout->setObjectName(QStringLiteral("verticalLayout"));
		verticalLayout->setContentsMargins(0, 0, 0, 0);
		m_okPushButton = new QPushButton(layoutWidget);
		m_okPushButton->setObjectName(QStringLiteral("m_okPushButton"));

		verticalLayout->addWidget(m_okPushButton);

		verticalSpacer = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

		verticalLayout->addItem(verticalSpacer);

		m_cancelPushButton = new QPushButton(layoutWidget);
		m_cancelPushButton->setObjectName(QStringLiteral("m_cancelPushButton"));

		verticalLayout->addWidget(m_cancelPushButton);

		layoutWidget1 = new QWidget(plotDialogClass);
		layoutWidget1->setObjectName(QStringLiteral("layoutWidget1"));
		layoutWidget1->setGeometry(QRect(30, 40, 331, 271));
		verticalLayout_2 = new QVBoxLayout(layoutWidget1);
		verticalLayout_2->setSpacing(6);
		verticalLayout_2->setContentsMargins(11, 11, 11, 11);
		verticalLayout_2->setObjectName(QStringLiteral("verticalLayout_2"));
		verticalLayout_2->setContentsMargins(0, 0, 0, 0);
		m_positionGroupBox = new QGroupBox(layoutWidget1);
		m_positionGroupBox->setObjectName(QStringLiteral("m_positionGroupBox"));
		m_xLabel = new QLabel(m_positionGroupBox);
		m_xLabel->setObjectName(QStringLiteral("m_xLabel"));
		m_xLabel->setGeometry(QRect(10, 20, 54, 12));
		m_yLabel = new QLabel(m_positionGroupBox);
		m_yLabel->setObjectName(QStringLiteral("m_yLabel"));
		m_yLabel->setGeometry(QRect(10, 50, 54, 12));
		m_xComboBox = new QComboBox(m_positionGroupBox);
		m_xComboBox->setObjectName(QStringLiteral("m_xComboBox"));
		m_xComboBox->setGeometry(QRect(70, 10, 51, 22));
		m_yComboBox = new QComboBox(m_positionGroupBox);
		m_yComboBox->setObjectName(QStringLiteral("m_yComboBox"));
		m_yComboBox->setGeometry(QRect(70, 50, 69, 22));

		verticalLayout_2->addWidget(m_positionGroupBox);

		groupBox = new QGroupBox(layoutWidget1);
		groupBox->setObjectName(QStringLiteral("groupBox"));
		m_yTitleLineEdit = new QLineEdit(groupBox);
		m_yTitleLineEdit->setObjectName(QStringLiteral("m_yTitleLineEdit"));
		m_yTitleLineEdit->setGeometry(QRect(70, 60, 141, 20));
		m_xTitleLineEdit = new QLineEdit(groupBox);
		m_xTitleLineEdit->setObjectName(QStringLiteral("m_xTitleLineEdit"));
		m_xTitleLineEdit->setGeometry(QRect(70, 20, 141, 20));
		m_xTitleLabel = new QLabel(groupBox);
		m_xTitleLabel->setObjectName(QStringLiteral("m_xTitleLabel"));
		m_xTitleLabel->setGeometry(QRect(10, 20, 54, 12));
		m_yTitleLabel = new QLabel(groupBox);
		m_yTitleLabel->setObjectName(QStringLiteral("m_yTitleLabel"));
		m_yTitleLabel->setGeometry(QRect(10, 60, 54, 12));
		m_chartTitleLineEdit = new QLineEdit(groupBox);
		m_chartTitleLineEdit->setObjectName(QStringLiteral("m_chartTitleLineEdit"));
		m_chartTitleLineEdit->setGeometry(QRect(70, 100, 141, 20));
		m_chartTitleLabel = new QLabel(groupBox);
		m_chartTitleLabel->setObjectName(QStringLiteral("m_chartTitleLabel"));
		m_chartTitleLabel->setGeometry(QRect(10, 100, 54, 12));

		verticalLayout_2->addWidget(groupBox);


		retranslateUi(plotDialogClass);
		QObject::connect(m_cancelPushButton, SIGNAL(clicked()), plotDialogClass, SLOT(close()));
		QObject::connect(m_okPushButton, SIGNAL(clicked()), plotDialogClass, SLOT(accept()));

		QMetaObject::connectSlotsByName(plotDialogClass);
	} // setupUi

	void retranslateUi(QDialog *plotDialogClass)
	{
		plotDialogClass->setWindowTitle(QApplication::translate("plotDialogClass", "plotDialog", 0));
		m_okPushButton->setText(QApplication::translate("plotDialogClass", "&Ok", 0));
		m_cancelPushButton->setText(QApplication::translate("plotDialogClass", "&Cancel", 0));
		m_positionGroupBox->setTitle(QApplication::translate("plotDialogClass", "\345\235\220\346\240\207", 0));
		m_xLabel->setText(QApplication::translate("plotDialogClass", "X\350\275\264:", 0));
		m_yLabel->setText(QApplication::translate("plotDialogClass", "Y\350\275\264\357\274\232", 0));

		m_xComboBox->clear();
		m_xComboBox->addItem(QString("None"));

		m_yComboBox->clear();
		m_yComboBox->addItem(QString("None"));

		groupBox->setTitle(QApplication::translate("plotDialogClass", "\346\240\207\351\242\230", 0));
		m_xTitleLabel->setText(QApplication::translate("plotDialogClass", "X\350\275\264\346\240\207\351\242\230\357\274\232", 0));
		m_yTitleLabel->setText(QApplication::translate("plotDialogClass", "Y\350\275\264\346\240\207\351\242\230:", 0));
		m_chartTitleLabel->setText(QApplication::translate("plotDialogClass", "\345\233\276\350\241\250\345\220\215", 0));
	} // retranslateUi

};

namespace Ui {
	class plotDialogClass : public Ui_plotDialogClass {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_PLOTDIALOG_H
