#ifndef __TABLE__CELL__H__
#define __TABLE__CELL__H__

#if defined _MSC_VER && _MSC_VER > 1000
	#pragma once
#endif

#include <qtablewidget.h>

class QVariant;

class tableCell :public QTableWidgetItem{

	typedef QString::iterator expressionIterator;
public:
	tableCell();
	~tableCell() = default;

	QTableWidgetItem* clone()const;

	void setData(int, const QVariant&);
	QVariant data(int)const;

	void setFormula(const QString&);
	QString formula()const;

	void setDirty();

private:

	QVariant& value()const;
	QVariant evalExpression(expressionIterator&,expressionIterator)const;
	QVariant evalTerm(expressionIterator&,expressionIterator)const;
	QVariant evalFactor(expressionIterator&,expressionIterator)const;

private:
	mutable QVariant	m_cacheValue;
	mutable bool		m_cacheIsDirty;
};

#endif