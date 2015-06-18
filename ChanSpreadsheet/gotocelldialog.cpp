#include "gotocelldialog.h"
#include <qregexp.h>

goToCellDialog::goToCellDialog(QWidget *parent)
	: QDialog(parent){
	ui.setupUi(this);

	//初始化一些设置
	init();
}


void goToCellDialog::init(){

	//对于lineedit 的设置
	setGoToCellLineEdit();

	//cancel已经设置
}

void goToCellDialog::setGoToCellLineEdit(){

	//设置文本编辑框可接受的类型  具体参照正则表达式
	QRegExp exp("[a-zA-Z][1-9]{0,2}");

	//设置正则表达式
	ui.m_cellLocationLineEdit->setValidator(new QRegExpValidator(exp, this));

	connect(ui.m_cellLocationLineEdit, SIGNAL(textChanged(const QString&)), this, SLOT(enableOkButton()));
}


void goToCellDialog::enableOkButton(){

	//如果有有效的输入就是的ok按钮有效
	ui.m_okPushButton->setEnabled(ui.m_cellLocationLineEdit->hasAcceptableInput());
}


void goToCellDialog::okButtonClicked(){

	//获得文本
	const QString txt(ui.m_cellLocationLineEdit->text());

	//接受请求了
	accept();
}