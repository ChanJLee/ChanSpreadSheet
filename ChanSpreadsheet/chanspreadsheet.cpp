#include "chanspreadsheet.h"

#include <qmenu.h>
#include <qstatusbar.h>
#include <qtoolbar.h>
#include <qicon.h>
#include <qapplication.h>
#include <qmenubar.h>
#include <algorithm>
#include <qlabel.h>
#include <qmessagebox.h>
#include <qfiledialog.h>
#include <qevent.h>
#include <finddialog.h>
#include <gotocelldialog.h>
#include <sortdialog.h>
#include "plotter.h"
#include "plotdialog.h"
#include <qsettings.h>
#include <qbytearray.h>

//��̬��Ա����
template <typename ParentPtr, typename ShortCutType>
void ChanSpreadsheet::releaseAction(QAction*& pAction, ParentPtr pParent, 
	const char* const pTitle, const char* const pIconFileName,
	ShortCutType shortCut, const char* const pStatusTip){

	//����QAction
	pAction = new QAction(tr(pTitle), pParent);

	//�����ͼ�� ���ͼ��
	if (pIconFileName != NULL)
		pAction->setIcon(QIcon(pIconFileName));

	//���ÿ�ݼ�
	pAction->setShortcut(shortCut);

	//����״̬��ʾ
	pAction->setStatusTip(tr(pStatusTip));
}

//��Ա����
ChanSpreadsheet::ChanSpreadsheet(QWidget *parent)
	: QMainWindow(parent),
	m_chanSpreadSheetWidget(NULL){
	//��һЩ��ʼ������
	init();
}

void ChanSpreadsheet::init(){

	//�������ӱ�ײ�ʵ��
	m_chanSpreadSheetWidget = new chanSpreadsheetWidget(this);

	//��������Ŀؼ�
	this->setCentralWidget(m_chanSpreadSheetWidget);

	//��������
	createActions();

	//�����˵�
	createMenus();

	//���������Ĳ˵�
	createContextMenu();

	//����״̬��
	createStatusBar();

	//����������
	createToolBars();

	//���ô��ڵ�ͼ��
	setWindowIcon(QIcon(srcFileName::pWindow));

	//��ȡ�û�������
	readSettings();

	//ʱ����Ƶ�ǰ���ļ���
	setCurrentFile("");

	//���Ҵ���
	m_findDialog = NULL;

	//��ͼ����
	m_plotter = NULL;

	//���ô�С����
	setSizePolicy(QSizePolicy::Fixed,QSizePolicy::Fixed);
}


void ChanSpreadsheet::createActions(){

	//file�˵���action
	createFileMenuAction();

	//edit
	createEditMenuAction();

	//tool
	createToolMenuAction();

	//option
	createOptionMenuAction();

	//help
	createHelpMenuAction();
}

void ChanSpreadsheet::createFileMenuAction(){
	//file 
	releaseAction(m_newFileAction, this, "&New", srcFileName::pNew, QKeySequence::New,
		"Create a new Chan Spreadsheet file");
	connect(m_newFileAction, SIGNAL(triggered()), this, SLOT(newFile()));

	releaseAction(m_openAction, this, "&Open", srcFileName::pOpen, QKeySequence::Open,
		"open a new Chan Spreadsheet file");
	connect(m_openAction, SIGNAL(triggered()), this, SLOT(open()));

	releaseAction(m_saveAction, this, "&Save", srcFileName::pSave, QKeySequence::Open,
		"open a new Chan Spreadsheet file");
	connect(m_saveAction, SIGNAL(triggered()), this, SLOT(save()));

	releaseAction(m_saveAsAction, this, "Save &As", srcFileName::pSaveAs, QKeySequence::SaveAs,
		"save as...");
	connect(m_saveAsAction, SIGNAL(triggered()), this, SLOT(saveAs()));

	releaseAction(m_exitAction, this, "E&xit", srcFileName::pExit,tr("Ctrl + O"),
		"exit");
	connect(m_exitAction, SIGNAL(triggered()), this, SLOT(close()));

	//��������ļ�action��������
	std::for_each(m_recentFileActions, m_recentFileActions + MAX_RECENT_FILES, 
		[this](QAction*& action){

		//����action
		action = new QAction(this);

		//���ò��ɼ�
		action->setVisible(false);

		//�����ź�
		connect(action, SLOT(triggered()), this, SLOT(openRecentFile()));
	});
}

void ChanSpreadsheet::createEditMenuAction(){
	//edit
	releaseAction(m_cutAction, this, "Cu&t", srcFileName::pCut, QKeySequence::Cut, 
		"cut...");
	connect(m_cutAction, SIGNAL(triggered()), m_chanSpreadSheetWidget, SLOT(cut()));

	releaseAction(m_copyAction, this, "&Copy", srcFileName::pCopy, QKeySequence::Copy, 
		"copy...");
	connect(m_copyAction, SIGNAL(triggered()),m_chanSpreadSheetWidget,SLOT(copy()));

	releaseAction(m_pasteAction, this, "&Paste", srcFileName::pPaste, QKeySequence::Paste, 
		"paste...");
	connect(m_pasteAction, SIGNAL(triggered()), m_chanSpreadSheetWidget, SLOT(paste()));

	releaseAction(m_selectColumnAction, this, "&Column", NULL, tr(""),
		"select column");
	connect(m_selectColumnAction, SIGNAL(triggered()), m_chanSpreadSheetWidget, SLOT(selectCurrentColumn()));

	releaseAction(m_selectRowAction, this, "&Row", NULL, tr(""),
		"select row");
	connect(m_selectRowAction, SIGNAL(triggered()), m_chanSpreadSheetWidget, SLOT(selectCurrentRow()));

	releaseAction(m_selectAllAction, this, "&All",srcFileName::pSelectAll, tr("Ctrl + A"), 
		"select all");
	connect(m_selectAllAction, SIGNAL(triggered()), m_chanSpreadSheetWidget, SLOT(selectAll()));
}

void ChanSpreadsheet::createToolMenuAction(){
	//tool
	releaseAction(m_recalculateAction, this, "&Recalculate", srcFileName::pRecalculate, tr(""),
		"recalculate the formula");
	connect(m_recalculateAction, SIGNAL(triggered()), m_chanSpreadSheetWidget, SLOT(recalculate()));

	releaseAction(m_sortAction, this, "Sort", srcFileName::pSort, tr(""), 
		"sort the range what you selected");
	connect(m_sortAction, SIGNAL(triggered()),this, SLOT(sort()));

	releaseAction(m_findAction, this, "&Find", srcFileName::pFind, QKeySequence::Find, 
		"find something");
	connect(m_findAction, SIGNAL(triggered()), this, SLOT(find()));

	releaseAction(m_goToCellAction, this, "&Go To Cell", srcFileName::pGoToCell, tr("Ctrl + G"), 
		"go to cell");
	connect(m_goToCellAction, SIGNAL(triggered()), this, SLOT(goToCell()));

	releaseAction(m_plotAction, this, "&Plot", srcFileName::pPlot, tr(""), 
		"plot");
	connect(m_plotAction, SIGNAL(triggered()), this, SLOT(plot()));
}

void ChanSpreadsheet::createOptionMenuAction(){
	//���ذ�ť
	releaseAction(m_autoRecalculateAction, this, "&Recalculate", NULL, tr("F9"), 
		"recalculate");
	m_autoRecalculateAction->setCheckable(true);
	m_autoRecalculateAction->setChecked(true);
	connect(m_autoRecalculateAction, SIGNAL(toggled(bool)), m_chanSpreadSheetWidget, SLOT(setAutoRecalculate(bool)));

	releaseAction(m_showGridAction, this, "&showGridAction", NULL, tr("F5"),
		"show grid");
	m_showGridAction->setCheckable(true);
	m_showGridAction->setChecked(true);
	connect(m_showGridAction, SIGNAL(toggled(bool)), m_chanSpreadSheetWidget, SLOT(setShowGrid(bool)));
}

void ChanSpreadsheet::createHelpMenuAction(){
	//help
	releaseAction(m_aboutChanSpreadsheetAction, this, "&About Me", srcFileName::pAbout, tr(""),
		"help");
	connect(m_aboutChanSpreadsheetAction, SIGNAL(triggered()), this, SLOT(aboutChanSpreadsheet()));

	releaseAction(m_aboutQtAction, this, "About &Qt", srcFileName::pAboutQt, tr(""), 
		"about QT");
	connect(m_aboutQtAction, SIGNAL(triggered()), qApp, SLOT(aboutQt()));
}

void ChanSpreadsheet::createMenus(){

	//����file�˵�
	createFileMenu();

	//edit
	createEditMenu();

	//tool
	createToolMenu();

	//option
	createOptionMenu();

	//help
	createHelpMenu();
}

void ChanSpreadsheet::createFileMenu(){

	//����ļ��˵�
	m_fileMenu = menuBar()->addMenu(tr("&File"));

	//new open save saves 
	m_fileMenu->addAction(m_newFileAction);
	m_fileMenu->addAction(m_openAction);
	m_fileMenu->addAction(m_saveAction);
	m_fileMenu->addAction(m_saveAsAction);

	//��ӷָ���������ļ�����Ҫ��ʾ����ո񣬷�������ʾ
	m_separatorAction = m_fileMenu->addSeparator();

	//������ļ���ӽ�file�˵�
	std::for_each(m_recentFileActions, m_recentFileActions + MAX_RECENT_FILES,
		[this](QAction* action){

		m_fileMenu->addAction(action);
	});

	//�����һ���ָ���
	m_fileMenu->addSeparator();

	//exit
	m_fileMenu->addAction(m_exitAction);
}

void ChanSpreadsheet::createEditMenu(){
	
	//���edit �ļ��˵�
	m_editMenu = menuBar()->addMenu(tr("&Edit"));

	//cut copy paste
	m_editMenu->addAction(m_cutAction);
	m_editMenu->addAction(m_copyAction);
	m_editMenu->addAction(m_pasteAction);

	//ѡ����Ӳ˵�
	m_editMenu->addSeparator();
	m_selectSubMenu = m_editMenu->addMenu(tr("&Select"));
	m_selectSubMenu->addAction(m_selectRowAction);
	m_selectSubMenu->addAction(m_selectColumnAction);
	m_selectSubMenu->addAction(m_selectAllAction);
}

void ChanSpreadsheet::createToolMenu(){
	
	//��ӹ��߲˵�
	m_toolMenu = menuBar()->addMenu(tr("&Tools"));

	//���¼��㡡���� ���ҹ��ߡ����ٶ�λ���ߡ��Ʊ���
	m_toolMenu->addAction(m_recalculateAction);
	m_toolMenu->addAction(m_sortAction);
	m_toolMenu->addAction(m_findAction);
	m_toolMenu->addAction(m_goToCellAction);
	m_toolMenu->addAction(m_plotAction);
}

void ChanSpreadsheet::createOptionMenu(){

	//���ѡ��˵�
	m_optionMenu = menuBar()->addMenu(tr("&Options"));

	//�Զ�����ѡ�� �Ƿ���ʾ����
	m_optionMenu->addAction(m_showGridAction);
	m_optionMenu->addAction(m_autoRecalculateAction);
}

void ChanSpreadsheet::createHelpMenu(){

	//��������os����ʾ���
	menuBar()->addSeparator();

	//��Ӱ����˵�
	m_helpMenu = menuBar()->addMenu(tr("&Help"));

	//about me && qt
	m_helpMenu->addAction(m_aboutChanSpreadsheetAction);
	m_helpMenu->addAction(m_aboutQtAction);
}

void ChanSpreadsheet::createContextMenu(){

	//������������ʾ�˵� �������Ҽ�������ʾ cut copy paste
	m_chanSpreadSheetWidget->addAction(m_cutAction);
	m_chanSpreadSheetWidget->addAction(m_copyAction);
	m_chanSpreadSheetWidget->addAction(m_pasteAction);

	//���������ĵĲ���Ϊaction
	m_chanSpreadSheetWidget->setContextMenuPolicy(Qt::ActionsContextMenu);
}


void ChanSpreadsheet::createToolBars(){
	
	//�ļ�������
	m_fileToolBar = addToolBar(tr("&File"));
	m_fileToolBar->addAction(m_newFileAction);
	m_fileToolBar->addAction(m_openAction);
	m_fileToolBar->addAction(m_saveAction);

	m_editToolBar = addToolBar(tr("&Edit"));
	m_editToolBar->addAction(m_cutAction);
	m_editToolBar->addAction(m_copyAction);
	m_editToolBar->addAction(m_pasteAction);

	//���һ���ָ���
	m_editToolBar->addAction(m_findAction);
	m_editToolBar->addAction(m_goToCellAction);
}

void ChanSpreadsheet::createStatusBar(){

	//ָʾλ��
	m_locationLabel = new QLabel("W999");
	m_locationLabel->setAlignment(Qt::AlignHCenter);
	m_locationLabel->setMinimumSize(m_locationLabel->sizeHint());

	//��ʾ��ʽ
	m_formulaLabel = new QLabel("");
	m_formulaLabel->setIndent(3);//��������

	//���뵽״̬����
	statusBar()->addWidget(m_locationLabel);
	statusBar()->addWidget(m_formulaLabel);

	connect(m_chanSpreadSheetWidget, SIGNAL(currentCellChanged(int, int, int, int)), 
		this, SLOT(updateStatusBar()));
	connect(m_chanSpreadSheetWidget, SIGNAL(modified()),
		this, SLOT(chanSpreadsheetModified()));

	updateStatusBar();
}

void ChanSpreadsheet::updateStatusBar(){

	//����״̬��
	m_locationLabel->setText(m_chanSpreadSheetWidget->currentLocation());
	m_formulaLabel->setText(m_chanSpreadSheetWidget->currentFormula());
}

void ChanSpreadsheet::chanSpreadsheetModified(){
	//�����������б仯����Ҫ��ʾ����ʱ�ı仯 ������������Ĺ�ʽ �Դ���ָʾ�û��Ĳ���

	//���ô��ڱ仯��
	setWindowModified(true);

	//ָʾ��������Ĺ�ʽ
	updateStatusBar();

	//���ñ���
	setChanSpreadsheetWindowTitle();
}

void ChanSpreadsheet::newFile(){

	//�����ǰ���ļ�������
	if (okToContinue()){

		//��ô������е����� ����ʾ����һ���µ��ļ�
		m_chanSpreadSheetWidget->clear();

		//���õ�ǰ���ļ�û������
		setCurrentFile("");

		//���ñ���
		setChanSpreadsheetWindowTitle();
	}
}

bool ChanSpreadsheet::okToContinue(){

	//���û���޸Ĺ� ��ô���Լ���
	if (!isWindowModified()) return true;

	//��������ʾ������������  yes no cancel ������ť
	int result = QMessageBox::warning(this, "Chan Spreadsheet",
		tr(
		"the document has been modified.\n"
		"do you want to save your changes?\n"
		), QMessageBox::Yes | QMessageBox::No | QMessageBox::Cancel);

	//yes ���� cancel�񶨼����༭��ǰ���ļ�  No����true �����˿����ڲ������ļ�������������ǰ������
	if (result == QMessageBox::Yes) return save();
	else if (result == QMessageBox::Cancel) return false;
	else return true;
}

void ChanSpreadsheet::open(){

	//������Ա�����֮ǰ���ļ� ��ô�Ϳ��Լ�����
	if (!okToContinue()) return;

	//���ļ� ͨ���Ի�����Ҫ�򿪵��ļ���
	const QString& fileName = QFileDialog::getOpenFileName(this,
		tr("Open Chan Spreadsheet"),tr("\\."),tr("Chan Spreadsheet files (*.csp)"));

	//����ļ�����Ч �ͷ���
	if (fileName.isEmpty()) return;

	//���Լ����ļ���
	loadFile(fileName);
}

bool ChanSpreadsheet::loadFile(const QString& fileName){

	//������ļ�ʧ��
	if (!m_chanSpreadSheetWidget->readFile(fileName)){

		//�ӳ����룬���û��㹻�л��ῴ������ı�����Ϣ
		statusBar()->showMessage(tr("failed to load file"), MESSAGE_DELAY);

		//����falseָʾʧ��
		return false;
	}

	//�򿪳ɹ������õ�ǰ���ļ�ΪfileName 
	setCurrentFile(fileName);

	//�ɹ��˾���ʾ�û����سɹ� ���ҷ���true ָʾ�ɹ�
	statusBar()->showMessage(tr("successed to load file"), MESSAGE_DELAY);

	//���õ�ǰû�б��޸Ĺ� �������ô��ڵı���
	setWindowModified(false);
	setChanSpreadsheetWindowTitle();

	//����trueָʾ�ɹ�
	return true;
}

bool ChanSpreadsheet::save(){

	//�����ǰ���ļ���û������ ��ô��Ҫ�����û������ʱ����ļ�һ������
	if (m_curFile.isEmpty()) return saveAs();

	//���浱ǰ���ļ�
	return saveFile(m_curFile);
}

bool ChanSpreadsheet::saveFile(const QString& fileName){

	//��������ļ�ʧ��
	if (!m_chanSpreadSheetWidget->writeFile(fileName)){

		//��ʾ������Ϣ�����Ҹ��û��㹻��ʵ��ȥ��ӳ ��ǰ���ļ�û�б���ɹ�
		statusBar()->showMessage(tr("failed to save file"), MESSAGE_DELAY);
		return false;
	}

	//���õ�ǰ���ļ� ��Ϊ����saveAs �������� ��ʱ�ļ��Ѿ���������
	setCurrentFile(fileName);

	//��ʾ�û���ǰ�Ѿ��ɹ��ı������ļ� ������trueָʾ��ǰ�Ѿ��ɹ�����
	statusBar()->showMessage(tr("successed to save file"), MESSAGE_DELAY);

	//��������� ��ô�Ϳ����� * ��ȥ����
	setChanSpreadsheetWindowTitle();

	return true;
}

bool ChanSpreadsheet::saveAs(){

	//"." ����ǰ���ļ�Ŀ¼
	const QString& fileName = QFileDialog::getSaveFileName(this,
		tr("save Chan Spreadsheet file"), ".", tr("Chan Spreadsheet files(*.csp)"));

	//����ļ�������Ч�� ��ô�ͷ���false ָʾʧ��
	if (fileName.isEmpty()) return false;

	//���Ե���saveFile ���浱ǰ���ļ���
	return saveFile(fileName);
}

void ChanSpreadsheet::closeEvent(QCloseEvent* event){

	//��������˵�ǰ���ļ�
	if (okToContinue()){

		//д���û�������
		writeSettings();

		//���ڿ��Թر���
		event->accept();
	}
	 
	//���û�гɹ����� ��ô�ͺ�����εĲ���
	else event->ignore();
}

//����޸�ʱ�䡡2015/1/14 14:15
void ChanSpreadsheet::setCurrentFile(const QString& fileName){

	//���õ�ǰ���ļ�Ϊ�������ļ�
	m_curFile = fileName;

	//���õ�ǰ�Ĵ���û���޸Ĺ�
	setWindowModified(false);

	//ɾ����m_curFile �� ���Ұ���ŵ���һ��
	if (!m_curFile.isEmpty()){

		//�ҵ�֮ǰ�ļ�¼
		m_recentFiles.removeAll(m_curFile);

		//�����ŵ���һ��
		m_recentFiles.push_front(m_curFile);
	}

	//����������ļ�actions
	updateRecentFileActions();
}

//����޸�ʱ�� 2015/1/14 14:15
void ChanSpreadsheet::setChanSpreadsheetWindowTitle(){

	//Ĭ�ϵı���
	QString showName = m_curFile.isEmpty() ?
		tr("untitled") : strippedName(m_curFile);
	//�����ǰ���ļ����ǿյ� ��ô���õ�ǰ���ļ�����Ϊ����  �����ǰ���ļ��ǿյ�
	//��ô����Ĭ�ϵ�������Ϊ���ڵı���

	//��ʾ���� �޸Ĺ���Ҫ�� *  ����û��
	if (isWindowModified())
		setWindowTitle(tr("%1 [*] - %2").arg(showName).arg(tr("Chan Spreadsheet")));
	else setWindowTitle(tr("%1 - %2").arg(showName).arg(tr("Chan Spreadsheet")));	
}

void ChanSpreadsheet::updateRecentFileActions(){

	//�ҵ�Ҫɾ������
	QStringList::iterator it = std::remove_if(m_recentFiles.begin(), m_recentFiles.end(),
		[](const QString& fileName){
		return !QFile::exists(fileName);
	});

	//ɾ�������ڵ��ļ���¼
	m_recentFiles.erase(it, m_recentFiles.end());

	//��������Ч�ļ��Ĵ�С
	const size_t size  = m_recentFiles.size();

	//��������ļ��ĵ�����
	size_t index = 0;

	std::for_each(m_recentFileActions, m_recentFileActions + MAX_RECENT_FILES, 
		[&,this](QAction* action){

		//�õ��ܹ��㹻��ʾ����ļ���action
		if (index < size){

			//��һ�����±� �ڶ������ļ���
			QString text = tr("&%1 - %2").arg(index).arg(strippedName(m_recentFiles[index]));

			//������ʾ���ı�
			action->setText(text);

			//������֮����������
			action->setData(m_recentFiles[index]);

			//���ÿɼ�
			action->setVisible(true);
		}

		//�������Щaction ��ʹ��������
		else action->setVisible(false);

		//ָ����һ��
		++index;
	});
}

void ChanSpreadsheet::openRecentFile(){

	//���û�б���ɹ���ô��ֱ�ӷ���
	if (!okToContinue()) return;

	//�ҵ�������
	QAction* action = qobject_cast<QAction*>(sender());

	//���ת��ʧ����ô����
	if (action == NULL) return;

	//action�ı����������string
	loadFile(action->data().toString());
}

void ChanSpreadsheet::find(){

	//���find ���ҶԻ���û������ ��ô������һ��
	if (m_findDialog == NULL){

		m_findDialog = new findDialog(this);

		//�����ź����
		connect(m_findDialog, SIGNAL(findNext(const QString&, Qt::CaseSensitivity)),
			m_chanSpreadSheetWidget, SLOT(findNext(const QString&, Qt::CaseSensitivity)));

		connect(m_findDialog, SIGNAL(findPrev(const QString&, Qt::CaseSensitivity)),
			m_chanSpreadSheetWidget, SLOT(findPrev(const QString&, Qt::CaseSensitivity)));

		m_findDialog->setWindowTitle(tr("find"));
	}

	//��ʾfind
	m_findDialog->show();

	//��Ϊ���㴰��
	m_findDialog->raise();

	//��Ϊ�����
	m_findDialog->activateWindow();
}

void ChanSpreadsheet::goToCell(){

	//����һ���Ի���
	goToCellDialog dialog(this);

	dialog.setWindowTitle(tr("go to cell"));

	if (dialog.exec()){

		//ȫ��ת��Ϊ��д
		QString position = dialog.cell().toUpper();

		//����ĵ�һ��Ϊ��ĸ  ֮���ȫ������
		m_chanSpreadSheetWidget->setCurrentCell(position.mid(1).toInt(), 
			position[0].unicode() - 'A');
	}
}


void ChanSpreadsheet::sort(){

	//����һ���Ի���
	sortDialog dialog(this);

	dialog.setWindowTitle(tr("sort"));

	//��÷�Χ
	QTableWidgetSelectionRange range = m_chanSpreadSheetWidget->selectedRange();

	//�ҵ��еķ�Χ
	dialog.setColumnRange('A' + range.leftColumn(), 'A' + range.rightColumn());

	//���û�ѡ��Ľ���������ĵײ�ʵ��
	if (dialog.exec()){
		m_chanSpreadSheetWidget->sort(dialog.comparisonObject());
	}
}

void ChanSpreadsheet::plot(){

	plotDialog dialog(this);

	dialog.setWindowTitle("plotter");

	if (m_plotter == NULL){
		//����һ����ͼ����
		m_plotter = new plotter(this);
	}

	QTableWidgetSelectionRange range = m_chanSpreadSheetWidget->selectedRange();

	//����ѡ��ķ�Χ
	dialog.setSelectedRange('A' + range.leftColumn(), 'A' + range.rightColumn());

	if (dialog.exec()){

		//���֮ǰ�ļ�¼
		m_plotter->clearAllCurve();

		//����ͼ������
		m_plotter->drawChart(dialog.getChartSettings(), m_chanSpreadSheetWidget->selectedTableItems());

		//��ʾ�Ĵ���
		QMainWindow* win = new QMainWindow(this);

		//�����м�Ĳ���
		win->setCentralWidget(m_plotter);

		//��ʾ
		win->show();
	}
}


void ChanSpreadsheet::aboutChanSpreadsheet(){

	//���� about �Ի���
	QMessageBox::about(
		this, tr("about Chan Spreadsheet"),
		tr(
		"<h2> Chan Spreadsheet %1 </h2>"
		"<p> Copyright c 2008 Software Inc."
		"<p>Chan Spreadsheet is a small application that\n"
		"demostrates QAction, QMenuBar and many other Qt class."
		"<p>For the exchange of learning, for commercial purposes is strictly prohibited."
		).arg(chanSpreadsheetInfo::version));
}

void ChanSpreadsheet::writeSettings(){

	//�����ô�ŵ�ϵͳ�� win��ע��� unix�ı��ļ�...
	QSettings settings(chanSpreadsheetInfo::organization, chanSpreadsheetInfo::application);

	//������״
	settings.setValue(chanSpreadsheetInfo::geometry, saveGeometry());

	//����ļ�����
	settings.setValue(chanSpreadsheetInfo::recentFiles, m_recentFiles);

	//�Ƿ�ѡ����show grid  
	settings.setValue(chanSpreadsheetInfo::showGrid, m_showGridAction->isChecked());

	//�Ƿ�ѡ���� auto recalcate
	settings.setValue(chanSpreadsheetInfo::autoRecalc, m_autoRecalculateAction->isChecked());
}

void ChanSpreadsheet::readSettings(){

	//��ô�ŵ�ϵͳ�е����� win��ע��� unix�ı��ļ�...
	QSettings settings(chanSpreadsheetInfo::organization, chanSpreadsheetInfo::application);
	
	//���ü�����״
	restoreGeometry(settings.value(chanSpreadsheetInfo::geometry).toByteArray());

	//����������ļ� ���Ҹ�����
	m_recentFiles = settings.value(chanSpreadsheetInfo::recentFiles).toStringList();
	updateRecentFileActions();

	//����show grid
	m_showGridAction->setChecked(settings.value(chanSpreadsheetInfo::showGrid).toBool());

	//�����Ƿ��Զ�����
	m_autoRecalculateAction->setChecked(settings.value(chanSpreadsheetInfo::autoRecalc).toBool());
}
