#include "chanSpreadsheetWidget.h"
#include "tableCell.h"
#include <qfile.h>
#include <qdatastream.h>
#include <qmessagebox.h>
#include <qapplication.h>
#include <utility>
#include <qclipboard.h>
#include <list>
#include <chanSpreadsheetCompare.h>


chanSpreadsheetWidget::chanSpreadsheetWidget(QWidget* parent):
QTableWidget(parent),
m_autoRecalc(true){

	//设置项原型
	setItemPrototype(new tableCell);

	//设置选择的模式
	setSelectionMode(ContiguousSelection);

	//只要有项改变　就发射信号
	connect(this, SIGNAL(itemChanged(QTableWidgetItem*)),
		this, SLOT(somethingChanged()));

	//清空整个表格，建立一个新的表格
	clear();
}

void chanSpreadsheetWidget::clear(){

	//清空行列
	setRowCount(0);
	setColumnCount(0);

	//重新设置
	setRowCount(ROW_COUNT);
	setColumnCount(COLUMN_COUNT);


	QTableWidgetItem* item = NULL;

	for (int i = 0; i != ROW_COUNT;++i){

		//分配一个项
		item = new QTableWidgetItem;

		//设置文本内容
		item->setText(QString(QChar('A' + i)));

		//设置水平的头项
		setHorizontalHeaderItem(i, item);
	}

	//以原点为默认的选择
	setCurrentCell(0, 0);
}

inline tableCell* chanSpreadsheetWidget::cell(int row, int column)const{
	return static_cast<tableCell*>(item(row,column));
}

QString chanSpreadsheetWidget::text(int row, int column)const{

	//获得cell
	tableCell* c = cell(row, column);

	//如果不为空就范围当前的内容 否则是一个默认的内容
	return c != NULL ? c->text() : QString();
}

QString chanSpreadsheetWidget::formula(int row, int column)const{

	tableCell* c = cell(row, column);

	//获得表格项中的公式
	return c != NULL ? c->formula() : QString();
}

void chanSpreadsheetWidget::setFormula(int row, int column, const QString& formula){

	tableCell* c = cell(row, column);

	//如果当前的还是没有分配内存的表格项 那么就分配一个
	if (c == NULL){
		c = new tableCell;

		//设置项
		setItem(row, column, c);
	}

	//设置公式
	c->setFormula(formula);
}

QString chanSpreadsheetWidget::currentLocation()const{

	//当前坐标的格式　第一个为列　第二个为行
	return QChar('A' + currentColumn()) +
		QString::number(currentRow() + 1);
}

QString chanSpreadsheetWidget::currentFormula()const{

	//返回公式
	return formula(currentRow(), currentColumn());
}

void chanSpreadsheetWidget::somethingChanged(){

	//如果设置了自动计算　那么就自动计算
	if (m_autoRecalc)
		recalculate();

	//发射修改过的信号
	emit modified();
}

bool chanSpreadsheetWidget::writeFile(const QString& fileName){

	//打开文件
	QFile file(fileName);

	//只读打开失败 
	if (!file.open(QIODevice::WriteOnly)){
		QMessageBox::warning(this,

			//第一个文件名　第二个错误信息
			tr("Chan Spreadsheet warning"),
			tr("can not write file %1:\n%2")
			.arg(fileName).arg(file.errorString()));

		//返回false 指示失败
		return false;
	}

	//建立一个写流
	QDataStream out(&file);

	//设置版本
	out.setVersion(QDataStream::Qt_4_3);

	//用来表示一个chan spreadsheet 文件
	out << quint32(MAGIC_NUMBER);

	//设置忙等待光标
	QApplication::setOverrideCursor(Qt::WaitCursor);

	for (size_t x = 0; x != COLUMN_COUNT; ++x){
		for (size_t y = 0; y != ROW_COUNT; ++y){

			QString fml = formula(y, x);

			if (!fml.isEmpty())
				out << quint16(x) << quint16(y) << fml;
		}
	}

	//设置为普通光标
	QApplication::restoreOverrideCursor();

	//返回true 指示成功
	return true;
}

bool chanSpreadsheetWidget::readFile(const QString& fileName){
	
	//读取文件
	QFile file(fileName);

	if (!file.open(QIODevice::ReadOnly)){
		QMessageBox::warning(this,

			//第一个文件名　第二个错误信息
			tr("Chan Spreadsheet warning"),
			tr("can not read file %1:\n%2")
			.arg(fileName).arg(file.errorString()));

		//返回false 指示失败
		return false;
	}

	//读取流
	QDataStream in(&file);

	//设置读取流的版本
	in.setVersion(QDataStream::Qt_4_3);

	//验证是否为chan spreadsheet文件
	quint32 magic;

	in >> magic;

	if (magic != MAGIC_NUMBER){
		QMessageBox::warning(this,

			//错误信息
			tr("Chan Spreadsheet warning"),
			tr("the file is not a Chan Spreadsheet file"));

		//返回false 指示失败
		return false;
	}

	//x y 坐标　公式
	quint16 x, y;
	QString fml;

	//设置忙等待光标
	QApplication::setOverrideCursor(Qt::WaitCursor);

	//当还没有到文件尾
	while (!in.atEnd()){
		
		//读取
		in >> x >> y >> fml;

		//设置公式
		setFormula(y, x, fml);
	}

	//重新设置光标为正常
	QApplication::restoreOverrideCursor();

	//返回true 指示成功
	return true;
}

chanSpreadsheetWidget::QStringListVec chanSpreadsheetWidget::selectedTableItems()const{

	//获得宽
	QTableWidgetSelectionRange range = selectedRange();

	//获得宽
	size_t width = range.rightColumn() - range.leftColumn() + 1;

	QStringListVec result(width);

	//用于访问result内容
	size_t rowIndex = 0;

	//选中的内容
	QList<QTableWidgetItem*> list = selectedItems();

	//把每一行的内容放入
	std::for_each(list.begin(), list.end(), [&](QTableWidgetItem* item){

		result[rowIndex].push_back(formula(item->row(), item->column()));

		rowIndex = (rowIndex + 1) % width;
	});

	//返回值
	return std::move(result);
}

QString chanSpreadsheetWidget::ClipboardStr()const{

	//获得选择的范围
	QTableWidgetSelectionRange range = selectedRange();

	QString items;

	for (int x = 0; x < range.columnCount(); ++x){

		//如果不是第一列 那么之后的每一列都放一个\n于其后
		if (x != 0){
			items += '\n';
		}

		for (int y = 0; y < range.rowCount(); ++y){

			//如果不是第一行 那么就加一个
			if (y != 0)
				items += '\t';

			//把表格中的内容加进最后的结果中
			items += formula(range.topRow() + y, range.leftColumn() + x);
		}
	}

	//返回结果
	return std::move(items);
}

void chanSpreadsheetWidget::cut(){

	//剪切操作 先拷贝 后删除选中的内容
	copy();
	del();
}

void chanSpreadsheetWidget::copy(){

	//选中结果
	QApplication::clipboard()->setText(ClipboardStr());
}

QTableWidgetSelectionRange chanSpreadsheetWidget::selectedRange()const{

	//获得选中的范围
	QList<QTableWidgetSelectionRange> ranges = selectedRanges();

	//因为之前在ctor中设置的 因此只可能被选中一个区域 就算没有选择 Qt也会返回当前的单元格
	return ranges.isEmpty() ? QTableWidgetSelectionRange() :
		*ranges.begin();
}

//最后修改时间 2015/1/17 11：11
void chanSpreadsheetWidget::paste(){

	//获得剪切板中的内容
	QString items = QApplication::clipboard()->text();

	//获得选择的范围
	QTableWidgetSelectionRange range = selectedRange();

	//分裂得到列
	QStringList columns = items.split('\n');

	//列大小
	const size_t columnSize = columns.size();

	//行大小
	const size_t rowSize = columns.first().count('\t') + 1;

	//如果剪切板中的内容!等于一个格子，就要判断要粘连的地方大小是否和剪切板中的相同
	if (rowSize * columnSize != 1 
		&& ((range.columnCount() != columnSize) ||
		(range.rowCount() != rowSize))){

		//如果大小不同
		QMessageBox::warning(this, tr("Chan Spreadsheet"),
			tr("The information can not be pasted beacause the"
			"copy and paste areas are not the same size"));

		//返回
		return;
	}

	//用于遍历列
	size_t x = 0;

	std::for_each(columns.begin(), columns.end(), [&,this](const QString& column){

		//解开行内容
		QStringList rows = column.split('\t');

		//用于遍历行
		size_t  y = 0;

		std::for_each(rows.begin(), rows.end(), [&,this](const QString& item){

			//获得要插入地点的实际坐标
			const size_t row = range.topRow() + y;
			const size_t column = range.leftColumn() + x;

			//如果在表格内就设置
			if (row < ROW_COUNT && column < COLUMN_COUNT)
				setFormula(row, column, item);
			++y;
		});
		++x;
	});

	//发射修改了的信号
	somethingChanged();
}

void chanSpreadsheetWidget::del(){

	//找到选择的项
	QList<QTableWidgetItem*> result = selectedItems();

	std::for_each(result.begin(), result.end(), [=](QTableWidgetItem* item){ delete item; });

	//如果不是空的 那么就发射信号
	if (!result.empty()) somethingChanged();
}


void chanSpreadsheetWidget::selectCurrentRow(){

	//选择当前的行
	selectRow(currentRow());
}

void chanSpreadsheetWidget::selectCurrentColumn(){

	//选择当前的列
	selectColumn(currentColumn());
}

void chanSpreadsheetWidget::findNext(const QString& item, Qt::CaseSensitivity cs){

	//查找之后的
	findText(item, cs, findPolicy::next);
}


void chanSpreadsheetWidget::findPrev(const QString& item, Qt::CaseSensitivity cs){

	//查找之前的
	findText(item, cs, findPolicy::prev);
}

void chanSpreadsheetWidget::findText(const QString& item,
	Qt::CaseSensitivity cs, findPolicy model){

	//获得x y 坐标
	int x = currentColumn();
	int y = currentRow();

	//查找符合要求的内容 如果要求大小写区分 那么就区分大小写 否则只要包含就可以了
	QList<QTableWidgetItem*> result = cs == Qt::CaseSensitive ?
		findItems(item, Qt::MatchFlag::MatchCaseSensitive) :
		findItems(item, Qt::MatchFlag::MatchContains);

	//找到符合结果的目标
	QList<QTableWidgetItem*>::iterator it = std::find_if(result.begin(), result.end(),
		[&, this](QTableWidgetItem* item){
		if (model == findPolicy::prev)
			return (item->column() < x || item->row() < y) ? true : false;
		else return (item->column() > x || item->row() > y) ? true : false; 
	});

	//如果找到了
	if (it != result.end()){

		//清除选择
		clearSelection();

		//设置当前的cell
		setCurrentCell((*it)->row(), (*it)->column());

		//设置窗口为活动
		activateWindow();

		//找到了就返回
		return;
	}

	//没找到就发出声音提醒用户
	QApplication::beep();
}

void chanSpreadsheetWidget::recalculate(){

	//如果有cell 则设其为脏 那么update 的时候会调用text自然对其进行计算
	//备注：计算在text中
	for (size_t x = 0; x != COLUMN_COUNT; ++x){

		for (size_t y = 0; y != ROW_COUNT; ++y){
			if (cell(y, x) != NULL)
				cell(y, x)->setDirty();
		}
	}

	//重绘
	viewport()->update();
}

void chanSpreadsheetWidget::setAutoRecalculate(bool recalc){

	//设置自动计算
	m_autoRecalc = recalc;

	if (m_autoRecalc) recalculate();
}

//最后修改时间 2015/1/18 9：03
void chanSpreadsheetWidget::sort(const chanSpreadsheetCompare& predicate){

	//可能会返回null cell
	QList<QTableWidgetItem*> items = selectedItems();

	//存放选中区域的结果
	std::list<QStringList> list;

	//存放每一行的文本
	QStringList rowText;

	//获得选择的范围 以此知道选择的宽
	QTableWidgetSelectionRange range = selectedRange();

	//获得选择范围的宽
	size_t width = range.rightColumn() - range.leftColumn() + 1;

	//这里不确定 items 中的顺序，我们默认的是 从左到右 从上到下
	//提取每行
	std::for_each(items.begin(), items.end(), [&](QTableWidgetItem* item){

		//将内容放进row text中
		rowText.push_back(formula(item->row(), item->column()));

		//如果需要换行 这里需要频繁的测试rowtext 的大小，因此stl库的list就不再合适，于是我使用的是qt自带的
		if (!(rowText.size() % width)){
			list.push_front(std::move(rowText));
			rowText.clear();
		}
			
	});

	//对内容进行排序
	list.sort(predicate);

	//将排序后的内容放回到原本的区域
	QList<QTableWidgetItem*>::iterator it = items.begin();

	std::for_each(list.begin(), list.end(), [&](QStringList& rowText){
		
		//对于每一行的文本 如果当前的表格项不是空的 那么就把它放入进选择的区域中
		std::for_each(rowText.begin(), rowText.end(), [&](QString& item){
			setFormula((*it)->row(), (*it)->column(), std::move(item));
			++it;
		});
	});

	//清空选择
	clearSelection();

	//发射有修改的信号
	somethingChanged();
}


