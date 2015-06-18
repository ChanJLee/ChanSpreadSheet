#ifndef SORTDIALOG_H
#define SORTDIALOG_H

#include <QtWidgets/QDialog>
#include "ui_sortdialog.h"
#include "chanSpreadsheetCompare.h"

class sortDialog : public QDialog
{
	Q_OBJECT

public:
	sortDialog(QWidget *parent = NULL);
	~sortDialog() = default;

	//设置对话框中的选择范围
	void setColumnRange(QChar, QChar);
	const chanSpreadsheetCompare comparisonObject()const;
private:
	//做一些初始化工作
	void init();

private:
	Ui::sortDialogClass ui;
};

#endif // SORTDIALOG_H
