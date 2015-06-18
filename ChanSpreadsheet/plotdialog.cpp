#include "plotdialog.h"

plotDialog::plotDialog(QWidget *parent)
	: QDialog(parent){
	ui.setupUi(this);
}

const chartSettings plotDialog::getChartSettings(){

	//���ͼ���е�����
	return chartSettings(
		(ui.m_xComboBox->currentIndex() + 'A'),
		(ui.m_yComboBox->currentIndex() + 'A'),
		(ui.m_xTitleLineEdit->text()),
		(ui.m_yTitleLineEdit->text()),
		(ui.m_chartTitleLineEdit->text()));
}

void plotDialog::setSelectedRange(QChar first, QChar last){

	//�����ԭ�е�����
	ui.m_xComboBox->clear();
	ui.m_yComboBox->clear();

	for (; first <= last; first = first.unicode() + 1){
		
		//�� x y combo box ���������
		ui.m_xComboBox->addItem(QString(first));
		ui.m_yComboBox->addItem(QString(first));
	}
}