#ifndef __CHAN__SPREADSHEET__COMPARE__H__
#define __CHAN__SPREADSHEET__COMPARE__H__

#if defined _MSC_VER && _MSC_VER > 1000
	#pragma once
#endif

class QStringList;

//仿函数，用来对表格中的内容进行排序

#pragma push(sizeof(int))

class chanSpreadsheetCompare{
	//键的个数
	static const size_t KEY_COUNT = 0x00000003u;

	enum { primaryKey, secondaryKey, tertiaryKey };
	enum { primaryOrder, secondaryOrder, tertiaryOrder };
public:
	//仿函数
	chanSpreadsheetCompare(int pKey,int sKey,int tKey,bool pOrder,bool sOrder,bool tOrder){

		//关键字的设置
		m_keys[primaryKey]				= pKey;
		m_keys[secondaryKey]			= sKey;
		m_keys[tertiaryKey]				= tKey;

		//关键字的排序
		m_ascending[primaryOrder]		= pOrder;
		m_ascending[secondaryOrder]		= sOrder;
		m_ascending[tertiaryOrder]		= tOrder;
	}

	bool operator()(const QStringList&,const QStringList&)const;

private:
	//需要排序的列 主键 第二键 第三键
	int			m_keys[KEY_COUNT];

	//三个键对应的升序还是降序
	bool		m_ascending[KEY_COUNT];
};

#pragma pop()

#endif