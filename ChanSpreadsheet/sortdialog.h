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

	//���öԻ����е�ѡ��Χ
	void setColumnRange(QChar, QChar);
	const chanSpreadsheetCompare comparisonObject()const;
private:
	//��һЩ��ʼ������
	void init();

private:
	Ui::sortDialogClass ui;
};

#endif // SORTDIALOG_H
