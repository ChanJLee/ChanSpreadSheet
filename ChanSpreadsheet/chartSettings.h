#ifndef __TABLE__SETTINGS__H__
#define __TABLE__SETTINGS__H__


#if defined _MSC_VER && _MSC_VER > 1000
	#pragma once
#endif

#include <tuple>
#include <qstring.h>
#include <functional>

class chartSettings{
	typedef std::tuple<QChar, QChar, QString, QString, QString> tuple;

	enum { x, y, xTitle, yTitle, chartTitle };
public:
	chartSettings(const QChar, const QChar, const QString&, const QString&, const QString&);

	const QChar getX()const { return std::get<x>(m_settings); }
	const QChar getY()const { return std::get<y>(m_settings); }

	const QString& getXTitle()const { return std::get<xTitle>(m_settings); }
	const QString& getYTitle()const { return std::get<yTitle>(m_settings); }

	const QString& getChartTitle()const { return std::get<chartTitle>(m_settings); }

private:
	tuple m_settings;
};
#endif