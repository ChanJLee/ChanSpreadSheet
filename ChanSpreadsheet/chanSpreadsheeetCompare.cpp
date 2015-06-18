#include "chanSpreadsheetCompare.h"
#include <qstringlist.h>

bool chanSpreadsheetCompare::operator()(const QStringList& lhs, const QStringList& rhs)const{
	
	//��ʼ�Ƚ�������ֵ
	for (size_t i = 0; i != KEY_COUNT; ++i){

		//�����ֵ��ͬ��ô��Ҫ�Ƚ����������  ���û��ѡ��Ļ��ͻ��и�ֵ����ʱ��ֱ�������Ϳ�����
		if (m_keys[i] < 0 || lhs[m_keys[i]] == rhs[m_keys[i]])
			continue;

		//���֮ǰһ�����ں���һ�� �����û�ѡ��Ļ������� ��ô��Ҫ����������
		if (m_ascending[i]){
			return lhs[m_keys[i]].toDouble() < rhs[m_keys[i]].toDouble();
		}

		//���֮��һ���Ǵ��ڵ�һ���� �����û�ѡ��Ļ��ǽ��� ��ô��Ҫ��������
		else{
			return lhs[m_keys[i]].toDouble() > rhs[m_keys[i]].toDouble();
		}
	}

	//�������ͬ��û�б�Ҫ����������
	return false;
}