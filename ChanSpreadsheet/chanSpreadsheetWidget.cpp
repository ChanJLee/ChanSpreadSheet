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

	//������ԭ��
	setItemPrototype(new tableCell);

	//����ѡ���ģʽ
	setSelectionMode(ContiguousSelection);

	//ֻҪ����ı䡡�ͷ����ź�
	connect(this, SIGNAL(itemChanged(QTableWidgetItem*)),
		this, SLOT(somethingChanged()));

	//���������񣬽���һ���µı��
	clear();
}

void chanSpreadsheetWidget::clear(){

	//�������
	setRowCount(0);
	setColumnCount(0);

	//��������
	setRowCount(ROW_COUNT);
	setColumnCount(COLUMN_COUNT);


	QTableWidgetItem* item = NULL;

	for (int i = 0; i != ROW_COUNT;++i){

		//����һ����
		item = new QTableWidgetItem;

		//�����ı�����
		item->setText(QString(QChar('A' + i)));

		//����ˮƽ��ͷ��
		setHorizontalHeaderItem(i, item);
	}

	//��ԭ��ΪĬ�ϵ�ѡ��
	setCurrentCell(0, 0);
}

inline tableCell* chanSpreadsheetWidget::cell(int row, int column)const{
	return static_cast<tableCell*>(item(row,column));
}

QString chanSpreadsheetWidget::text(int row, int column)const{

	//���cell
	tableCell* c = cell(row, column);

	//�����Ϊ�վͷ�Χ��ǰ������ ������һ��Ĭ�ϵ�����
	return c != NULL ? c->text() : QString();
}

QString chanSpreadsheetWidget::formula(int row, int column)const{

	tableCell* c = cell(row, column);

	//��ñ�����еĹ�ʽ
	return c != NULL ? c->formula() : QString();
}

void chanSpreadsheetWidget::setFormula(int row, int column, const QString& formula){

	tableCell* c = cell(row, column);

	//�����ǰ�Ļ���û�з����ڴ�ı���� ��ô�ͷ���һ��
	if (c == NULL){
		c = new tableCell;

		//������
		setItem(row, column, c);
	}

	//���ù�ʽ
	c->setFormula(formula);
}

QString chanSpreadsheetWidget::currentLocation()const{

	//��ǰ����ĸ�ʽ����һ��Ϊ�С��ڶ���Ϊ��
	return QChar('A' + currentColumn()) +
		QString::number(currentRow() + 1);
}

QString chanSpreadsheetWidget::currentFormula()const{

	//���ع�ʽ
	return formula(currentRow(), currentColumn());
}

void chanSpreadsheetWidget::somethingChanged(){

	//����������Զ����㡡��ô���Զ�����
	if (m_autoRecalc)
		recalculate();

	//�����޸Ĺ����ź�
	emit modified();
}

bool chanSpreadsheetWidget::writeFile(const QString& fileName){

	//���ļ�
	QFile file(fileName);

	//ֻ����ʧ�� 
	if (!file.open(QIODevice::WriteOnly)){
		QMessageBox::warning(this,

			//��һ���ļ������ڶ���������Ϣ
			tr("Chan Spreadsheet warning"),
			tr("can not write file %1:\n%2")
			.arg(fileName).arg(file.errorString()));

		//����false ָʾʧ��
		return false;
	}

	//����һ��д��
	QDataStream out(&file);

	//���ð汾
	out.setVersion(QDataStream::Qt_4_3);

	//������ʾһ��chan spreadsheet �ļ�
	out << quint32(MAGIC_NUMBER);

	//����æ�ȴ����
	QApplication::setOverrideCursor(Qt::WaitCursor);

	for (size_t x = 0; x != COLUMN_COUNT; ++x){
		for (size_t y = 0; y != ROW_COUNT; ++y){

			QString fml = formula(y, x);

			if (!fml.isEmpty())
				out << quint16(x) << quint16(y) << fml;
		}
	}

	//����Ϊ��ͨ���
	QApplication::restoreOverrideCursor();

	//����true ָʾ�ɹ�
	return true;
}

bool chanSpreadsheetWidget::readFile(const QString& fileName){
	
	//��ȡ�ļ�
	QFile file(fileName);

	if (!file.open(QIODevice::ReadOnly)){
		QMessageBox::warning(this,

			//��һ���ļ������ڶ���������Ϣ
			tr("Chan Spreadsheet warning"),
			tr("can not read file %1:\n%2")
			.arg(fileName).arg(file.errorString()));

		//����false ָʾʧ��
		return false;
	}

	//��ȡ��
	QDataStream in(&file);

	//���ö�ȡ���İ汾
	in.setVersion(QDataStream::Qt_4_3);

	//��֤�Ƿ�Ϊchan spreadsheet�ļ�
	quint32 magic;

	in >> magic;

	if (magic != MAGIC_NUMBER){
		QMessageBox::warning(this,

			//������Ϣ
			tr("Chan Spreadsheet warning"),
			tr("the file is not a Chan Spreadsheet file"));

		//����false ָʾʧ��
		return false;
	}

	//x y ���ꡡ��ʽ
	quint16 x, y;
	QString fml;

	//����æ�ȴ����
	QApplication::setOverrideCursor(Qt::WaitCursor);

	//����û�е��ļ�β
	while (!in.atEnd()){
		
		//��ȡ
		in >> x >> y >> fml;

		//���ù�ʽ
		setFormula(y, x, fml);
	}

	//�������ù��Ϊ����
	QApplication::restoreOverrideCursor();

	//����true ָʾ�ɹ�
	return true;
}

chanSpreadsheetWidget::QStringListVec chanSpreadsheetWidget::selectedTableItems()const{

	//��ÿ�
	QTableWidgetSelectionRange range = selectedRange();

	//��ÿ�
	size_t width = range.rightColumn() - range.leftColumn() + 1;

	QStringListVec result(width);

	//���ڷ���result����
	size_t rowIndex = 0;

	//ѡ�е�����
	QList<QTableWidgetItem*> list = selectedItems();

	//��ÿһ�е����ݷ���
	std::for_each(list.begin(), list.end(), [&](QTableWidgetItem* item){

		result[rowIndex].push_back(formula(item->row(), item->column()));

		rowIndex = (rowIndex + 1) % width;
	});

	//����ֵ
	return std::move(result);
}

QString chanSpreadsheetWidget::ClipboardStr()const{

	//���ѡ��ķ�Χ
	QTableWidgetSelectionRange range = selectedRange();

	QString items;

	for (int x = 0; x < range.columnCount(); ++x){

		//������ǵ�һ�� ��ô֮���ÿһ�ж���һ��\n�����
		if (x != 0){
			items += '\n';
		}

		for (int y = 0; y < range.rowCount(); ++y){

			//������ǵ�һ�� ��ô�ͼ�һ��
			if (y != 0)
				items += '\t';

			//�ѱ���е����ݼӽ����Ľ����
			items += formula(range.topRow() + y, range.leftColumn() + x);
		}
	}

	//���ؽ��
	return std::move(items);
}

void chanSpreadsheetWidget::cut(){

	//���в��� �ȿ��� ��ɾ��ѡ�е�����
	copy();
	del();
}

void chanSpreadsheetWidget::copy(){

	//ѡ�н��
	QApplication::clipboard()->setText(ClipboardStr());
}

QTableWidgetSelectionRange chanSpreadsheetWidget::selectedRange()const{

	//���ѡ�еķ�Χ
	QList<QTableWidgetSelectionRange> ranges = selectedRanges();

	//��Ϊ֮ǰ��ctor�����õ� ���ֻ���ܱ�ѡ��һ������ ����û��ѡ�� QtҲ�᷵�ص�ǰ�ĵ�Ԫ��
	return ranges.isEmpty() ? QTableWidgetSelectionRange() :
		*ranges.begin();
}

//����޸�ʱ�� 2015/1/17 11��11
void chanSpreadsheetWidget::paste(){

	//��ü��а��е�����
	QString items = QApplication::clipboard()->text();

	//���ѡ��ķ�Χ
	QTableWidgetSelectionRange range = selectedRange();

	//���ѵõ���
	QStringList columns = items.split('\n');

	//�д�С
	const size_t columnSize = columns.size();

	//�д�С
	const size_t rowSize = columns.first().count('\t') + 1;

	//������а��е�����!����һ�����ӣ���Ҫ�ж�Ҫճ���ĵط���С�Ƿ�ͼ��а��е���ͬ
	if (rowSize * columnSize != 1 
		&& ((range.columnCount() != columnSize) ||
		(range.rowCount() != rowSize))){

		//�����С��ͬ
		QMessageBox::warning(this, tr("Chan Spreadsheet"),
			tr("The information can not be pasted beacause the"
			"copy and paste areas are not the same size"));

		//����
		return;
	}

	//���ڱ�����
	size_t x = 0;

	std::for_each(columns.begin(), columns.end(), [&,this](const QString& column){

		//�⿪������
		QStringList rows = column.split('\t');

		//���ڱ�����
		size_t  y = 0;

		std::for_each(rows.begin(), rows.end(), [&,this](const QString& item){

			//���Ҫ����ص��ʵ������
			const size_t row = range.topRow() + y;
			const size_t column = range.leftColumn() + x;

			//����ڱ���ھ�����
			if (row < ROW_COUNT && column < COLUMN_COUNT)
				setFormula(row, column, item);
			++y;
		});
		++x;
	});

	//�����޸��˵��ź�
	somethingChanged();
}

void chanSpreadsheetWidget::del(){

	//�ҵ�ѡ�����
	QList<QTableWidgetItem*> result = selectedItems();

	std::for_each(result.begin(), result.end(), [=](QTableWidgetItem* item){ delete item; });

	//������ǿյ� ��ô�ͷ����ź�
	if (!result.empty()) somethingChanged();
}


void chanSpreadsheetWidget::selectCurrentRow(){

	//ѡ��ǰ����
	selectRow(currentRow());
}

void chanSpreadsheetWidget::selectCurrentColumn(){

	//ѡ��ǰ����
	selectColumn(currentColumn());
}

void chanSpreadsheetWidget::findNext(const QString& item, Qt::CaseSensitivity cs){

	//����֮���
	findText(item, cs, findPolicy::next);
}


void chanSpreadsheetWidget::findPrev(const QString& item, Qt::CaseSensitivity cs){

	//����֮ǰ��
	findText(item, cs, findPolicy::prev);
}

void chanSpreadsheetWidget::findText(const QString& item,
	Qt::CaseSensitivity cs, findPolicy model){

	//���x y ����
	int x = currentColumn();
	int y = currentRow();

	//���ҷ���Ҫ������� ���Ҫ���Сд���� ��ô�����ִ�Сд ����ֻҪ�����Ϳ�����
	QList<QTableWidgetItem*> result = cs == Qt::CaseSensitive ?
		findItems(item, Qt::MatchFlag::MatchCaseSensitive) :
		findItems(item, Qt::MatchFlag::MatchContains);

	//�ҵ����Ͻ����Ŀ��
	QList<QTableWidgetItem*>::iterator it = std::find_if(result.begin(), result.end(),
		[&, this](QTableWidgetItem* item){
		if (model == findPolicy::prev)
			return (item->column() < x || item->row() < y) ? true : false;
		else return (item->column() > x || item->row() > y) ? true : false; 
	});

	//����ҵ���
	if (it != result.end()){

		//���ѡ��
		clearSelection();

		//���õ�ǰ��cell
		setCurrentCell((*it)->row(), (*it)->column());

		//���ô���Ϊ�
		activateWindow();

		//�ҵ��˾ͷ���
		return;
	}

	//û�ҵ��ͷ������������û�
	QApplication::beep();
}

void chanSpreadsheetWidget::recalculate(){

	//�����cell ������Ϊ�� ��ôupdate ��ʱ������text��Ȼ������м���
	//��ע��������text��
	for (size_t x = 0; x != COLUMN_COUNT; ++x){

		for (size_t y = 0; y != ROW_COUNT; ++y){
			if (cell(y, x) != NULL)
				cell(y, x)->setDirty();
		}
	}

	//�ػ�
	viewport()->update();
}

void chanSpreadsheetWidget::setAutoRecalculate(bool recalc){

	//�����Զ�����
	m_autoRecalc = recalc;

	if (m_autoRecalc) recalculate();
}

//����޸�ʱ�� 2015/1/18 9��03
void chanSpreadsheetWidget::sort(const chanSpreadsheetCompare& predicate){

	//���ܻ᷵��null cell
	QList<QTableWidgetItem*> items = selectedItems();

	//���ѡ������Ľ��
	std::list<QStringList> list;

	//���ÿһ�е��ı�
	QStringList rowText;

	//���ѡ��ķ�Χ �Դ�֪��ѡ��Ŀ�
	QTableWidgetSelectionRange range = selectedRange();

	//���ѡ��Χ�Ŀ�
	size_t width = range.rightColumn() - range.leftColumn() + 1;

	//���ﲻȷ�� items �е�˳������Ĭ�ϵ��� ������ ���ϵ���
	//��ȡÿ��
	std::for_each(items.begin(), items.end(), [&](QTableWidgetItem* item){

		//�����ݷŽ�row text��
		rowText.push_back(formula(item->row(), item->column()));

		//�����Ҫ���� ������ҪƵ���Ĳ���rowtext �Ĵ�С�����stl���list�Ͳ��ٺ��ʣ�������ʹ�õ���qt�Դ���
		if (!(rowText.size() % width)){
			list.push_front(std::move(rowText));
			rowText.clear();
		}
			
	});

	//�����ݽ�������
	list.sort(predicate);

	//�����������ݷŻص�ԭ��������
	QList<QTableWidgetItem*>::iterator it = items.begin();

	std::for_each(list.begin(), list.end(), [&](QStringList& rowText){
		
		//����ÿһ�е��ı� �����ǰ�ı����ǿյ� ��ô�Ͱ��������ѡ���������
		std::for_each(rowText.begin(), rowText.end(), [&](QString& item){
			setFormula((*it)->row(), (*it)->column(), std::move(item));
			++it;
		});
	});

	//���ѡ��
	clearSelection();

	//�������޸ĵ��ź�
	somethingChanged();
}


