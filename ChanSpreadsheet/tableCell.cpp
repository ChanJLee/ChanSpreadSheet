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

	//设置它的值
	QTableWidgetItem::setData(role, value);

	//如果是edit role 那么设置它的脏位
	if (role == Qt::EditRole)
		setDirty();
}

void tableCell::setDirty(){

	//设置脏位
	m_cacheIsDirty = true;
}

QVariant tableCell::data(int role)const{

	if (role == Qt::DisplayRole){

		//如果是取值 且值是有效的 
		if (value().isValid()){
			//以字符串返回结果
			return value().toString();
		}else return "";
	}

	//如果是文本对齐
	else if (role == Qt::TextAlignmentRole){

		//如果值的类型是文本
		return (value().type() == QVariant::String) ?
			int(Qt::AlignLeft | Qt::AlignVCenter) :

			//如果不是文本
			int(Qt::AlignRight | Qt::AlignVCenter);
	}
	else{

		//否则返回默认的值
		return QTableWidgetItem::data(role);
	}
}

//返回值
QVariant& tableCell::value()const{

	//如果脏位被设置了 那么就要重新计算
	if (m_cacheIsDirty){

		//因为最新值，所以不再设置脏位了
		m_cacheIsDirty = false;
		
		//获得表格中的公式
		QString formulaStr = formula();

		//以 ' 开始的公式
		if (formulaStr.startsWith('\'')){

			//值为之后所有的字符串
			m_cacheValue = formulaStr.mid(1);
		}

		//以 = 开始的公式
		else if (formulaStr.startsWith('=')){

			//获得后面的字符串
			QString exp = formulaStr.mid(1);

			//对字符串进行加工 去掉其中的空格
			exp.replace(" ", "");

			//获得第一个值
			auto first = exp.begin();

			//计算值
			m_cacheValue = evalExpression(first,exp.end());
		}

		//否则就是单纯的公式 或者字符串 下面就开始判断他们
		else{

			//指示转换到double 是否成功
			bool flag = false;
			double result = formulaStr.toDouble(&flag);

			//如果成功就是数字　如果不成功就是字符串
			if (flag) m_cacheValue = result;
			else m_cacheValue = formulaStr;
		}
	}

	//否则返回值
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
			//开始计算
			lhs = op == '+' ? lhs.toDouble() + rhs.toDouble() :
				lhs.toDouble() - rhs.toDouble();

		}
		else return QVariant();//如果检测到错误，那么就不计算了
	}

	//如果都是加减那么就会一直算到结束
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