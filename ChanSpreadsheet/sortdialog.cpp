#include "sortdialog.h"

sortDialog::sortDialog(QWidget *parent)
	: QDialog(parent){

	//初始化
	ui.setupUi(this);
	
	//做一些其他工作
	init();
}


void sortDialog::init(){

	//设置第二键  第三键选择框隐藏
	ui.m_secondaryKeyGroupBox->hide();
	ui.m_tertiaryKeyGroupBox->hide();

	//设置默认的键值选项
	setColumnRange('A', 'Z');
}

void sortDialog::setColumnRange(QChar first, QChar end){

	//先把三个键值选项删除
	ui.m_primaryKeyColumnComboBox->clear();
	ui.m_secondaryKeyColumnComboBox->clear();
	ui.m_tertiaryKeyColumnComboBox->clear();

	//默认第二键 第三键是没有被选中的 所以要多加一个 "None"
	ui.m_secondaryKeyColumnComboBox->addItem(tr("None"));
	ui.m_tertiaryKeyColumnComboBox->addItem(tr("None"));
	
	//这里保证列号是升序的
	while (first <= end){

		//填充列号
		ui.m_primaryKeyColumnComboBox->addItem(QString(first));
		ui.m_secondaryKeyColumnComboBox->addItem(QString(first));
		ui.m_tertiaryKeyColumnComboBox->addItem(QString(first));

		//前进一个码
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