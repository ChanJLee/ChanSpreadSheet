#include "finddialog.h"

findDialog::findDialog(QWidget *parent)
	: QDialog(parent){

	ui.setupUi(this);

	//初始化一些设置
	init();
}


void findDialog::init(){

	//行文本编辑器和 使得的find按钮有效的槽链接
	connect(ui.m_findWhatLineEdit, SIGNAL(textChanged(const QString&)),
		this, SLOT(enableFindButton(const QString&)));

	//find 按钮和查找槽链接
	connect(ui.m_findPushButton, SIGNAL(clicked()), this, SLOT(findClicked()));

	//close按钮已经在设计师中设置过
}

void findDialog::enableFindButton(const QString& txt){

	//如果非空则find 按钮有效
	ui.m_findPushButton->setEnabled(!txt.isEmpty());
}

void findDialog::findClicked(){

	//获得行编辑中的文本
	const QString& txt = ui.m_findWhatLineEdit->text();

	//如果匹配大小写点击了 那么就要设置对应的情况
	Qt::CaseSensitivity cs = ui.m_mathcCaseCheckBox->isChecked() ?
		Qt::CaseSensitive : Qt::CaseInsensitive;

	//如果向前查找点击了，那么就要向前查找
	ui.m_searchBackwardCheckBox->isChecked() ?
		emit findPrev(txt, cs) : emit findNext(txt, cs);
}
