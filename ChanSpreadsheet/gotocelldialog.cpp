#include "gotocelldialog.h"
#include <qregexp.h>

goToCellDialog::goToCellDialog(QWidget *parent)
	: QDialog(parent){
	ui.setupUi(this);

	//��ʼ��һЩ����
	init();
}


void goToCellDialog::init(){

	//����lineedit ������
	setGoToCellLineEdit();

	//cancel�Ѿ�����
}

void goToCellDialog::setGoToCellLineEdit(){

	//�����ı��༭��ɽ��ܵ�����  �������������ʽ
	QRegExp exp("[a-zA-Z][1-9]{0,2}");

	//����������ʽ
	ui.m_cellLocationLineEdit->setValidator(new QRegExpValidator(exp, this));

	connect(ui.m_cellLocationLineEdit, SIGNAL(textChanged(const QString&)), this, SLOT(enableOkButton()));
}


void goToCellDialog::enableOkButton(){

	//�������Ч��������ǵ�ok��ť��Ч
	ui.m_okPushButton->setEnabled(ui.m_cellLocationLineEdit->hasAcceptableInput());
}


void goToCellDialog::okButtonClicked(){

	//����ı�
	const QString txt(ui.m_cellLocationLineEdit->text());

	//����������
	accept();
}