#include "sortdialog.h"

sortDialog::sortDialog(QWidget *parent)
	: QDialog(parent){

	//��ʼ��
	ui.setupUi(this);
	
	//��һЩ��������
	init();
}


void sortDialog::init(){

	//���õڶ���  ������ѡ�������
	ui.m_secondaryKeyGroupBox->hide();
	ui.m_tertiaryKeyGroupBox->hide();

	//����Ĭ�ϵļ�ֵѡ��
	setColumnRange('A', 'Z');
}

void sortDialog::setColumnRange(QChar first, QChar end){

	//�Ȱ�������ֵѡ��ɾ��
	ui.m_primaryKeyColumnComboBox->clear();
	ui.m_secondaryKeyColumnComboBox->clear();
	ui.m_tertiaryKeyColumnComboBox->clear();

	//Ĭ�ϵڶ��� ��������û�б�ѡ�е� ����Ҫ���һ�� "None"
	ui.m_secondaryKeyColumnComboBox->addItem(tr("None"));
	ui.m_tertiaryKeyColumnComboBox->addItem(tr("None"));
	
	//���ﱣ֤�к��������
	while (first <= end){

		//����к�
		ui.m_primaryKeyColumnComboBox->addItem(QString(first));
		ui.m_secondaryKeyColumnComboBox->addItem(QString(first));
		ui.m_tertiaryKeyColumnComboBox->addItem(QString(first));

		//ǰ��һ����
		first = first.unicode() + 1;
	}
}

const chanSpreadsheetCompare sortDialog::comparisonObject()const{

	return chanSpreadsheetCompare(
		ui.m_primaryKeyColumnComboBox->currentIndex(),
		ui.m_secondaryKeyColumnComboBox->currentIndex() - 1,
		ui.m_tertiaryKeyColumnComboBox->currentIndex() - 1,
		!ui.m_primaryKeyOrderComboBox->currentIndex(),
		!ui.m_secondaryKeyOrderComboBox->currentIndex(),
		!ui.m_tertiaryKeyOrderComboBox->currentIndex()
		);
}