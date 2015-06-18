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

	//获得图表的设置 以此来画出曲线图
	const chartSettings getChartSettings();

	//设置x y 能够选择的范围
	void setSelectedRange(QChar, QChar);
private:

	Ui::plotDialogClass ui;
};

#endif // PLOTDIALOG_H
