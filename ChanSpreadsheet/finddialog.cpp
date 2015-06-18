#include "finddialog.h"

findDialog::findDialog(QWidget *parent)
	: QDialog(parent){

	ui.setupUi(this);

	//��ʼ��һЩ����
	init();
}


void findDialog::init(){

	//���ı��༭���� ʹ�õ�find��ť��Ч�Ĳ�����
	connect(ui.m_findWhatLineEdit, SIGNAL(textChanged(const QString&)),
		this, SLOT(enableFindButton(const QString&)));

	//find ��ť�Ͳ��Ҳ�����
	connect(ui.m_findPushButton, SIGNAL(clicked()), this, SLOT(findClicked()));

	//close��ť�Ѿ������ʦ�����ù�
}

void findDialog::enableFindButton(const QString& txt){

	//����ǿ���find ��ť��Ч
	ui.m_findPushButton->setEnabled(!txt.isEmpty());
}

void findDialog::findClicked(){

	//����б༭�е��ı�
	const QString& txt = ui.m_findWhatLineEdit->text();

	//���ƥ���Сд����� ��ô��Ҫ���ö�Ӧ�����
	Qt::CaseSensitivity cs = ui.m_mathcCaseCheckBox->isChecked() ?
		Qt::CaseSensitive : Qt::CaseInsensitive;

	//�����ǰ���ҵ���ˣ���ô��Ҫ��ǰ����
	ui.m_searchBackwardCheckBox->isChecked() ?
		emit findPrev(txt, cs) : emit findNext(txt, cs);
}
