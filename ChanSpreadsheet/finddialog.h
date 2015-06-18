#ifndef FINDDIALOG_H
#define FINDDIALOG_H

#include <QtWidgets/QDialog>
#include "ui_finddialog.h"

class findDialog : public QDialog
{
	Q_OBJECT

public:
	findDialog(QWidget *parent = 0);
	~findDialog() = default;

signals:
	void findNext(const QString&, Qt::CaseSensitivity);
	void findPrev(const QString&, Qt::CaseSensitivity);

private slots:
	void findClicked();
	void enableFindButton(const QString&);

private:
	void init();

private:
	Ui::findDialogClass ui;
};

#endif // FINDDIALOG_H
