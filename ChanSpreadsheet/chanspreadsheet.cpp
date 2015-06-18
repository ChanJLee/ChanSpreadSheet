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

//静态成员函数
template <typename ParentPtr, typename ShortCutType>
void ChanSpreadsheet::releaseAction(QAction*& pAction, ParentPtr pParent, 
	const char* const pTitle, const char* const pIconFileName,
	ShortCutType shortCut, const char* const pStatusTip){

	//产生QAction
	pAction = new QAction(tr(pTitle), pParent);

	//如果有图标 则加图标
	if (pIconFileName != NULL)
		pAction->setIcon(QIcon(pIconFileName));

	//设置快捷键
	pAction->setShortcut(shortCut);

	//设置状态提示
	pAction->setStatusTip(tr(pStatusTip));
}

//成员函数
ChanSpreadsheet::ChanSpreadsheet(QWidget *parent)
	: QMainWindow(parent),
	m_chanSpreadSheetWidget(NULL){
	//做一些初始化工作
	init();
}

void ChanSpreadsheet::init(){

	//创建电子表底层实现
	m_chanSpreadSheetWidget = new chanSpreadsheetWidget(this);

	//设置中央的控件
	this->setCentralWidget(m_chanSpreadSheetWidget);

	//创建动作
	createActions();

	//创建菜单
	createMenus();

	//创建上下文菜单
	createContextMenu();

	//创建状态栏
	createStatusBar();

	//创建工具栏
	createToolBars();

	//设置窗口的图标
	setWindowIcon(QIcon(srcFileName::pWindow));

	//读取用户的设置
	readSettings();

	//时间遏制当前的文件名
	setCurrentFile("");

	//查找窗口
	m_findDialog = NULL;

	//绘图窗口
	m_plotter = NULL;

	//设置大小策略
	setSizePolicy(QSizePolicy::Fixed,QSizePolicy::Fixed);
}


void ChanSpreadsheet::createActions(){

	//file菜单的action
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

	//对最近的文件action进行设置
	std::for_each(m_recentFileActions, m_recentFileActions + MAX_RECENT_FILES, 
		[this](QAction*& action){

		//分配action
		action = new QAction(this);

		//设置不可见
		action->setVisible(false);

		//链接信号
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
	//开关按钮
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

	//生成file菜单
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

	//添加文件菜单
	m_fileMenu = menuBar()->addMenu(tr("&File"));

	//new open save saves 
	m_fileMenu->addAction(m_newFileAction);
	m_fileMenu->addAction(m_openAction);
	m_fileMenu->addAction(m_saveAction);
	m_fileMenu->addAction(m_saveAsAction);

	//添加分割，如果有最近文件，就要显示这个空格，否则不用显示
	m_separatorAction = m_fileMenu->addSeparator();

	//将最近文件添加进file菜单
	std::for_each(m_recentFileActions, m_recentFileActions + MAX_RECENT_FILES,
		[this](QAction* action){

		m_fileMenu->addAction(action);
	});

	//再添加一个分隔符
	m_fileMenu->addSeparator();

	//exit
	m_fileMenu->addAction(m_exitAction);
}

void ChanSpreadsheet::createEditMenu(){
	
	//添加edit 文件菜单
	m_editMenu = menuBar()->addMenu(tr("&Edit"));

	//cut copy paste
	m_editMenu->addAction(m_cutAction);
	m_editMenu->addAction(m_copyAction);
	m_editMenu->addAction(m_pasteAction);

	//选择的子菜单
	m_editMenu->addSeparator();
	m_selectSubMenu = m_editMenu->addMenu(tr("&Select"));
	m_selectSubMenu->addAction(m_selectRowAction);
	m_selectSubMenu->addAction(m_selectColumnAction);
	m_selectSubMenu->addAction(m_selectAllAction);
}

void ChanSpreadsheet::createToolMenu(){
	
	//添加工具菜单
	m_toolMenu = menuBar()->addMenu(tr("&Tools"));

	//重新计算　排序 查找工具　快速定位工具　制表工具
	m_toolMenu->addAction(m_recalculateAction);
	m_toolMenu->addAction(m_sortAction);
	m_toolMenu->addAction(m_findAction);
	m_toolMenu->addAction(m_goToCellAction);
	m_toolMenu->addAction(m_plotAction);
}

void ChanSpreadsheet::createOptionMenu(){

	//添加选择菜单
	m_optionMenu = menuBar()->addMenu(tr("&Options"));

	//自动计算选项 是否显示格子
	m_optionMenu->addAction(m_showGridAction);
	m_optionMenu->addAction(m_autoRecalculateAction);
}

void ChanSpreadsheet::createHelpMenu(){

	//兼容其他os的显示风格
	menuBar()->addSeparator();

	//添加帮助菜单
	m_helpMenu = menuBar()->addMenu(tr("&Help"));

	//about me && qt
	m_helpMenu->addAction(m_aboutChanSpreadsheetAction);
	m_helpMenu->addAction(m_aboutQtAction);
}

void ChanSpreadsheet::createContextMenu(){

	//创建上下文显示菜单 点击鼠标右键即可显示 cut copy paste
	m_chanSpreadSheetWidget->addAction(m_cutAction);
	m_chanSpreadSheetWidget->addAction(m_copyAction);
	m_chanSpreadSheetWidget->addAction(m_pasteAction);

	//设置上下文的策略为action
	m_chanSpreadSheetWidget->setContextMenuPolicy(Qt::ActionsContextMenu);
}


void ChanSpreadsheet::createToolBars(){
	
	//文件工具栏
	m_fileToolBar = addToolBar(tr("&File"));
	m_fileToolBar->addAction(m_newFileAction);
	m_fileToolBar->addAction(m_openAction);
	m_fileToolBar->addAction(m_saveAction);

	m_editToolBar = addToolBar(tr("&Edit"));
	m_editToolBar->addAction(m_cutAction);
	m_editToolBar->addAction(m_copyAction);
	m_editToolBar->addAction(m_pasteAction);

	//添加一个分隔栏
	m_editToolBar->addAction(m_findAction);
	m_editToolBar->addAction(m_goToCellAction);
}

void ChanSpreadsheet::createStatusBar(){

	//指示位置
	m_locationLabel = new QLabel("W999");
	m_locationLabel->setAlignment(Qt::AlignHCenter);
	m_locationLabel->setMinimumSize(m_locationLabel->sizeHint());

	//显示公式
	m_formulaLabel = new QLabel("");
	m_formulaLabel->setIndent(3);//设置缩进

	//放入到状态栏中
	statusBar()->addWidget(m_locationLabel);
	statusBar()->addWidget(m_formulaLabel);

	connect(m_chanSpreadSheetWidget, SIGNAL(currentCellChanged(int, int, int, int)), 
		this, SLOT(updateStatusBar()));
	connect(m_chanSpreadSheetWidget, SIGNAL(modified()),
		this, SLOT(chanSpreadsheetModified()));

	updateStatusBar();
}

void ChanSpreadsheet::updateStatusBar(){

	//更新状态栏
	m_locationLabel->setText(m_chanSpreadSheetWidget->currentLocation());
	m_formulaLabel->setText(m_chanSpreadSheetWidget->currentFormula());
}

void ChanSpreadsheet::chanSpreadsheetModified(){
	//如果表格内容有变化，就要显示出当时的变化 比如正在输入的公式 以此来指示用户的操作

	//设置窗口变化了
	setWindowModified(true);

	//指示正在输入的公式
	updateStatusBar();

	//设置标题
	setChanSpreadsheetWindowTitle();
}

void ChanSpreadsheet::newFile(){

	//如果当前的文件保存了
	if (okToContinue()){

		//那么清空所有的内容 以显示这是一个新的文件
		m_chanSpreadSheetWidget->clear();

		//设置当前的文件没有名字
		setCurrentFile("");

		//设置标题
		setChanSpreadsheetWindowTitle();
	}
}

bool ChanSpreadsheet::okToContinue(){

	//如果没有修改过 那么可以继续
	if (!isWindowModified()) return true;

	//弹出的提示框有三个内容  yes no cancel 三个按钮
	int result = QMessageBox::warning(this, "Chan Spreadsheet",
		tr(
		"the document has been modified.\n"
		"do you want to save your changes?\n"
		), QMessageBox::Yes | QMessageBox::No | QMessageBox::Cancel);

	//yes 保存 cancel否定继续编辑当前的文件  No返回true 其他人可以在不保存文件的情况下情况当前的内容
	if (result == QMessageBox::Yes) return save();
	else if (result == QMessageBox::Cancel) return false;
	else return true;
}

void ChanSpreadsheet::open(){

	//如果可以保存了之前的文件 那么就可以继续了
	if (!okToContinue()) return;

	//打开文件 通过对话框获得要打开的文件名
	const QString& fileName = QFileDialog::getOpenFileName(this,
		tr("Open Chan Spreadsheet"),tr("\\."),tr("Chan Spreadsheet files (*.csp)"));

	//如果文件名无效 就返回
	if (fileName.isEmpty()) return;

	//可以加载文件了
	loadFile(fileName);
}

bool ChanSpreadsheet::loadFile(const QString& fileName){

	//如果打开文件失败
	if (!m_chanSpreadSheetWidget->readFile(fileName)){

		//延迟两秒，让用户足够有机会看到软件的报错信息
		statusBar()->showMessage(tr("failed to load file"), MESSAGE_DELAY);

		//返回false指示失败
		return false;
	}

	//打开成功就设置当前的文件为fileName 
	setCurrentFile(fileName);

	//成功了就提示用户加载成功 并且返回true 指示成功
	statusBar()->showMessage(tr("successed to load file"), MESSAGE_DELAY);

	//设置当前没有被修改过 并且设置窗口的标题
	setWindowModified(false);
	setChanSpreadsheetWindowTitle();

	//返回true指示成功
	return true;
}

bool ChanSpreadsheet::save(){

	//如果当前的文件还没有名字 那么就要提醒用户保存的时候给文件一个名字
	if (m_curFile.isEmpty()) return saveAs();

	//保存当前的文件
	return saveFile(m_curFile);
}

bool ChanSpreadsheet::saveFile(const QString& fileName){

	//如果保存文件失败
	if (!m_chanSpreadSheetWidget->writeFile(fileName)){

		//显示错误信息，并且给用户足够的实现去反映 当前的文件没有保存成功
		statusBar()->showMessage(tr("failed to save file"), MESSAGE_DELAY);
		return false;
	}

	//设置当前的文件 因为可能saveAs 函数调用 此时文件已经被命名了
	setCurrentFile(fileName);

	//提示用户当前已经成功的保存了文件 并返回true指示当前已经成功保存
	statusBar()->showMessage(tr("successed to save file"), MESSAGE_DELAY);

	//如果保存了 那么就可以让 * 号去掉了
	setChanSpreadsheetWindowTitle();

	return true;
}

bool ChanSpreadsheet::saveAs(){

	//"." 代表当前的文件目录
	const QString& fileName = QFileDialog::getSaveFileName(this,
		tr("save Chan Spreadsheet file"), ".", tr("Chan Spreadsheet files(*.csp)"));

	//如果文件名是无效的 那么就返回false 指示失败
	if (fileName.isEmpty()) return false;

	//可以调用saveFile 保存当前的文件了
	return saveFile(fileName);
}

void ChanSpreadsheet::closeEvent(QCloseEvent* event){

	//如果保存了当前的文件
	if (okToContinue()){

		//写下用户的设置
		writeSettings();

		//现在可以关闭了
		event->accept();
	}
	 
	//如果没有成功保存 那么就忽略这次的操作
	else event->ignore();
}

//最后修改时间　2015/1/14 14:15
void ChanSpreadsheet::setCurrentFile(const QString& fileName){

	//设置当前的文件为给定的文件
	m_curFile = fileName;

	//设置当前的窗口没有修改过
	setWindowModified(false);

	//删除有m_curFile 的 并且把其放到第一个
	if (!m_curFile.isEmpty()){

		//找到之前的记录
		m_recentFiles.removeAll(m_curFile);

		//把它放到第一个
		m_recentFiles.push_front(m_curFile);
	}

	//更新最近的文件actions
	updateRecentFileActions();
}

//最后修改时间 2015/1/14 14:15
void ChanSpreadsheet::setChanSpreadsheetWindowTitle(){

	//默认的标题
	QString showName = m_curFile.isEmpty() ?
		tr("untitled") : strippedName(m_curFile);
	//如果当前的文件不是空的 那么就用当前的文件名作为标题  如果当前的文件是空的
	//那么就用默认的名字作为窗口的标题

	//显示标题 修改过就要有 *  否则没有
	if (isWindowModified())
		setWindowTitle(tr("%1 [*] - %2").arg(showName).arg(tr("Chan Spreadsheet")));
	else setWindowTitle(tr("%1 - %2").arg(showName).arg(tr("Chan Spreadsheet")));	
}

void ChanSpreadsheet::updateRecentFileActions(){

	//找到要删除的项
	QStringList::iterator it = std::remove_if(m_recentFiles.begin(), m_recentFiles.end(),
		[](const QString& fileName){
		return !QFile::exists(fileName);
	});

	//删除不存在的文件记录
	m_recentFiles.erase(it, m_recentFiles.end());

	//获得最近有效文件的大小
	const size_t size  = m_recentFiles.size();

	//访问最近文件的迭代器
	size_t index = 0;

	std::for_each(m_recentFileActions, m_recentFileActions + MAX_RECENT_FILES, 
		[&,this](QAction* action){

		//得到能够足够显示最近文件的action
		if (index < size){

			//第一个是下标 第二个是文件名
			QString text = tr("&%1 - %2").arg(index).arg(strippedName(m_recentFiles[index]));

			//设置显示的文本
			action->setText(text);

			//设置与之关联的数据
			action->setData(m_recentFiles[index]);

			//设置可见
			action->setVisible(true);
		}

		//多余的那些action 就使他们隐藏
		else action->setVisible(false);

		//指向下一个
		++index;
	});
}

void ChanSpreadsheet::openRecentFile(){

	//如果没有保存成功那么就直接返回
	if (!okToContinue()) return;

	//找到发送者
	QAction* action = qobject_cast<QAction*>(sender());

	//如果转换失败那么返回
	if (action == NULL) return;

	//action的保存的数据是string
	loadFile(action->data().toString());
}

void ChanSpreadsheet::find(){

	//如果find 查找对话框还没有生成 那么就生成一个
	if (m_findDialog == NULL){

		m_findDialog = new findDialog(this);

		//链接信号与槽
		connect(m_findDialog, SIGNAL(findNext(const QString&, Qt::CaseSensitivity)),
			m_chanSpreadSheetWidget, SLOT(findNext(const QString&, Qt::CaseSensitivity)));

		connect(m_findDialog, SIGNAL(findPrev(const QString&, Qt::CaseSensitivity)),
			m_chanSpreadSheetWidget, SLOT(findPrev(const QString&, Qt::CaseSensitivity)));

		m_findDialog->setWindowTitle(tr("find"));
	}

	//显示find
	m_findDialog->show();

	//成为顶层窗口
	m_findDialog->raise();

	//成为活动窗口
	m_findDialog->activateWindow();
}

void ChanSpreadsheet::goToCell(){

	//创建一个对话框
	goToCellDialog dialog(this);

	dialog.setWindowTitle(tr("go to cell"));

	if (dialog.exec()){

		//全都转化为大写
		QString position = dialog.cell().toUpper();

		//坐标的第一个为字母  之后就全是数字
		m_chanSpreadSheetWidget->setCurrentCell(position.mid(1).toInt(), 
			position[0].unicode() - 'A');
	}
}


void ChanSpreadsheet::sort(){

	//创建一个对话框
	sortDialog dialog(this);

	dialog.setWindowTitle(tr("sort"));

	//获得范围
	QTableWidgetSelectionRange range = m_chanSpreadSheetWidget->selectedRange();

	//找到列的范围
	dialog.setColumnRange('A' + range.leftColumn(), 'A' + range.rightColumn());

	//将用户选择的结果传给表格的底层实现
	if (dialog.exec()){
		m_chanSpreadSheetWidget->sort(dialog.comparisonObject());
	}
}

void ChanSpreadsheet::plot(){

	plotDialog dialog(this);

	dialog.setWindowTitle("plotter");

	if (m_plotter == NULL){
		//分配一个绘图对象
		m_plotter = new plotter(this);
	}

	QTableWidgetSelectionRange range = m_chanSpreadSheetWidget->selectedRange();

	//设置选择的范围
	dialog.setSelectedRange('A' + range.leftColumn(), 'A' + range.rightColumn());

	if (dialog.exec()){

		//清空之前的记录
		m_plotter->clearAllCurve();

		//设置图的内容
		m_plotter->drawChart(dialog.getChartSettings(), m_chanSpreadSheetWidget->selectedTableItems());

		//显示的窗口
		QMainWindow* win = new QMainWindow(this);

		//设置中间的部件
		win->setCentralWidget(m_plotter);

		//显示
		win->show();
	}
}


void ChanSpreadsheet::aboutChanSpreadsheet(){

	//弹出 about 对话框
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

	//将设置存放到系统中 win是注册表 unix文本文件...
	QSettings settings(chanSpreadsheetInfo::organization, chanSpreadsheetInfo::application);

	//几何形状
	settings.setValue(chanSpreadsheetInfo::geometry, saveGeometry());

	//最近文件内容
	settings.setValue(chanSpreadsheetInfo::recentFiles, m_recentFiles);

	//是否选择了show grid  
	settings.setValue(chanSpreadsheetInfo::showGrid, m_showGridAction->isChecked());

	//是否选择了 auto recalcate
	settings.setValue(chanSpreadsheetInfo::autoRecalc, m_autoRecalculateAction->isChecked());
}

void ChanSpreadsheet::readSettings(){

	//获得存放到系统中的设置 win是注册表 unix文本文件...
	QSettings settings(chanSpreadsheetInfo::organization, chanSpreadsheetInfo::application);
	
	//设置几何形状
	restoreGeometry(settings.value(chanSpreadsheetInfo::geometry).toByteArray());

	//设置最近的文件 并且更新它
	m_recentFiles = settings.value(chanSpreadsheetInfo::recentFiles).toStringList();
	updateRecentFileActions();

	//设置show grid
	m_showGridAction->setChecked(settings.value(chanSpreadsheetInfo::showGrid).toBool());

	//设置是否自动计算
	m_autoRecalculateAction->setChecked(settings.value(chanSpreadsheetInfo::autoRecalc).toBool());
}
