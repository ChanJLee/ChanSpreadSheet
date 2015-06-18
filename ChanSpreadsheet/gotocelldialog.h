#ifndef GOTOCELLDIALOG_H
#define GOTOCELLDIALOG_H

#include <QtWidgets/QDialog>
#include "ui_gotocelldialog.h"

class goToCellDialog : public QDialog
{
	Q_OBJECT

public:
	goToCellDialog(QWidget *parent = 0);
	~goToCellDialog() = default;

	const QString cell(){ return ui.m_cellLocationLineEdit->text(); }
private slots:
	void okButtonClicked();
	void enableOkButton();

private:
	void init();
	void setGoToCellLineEdit();

private:
	Ui::goToCellDialogClass ui;
};

#endif // GOTOCELLDIALOG_H
