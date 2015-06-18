#ifndef PLOTDIALOG_H
#define PLOTDIALOG_H

#include <QtWidgets/QDialog>
#include "ui_plotdialog.h"
#include "chartSettings.h">

class plotDialog : public QDialog
{
	Q_OBJECT

public:
	plotDialog(QWidget *parent = NULL);
	~plotDialog() = default;

	//���ͼ������� �Դ�����������ͼ
	const chartSettings getChartSettings();

	//����x y �ܹ�ѡ��ķ�Χ
	void setSelectedRange(QChar, QChar);
private:

	Ui::plotDialogClass ui;
};

#endif // PLOTDIALOG_H
