#include "chartSettings.h"

chartSettings::chartSettings(const QChar x,const QChar y,
	const QString& xTitle,const QString& yTitle,
	const QString& chartTitle):
m_settings(std::make_tuple(x,y,xTitle,yTitle,chartTitle))
{
}

