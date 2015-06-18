#ifndef CHANSPREADSHEET_H
#define CHANSPREADSHEET_H

#if defined _MSC_VER && _MSC_VER > 1000
	#pragma once
#endif

#include <QtWidgets/QMainWindow>
#include "chanSpreadsheetWidget.h"
#include <qfileinfo.h>

class findDialog;
class goToCellDialog;
class sortDialog;
class QLabel;
class plotter;
class plotDialog;


//图标资源文件
namespace srcFileName{
	char* const pOpen			= "src/open.png";
	char* const pNew			= "src/new.png";
	char* const pSave			= "src/save.png";
	char* const pSaveAs			= "src/saveAs.png";
	char* const pExit			= "src/exit.png";
	char* const pCut			= "src/cut.png";
	char* const pPaste			= "src/paste.png";
	char* const pCopy			= "src/copy.png";
	char* const pFind			= "src/find.png";
	char* const pSelectAll		= "src/selectAll.png";
	char* const pGoToCell		= "src/goToCell.png";
	char* const pWindow			= "src/window.png";
	char* const pPlot			= "src/plot.png";
	char* const pAbout			= "src/about.png";
	char* const pAboutQt		= "src/aboutQt.png";
	char* const pSort			= "src/sort.png";
	char* const pRecalculate	= "src/recalculate.png";
	char* const pSplash			= "src/background.png";
}

namespace chanSpreadsheetInfo{
	//存放到系统中的位置
	const QString organization = "Software Inc.";
	//名字
	const QString application   = "Chan Spreadsheet";
	//版本号

	//定义版本号的宏
#	if !defined CSP_VER 
#		define CSP_VER 1.2
#	endif

	const QString version		= "1.2";
	const QString geometry		= "geometry";
	const QString recentFiles	= "recentFiles";
	const QString showGrid		= "showGrid";
	const QString autoRecalc	= "aytiRecalc";
}

//返回文件名
inline QString strippedName(const QString& fullFileName){
	return QFileInfo(fullFileName).fileName();
}

class ChanSpreadsheet : public QMainWindow
{
	Q_OBJECT
		
private:

	//容许的最大最近文件数
	const static size_t MAX_RECENT_FILES = 0x00000005u;
	//信息显示的延迟时间
	const static size_t MESSAGE_DELAY    = 0x000007D0u;

	//生成QAction
	template <typename ParentPtr,typename ShortCutType>
	static void releaseAction(QAction*&,ParentPtr,const char* const, const char* const,
		ShortCutType, const char* const);

public:
	//ctor
	ChanSpreadsheet(QWidget *parent = NULL);

	//删除不必要的函数
	ChanSpreadsheet(const ChanSpreadsheet&) = delete;
	ChanSpreadsheet& operator=(const ChanSpreadsheet&) = delete;
	
protected:
	//关闭事件
	void closeEvent(QCloseEvent*);

private slots:
	void newFile();
	void open();
	bool save();
	bool saveAs();
	void find();
	void goToCell();
	void sort();
	void plot();
	void aboutChanSpreadsheet();
	void openRecentFile();
	void updateStatusBar();
	void chanSpreadsheetModified();
	
private:
	//做一些初始化工作
	void init();
	
private:
	void createActions();

	void createFileMenuAction();
	void createEditMenuAction();
	void createToolMenuAction();
	void createOptionMenuAction();
	void createHelpMenuAction();

	void createMenus();
	void createFileMenu();
	void createEditMenu();
	void createToolMenu();
	void createOptionMenu();
	void createHelpMenu();

	void createContextMenu();
	void createToolBars();
	void createStatusBar();

	void readSettings();
	void writeSettings();
	bool okToContinue();
	bool loadFile(const QString&);
	bool saveFile(const QString&);
	void setCurrentFile(const QString&);
	void updateRecentFileActions();
	void setChanSpreadsheetWindowTitle();

private:
	
	//存放电子表格底层实现
	chanSpreadsheetWidget*	m_chanSpreadSheetWidget;

	//一个显示坐标，一个显示公式	
	QLabel*					m_locationLabel;
	QLabel*					m_formulaLabel;

	//在file 菜单中显示的最近文件名
	QAction*				m_recentFileActions[MAX_RECENT_FILES];

	//菜单栏内容
	QMenu*					m_fileMenu;
	QMenu*					m_editMenu;
	QMenu*					m_toolMenu;
	QMenu*					m_optionMenu;
	QMenu*					m_helpMenu;

	//file的各种动作
	QAction*				m_newFileAction;
	QAction*				m_openAction;
	QAction*				m_saveAction;
	QAction*				m_saveAsAction;
	QAction*				m_exitAction;
	//如果有最近的文件 就要显示这个分割
	QAction*				m_separatorAction;

	//edit的各种动作
	QAction*				m_cutAction;
	QAction*				m_copyAction;
	QAction*				m_pasteAction;
	QMenu*					m_selectSubMenu;
	QAction*				m_selectRowAction;
	QAction*				m_selectColumnAction;
	QAction*				m_selectAllAction;

	//tool 的各种动作	
	QAction*				m_findAction;
	QAction*				m_goToCellAction;
	QAction*				m_sortAction;
	QAction*				m_plotAction;
	QAction*				m_recalculateAction;

	//option的各种动作
	QAction*				m_showGridAction;
	QAction*				m_autoRecalculateAction;

	//help 的各种动作
	QAction*				m_aboutQtAction;
	QAction*				m_aboutChanSpreadsheetAction;	

	//工具栏
	QToolBar*				m_fileToolBar;
	QToolBar*				m_editToolBar;

	//存放历史文件名
	QStringList				m_recentFiles;

	//查找对话框
	findDialog*				m_findDialog;

	//绘图的底层实现
	plotter*				m_plotter;

	//指示当前文件的名字
	QString					m_curFile;
};

#endif // CHANSPREADSHEET_H
