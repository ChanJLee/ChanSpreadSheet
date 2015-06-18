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
	const static size_t MAGIC_NUMBER = 0x7F51C883u;//������ʾchan spreadsheet ���ļ���ʽ 
	const static size_t ROW_COUNT	 = 0x000003E7u;//����
	const static size_t COLUMN_COUNT = 0x0000001Au;//����

	enum findPolicy{ prev, next };

public:
	chanSpreadsheetWidget(QWidget* = NULL);
	~chanSpreadsheetWidget() = default; //Ĭ�ϵ��������㹻��

	//ɾ��copy ctor assign operator
	chanSpreadsheetWidget(const chanSpreadsheetWidget&) = delete;
	chanSpreadsheetWidget& operator =(const chanSpreadsheetWidget&) = delete;

public:
	typedef std::vector<QStringList> QStringListVec;

public:
	//���ص�ǰ�Ƿ����Զ����¼���
	bool autoRecalculate()const { return m_autoRecalc; }

	//��ǰ������
	QString currentLocation()const;

	//��ǰ����еĹ�ʽ
	QString currentFormula()const;

	//��ǰѡ�������
	QStringListVec selectedTableItems()const;

	//ѡ��ķ�Χ
	QTableWidgetSelectionRange selectedRange()const;

	//������е�����
	void clear();

	//��ȡ�ļ�
	bool readFile(const QString&);

	//д�ļ�
	bool writeFile(const QString&);

	//��ѡ�е����ݽ������� ��ʹ�ò����еķº�����������
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