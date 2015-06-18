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


//ͼ����Դ�ļ�
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
	//��ŵ�ϵͳ�е�λ��
	const QString organization = "Software Inc.";
	//����
	const QString application   = "Chan Spreadsheet";
	//�汾��

	//����汾�ŵĺ�
#	if !defined CSP_VER 
#		define CSP_VER 1.2
#	endif

	const QString version		= "1.2";
	const QString geometry		= "geometry";
	const QString recentFiles	= "recentFiles";
	const QString showGrid		= "showGrid";
	const QString autoRecalc	= "aytiRecalc";
}

//�����ļ���
inline QString strippedName(const QString& fullFileName){
	return QFileInfo(fullFileName).fileName();
}

class ChanSpreadsheet : public QMainWindow
{
	Q_OBJECT
		
private:

	//������������ļ���
	const static size_t MAX_RECENT_FILES = 0x00000005u;
	//��Ϣ��ʾ���ӳ�ʱ��
	const static size_t MESSAGE_DELAY    = 0x000007D0u;

	//����QAction
	template <typename ParentPtr,typename ShortCutType>
	static void releaseAction(QAction*&,ParentPtr,const char* const, const char* const,
		ShortCutType, const char* const);

public:
	//ctor
	ChanSpreadsheet(QWidget *parent = NULL);

	//ɾ������Ҫ�ĺ���
	ChanSpreadsheet(const ChanSpreadsheet&) = delete;
	ChanSpreadsheet& operator=(const ChanSpreadsheet&) = delete;
	
protected:
	//�ر��¼�
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
	//��һЩ��ʼ������
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
	
	//��ŵ��ӱ��ײ�ʵ��
	chanSpreadsheetWidget*	m_chanSpreadSheetWidget;

	//һ����ʾ���꣬һ����ʾ��ʽ	
	QLabel*					m_locationLabel;
	QLabel*					m_formulaLabel;

	//��file �˵�����ʾ������ļ���
	QAction*				m_recentFileActions[MAX_RECENT_FILES];

	//�˵�������
	QMenu*					m_fileMenu;
	QMenu*					m_editMenu;
	QMenu*					m_toolMenu;
	QMenu*					m_optionMenu;
	QMenu*					m_helpMenu;

	//file�ĸ��ֶ���
	QAction*				m_newFileAction;
	QAction*				m_openAction;
	QAction*				m_saveAction;
	QAction*				m_saveAsAction;
	QAction*				m_exitAction;
	//�����������ļ� ��Ҫ��ʾ����ָ�
	QAction*				m_separatorAction;

	//edit�ĸ��ֶ���
	QAction*				m_cutAction;
	QAction*				m_copyAction;
	QAction*				m_pasteAction;
	QMenu*					m_selectSubMenu;
	QAction*				m_selectRowAction;
	QAction*				m_selectColumnAction;
	QAction*				m_selectAllAction;

	//tool �ĸ��ֶ���	
	QAction*				m_findAction;
	QAction*				m_goToCellAction;
	QAction*				m_sortAction;
	QAction*				m_plotAction;
	QAction*				m_recalculateAction;

	//option�ĸ��ֶ���
	QAction*				m_showGridAction;
	QAction*				m_autoRecalculateAction;

	//help �ĸ��ֶ���
	QAction*				m_aboutQtAction;
	QAction*				m_aboutChanSpreadsheetAction;	

	//������
	QToolBar*				m_fileToolBar;
	QToolBar*				m_editToolBar;

	//�����ʷ�ļ���
	QStringList				m_recentFiles;

	//���ҶԻ���
	findDialog*				m_findDialog;

	//��ͼ�ĵײ�ʵ��
	plotter*				m_plotter;

	//ָʾ��ǰ�ļ�������
	QString					m_curFile;
};

#endif // CHANSPREADSHEET_H
