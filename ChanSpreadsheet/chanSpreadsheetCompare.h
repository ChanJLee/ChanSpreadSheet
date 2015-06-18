#ifndef __CHAN__SPREADSHEET__COMPARE__H__
#define __CHAN__SPREADSHEET__COMPARE__H__

#if defined _MSC_VER && _MSC_VER > 1000
	#pragma once
#endif

class QStringList;

//�º����������Ա���е����ݽ�������

#pragma push(sizeof(int))

class chanSpreadsheetCompare{
	//���ĸ���
	static const size_t KEY_COUNT = 0x00000003u;

	enum { primaryKey, secondaryKey, tertiaryKey };
	enum { primaryOrder, secondaryOrder, tertiaryOrder };
public:
	//�º���
	chanSpreadsheetCompare(int pKey,int sKey,int tKey,bool pOrder,bool sOrder,bool tOrder){

		//�ؼ��ֵ�����
		m_keys[primaryKey]				= pKey;
		m_keys[secondaryKey]			= sKey;
		m_keys[tertiaryKey]				= tKey;

		//�ؼ��ֵ�����
		m_ascending[primaryOrder]		= pOrder;
		m_ascending[secondaryOrder]		= sOrder;
		m_ascending[tertiaryOrder]		= tOrder;
	}

	bool operator()(const QStringList&,const QStringList&)const;

private:
	//��Ҫ������� ���� �ڶ��� ������
	int			m_keys[KEY_COUNT];

	//��������Ӧ�������ǽ���
	bool		m_ascending[KEY_COUNT];
};

#pragma pop()

#endif