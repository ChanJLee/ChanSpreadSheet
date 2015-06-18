#include "chanSpreadsheetCompare.h"
#include <qstringlist.h>

bool chanSpreadsheetCompare::operator()(const QStringList& lhs, const QStringList& rhs)const{
	
	//开始比较三个键值
	for (size_t i = 0; i != KEY_COUNT; ++i){

		//如果键值相同那么就要比较下面的内容  如果没有选择的话就会有负值，这时候直接跳过就可以了
		if (m_keys[i] < 0 || lhs[m_keys[i]] == rhs[m_keys[i]])
			continue;

		//如果之前一个大于后面一个 并且用户选择的还是升序 那么就要进行排序了
		if (m_ascending[i]){
			return lhs[m_keys[i]].toDouble() < rhs[m_keys[i]].toDouble();
		}

		//如果之后一个是大于第一个的 并且用户选择的还是降序 那么就要重新排序
		else{
			return lhs[m_keys[i]].toDouble() > rhs[m_keys[i]].toDouble();
		}
	}

	//如果都相同就没有必要进行排序了
	return false;
}