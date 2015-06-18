#ifndef __CHAN__SPREADSHEET__H__
#define __CHAN__SPREADSHEET__H__

#if defined _MSC_VER && _MSC_VER > 1000
	#pragma once
#endif

#include <qtablewidget.h>
#include <vector>

class tableCell;
class chanSpreadsheetCompare;

class chanSpreadsheetWidget: public QTableWidget{
	Q_OBJECT

private:
	const static size_t MAGIC_NUMBER = 0x7F51C883u;//用来表示chan spreadsheet 的文件格式 
	const static size_t ROW_COUNT	 = 0x000003E7u;//行数
	const static size_t COLUMN_COUNT = 0x0000001Au;//列数

	enum findPolicy{ prev, next };

public:
	chanSpreadsheetWidget(QWidget* = NULL);
	~chanSpreadsheetWidget() = default; //默认的析构就足够了

	//删除copy ctor assign operator
	chanSpreadsheetWidget(const chanSpreadsheetWidget&) = delete;
	chanSpreadsheetWidget& operator =(const chanSpreadsheetWidget&) = delete;

public:
	typedef std::vector<QStringList> QStringListVec;

public:
	//返回当前是否是自动重新计算
	bool autoRecalculate()const { return m_autoRecalc; }

	//当前的坐标
	QString currentLocation()const;

	//当前表格中的公式
	QString currentFormula()const;

	//当前选择的内容
	QStringListVec selectedTableItems()const;

	//选择的范围
	QTableWidgetSelectionRange selectedRange()const;

	//清空所有的数据
	void clear();

	//读取文件
	bool readFile(const QString&);

	//写文件
	bool writeFile(const QString&);

	//对选中的内容进行排序 并使用参数中的仿函数进行排序
	void sort(const chanSpreadsheetCompare&);

public slots:
	void cut();
	void copy();
	void paste();
	void del();
	void selectCurrentRow();
	void selectCurrentColumn();
	void recalculate();
	void findNext(const QString&, Qt::CaseSensitivity);
	void findPrev(const QString&, Qt::CaseSensitivity);
	void setAutoRecalculate(bool autoRecalc);

signals:
	void modified();

private slots:
	void somethingChanged();
	tableCell* cell(int, int)const;
	QString text(int, int)const;
	QString formula(int, int)const;
	void setFormula(int, int, const QString&);

private:
	void findText(const QString&,Qt::CaseSensitivity,findPolicy);
	QString ClipboardStr()const;
private:
	bool m_autoRecalc;
};
 
#endif