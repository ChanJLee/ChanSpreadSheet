#include "tableCell.h"
#include <qchar.h>

tableCell::tableCell(){
	setDirty();
}

QTableWidgetItem* tableCell::clone()const{
	return new tableCell;
}

void tableCell::setFormula(const QString& formula){
	setData(Qt::EditRole, formula);
}

QString tableCell::formula()const{
	return data(Qt::EditRole).toString();
}

void tableCell::setData(int role, const QVariant& value){

	//��������ֵ
	QTableWidgetItem::setData(role, value);

	//�����edit role ��ô����������λ
	if (role == Qt::EditRole)
		setDirty();
}

void tableCell::setDirty(){

	//������λ
	m_cacheIsDirty = true;
}

QVariant tableCell::data(int role)const{

	if (role == Qt::DisplayRole){

		//�����ȡֵ ��ֵ����Ч�� 
		if (value().isValid()){
			//���ַ������ؽ��
			return value().toString();
		}else return "";
	}

	//������ı�����
	else if (role == Qt::TextAlignmentRole){

		//���ֵ���������ı�
		return (value().type() == QVariant::String) ?
			int(Qt::AlignLeft | Qt::AlignVCenter) :

			//��������ı�
			int(Qt::AlignRight | Qt::AlignVCenter);
	}
	else{

		//���򷵻�Ĭ�ϵ�ֵ
		return QTableWidgetItem::data(role);
	}
}

//����ֵ
QVariant& tableCell::value()const{

	//�����λ�������� ��ô��Ҫ���¼���
	if (m_cacheIsDirty){

		//��Ϊ����ֵ�����Բ���������λ��
		m_cacheIsDirty = false;
		
		//��ñ���еĹ�ʽ
		QString formulaStr = formula();

		//�� ' ��ʼ�Ĺ�ʽ
		if (formulaStr.startsWith('\'')){

			//ֵΪ֮�����е��ַ���
			m_cacheValue = formulaStr.mid(1);
		}

		//�� = ��ʼ�Ĺ�ʽ
		else if (formulaStr.startsWith('=')){

			//��ú�����ַ���
			QString exp = formulaStr.mid(1);

			//���ַ������мӹ� ȥ�����еĿո�
			exp.replace(" ", "");

			//��õ�һ��ֵ
			auto first = exp.begin();

			//����ֵ
			m_cacheValue = evalExpression(first,exp.end());
		}

		//������ǵ����Ĺ�ʽ �����ַ��� ����Ϳ�ʼ�ж�����
		else{

			//ָʾת����double �Ƿ�ɹ�
			bool flag = false;
			double result = formulaStr.toDouble(&flag);

			//����ɹ��������֡�������ɹ������ַ���
			if (flag) m_cacheValue = result;
			else m_cacheValue = formulaStr;
		}
	}

	//���򷵻�ֵ
	return m_cacheValue;
}

QVariant tableCell::evalExpression(expressionIterator& first,expressionIterator end)const{

	QVariant lhs = evalTerm(first, end);

	while (first != end){
		QChar op = *first;
		if (op != '+' && op != '-')
			return lhs;
		++first;

		QVariant rhs = evalTerm(first, end);

		if (lhs.type() == QVariant::Double &&
			rhs.type() == QVariant::Double){
			//��ʼ����
			lhs = op == '+' ? lhs.toDouble() + rhs.toDouble() :
				lhs.toDouble() - rhs.toDouble();

		}
		else return QVariant();//�����⵽������ô�Ͳ�������
	}

	//������ǼӼ���ô�ͻ�һֱ�㵽����
	return lhs;
}

QVariant tableCell::evalTerm(expressionIterator& first, expressionIterator end)const{
	QVariant lhs = evalFactor(first, end);

	while (first != end){
		QChar op = *first;

		if (op != '*' && op != '/')
			return lhs;
		++first;

		QVariant rhs = evalFactor(first, end);

		if (lhs.type() == QVariant::Double &&
			rhs.type() == QVariant::Double){
			if (op == '*')
				lhs = lhs.toDouble() * rhs.toDouble();
			else{
				if (rhs.toDouble() == 0)
					return QVariant();
				lhs = lhs.toDouble() / rhs.toDouble();
			}
		}
		else return QVariant();
	}

	return lhs;
}

QVariant tableCell::evalFactor(expressionIterator& first, expressionIterator end)const{

	if (first == end) return QVariant();

	QVariant result;
	bool negative = false;

	if (*first == '-'){
		negative = true;
		++first;
	}

	if (*first == '('){
		result = evalExpression((++first),end);
		if (*first++ != ')')
			return QVariant();
	}
	else{
		QRegExp regExp("[A-Za-z][1-9][0-9]{0,2}");
		QString token;
		
		
		while (QChar::isLetterOrNumber((*first).unicode()) || *first == '.'){
			token += *first;
			++first;
		}

		if (regExp.exactMatch(token)){

			int x = token.mid(1).toInt() - 1;
			int y = token[0].toUpper().unicode() - 'A';
			tableCell* src = static_cast<tableCell*>(tableWidget()->item(x, y));

			if (src == NULL) return 0.0;
			else result = src->value();

		}
		else{
			bool flag;
			result = token.toDouble(&flag);
			if (!flag) return QVariant();
		}
	}

	return negative ? -result.toDouble() : result;
}