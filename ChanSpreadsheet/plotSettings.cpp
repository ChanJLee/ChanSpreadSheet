#include "PlotSettings.h"
#include <cmath>

plotSettings::plotSettings():
m_minX(DEFAULT_MIN_X),
m_minY(DEFAULT_MIN_Y),
m_maxX(DEFAULT_MAX_X),
m_maxY(DEFAULT_MAX_Y),
m_numXTicks(DEFAULT_TRICK),
m_numYTicks(DEFAULT_TRICK){
}

void plotSettings::scroll(int x, int y){

	double stepX = spanX() / numXTicks();
	m_minX += x * stepX;
	m_maxX += x * stepX;

	double stepY = spanY() / numYTicks();
	m_minY += y * stepY;
	m_maxY += y * stepY;
}

//绘图做调整
void plotSettings::adjust(){
	adjustAxis(m_minX, m_maxX, m_numXTicks);
	adjustAxis(m_minY, m_maxY, m_numYTicks);
}

//最后修改时间 2015/1/13 15:08
void plotSettings::adjustAxis(double& min, double& max, int& numTicks){
	//调整中轴线

	//粗略的步数
	double grossStep = (max - min) / MIN_TRICK;

	//获得精确的步数
	double step = std::pow(10, std::floor(std::log10(grossStep)));

	//总是小于粗略的步数
	if (MAX_STEP_ZOOM * step < grossStep)
		step *= MAX_STEP_ZOOM;
	else if (MIN_STEP_ZOOM * step < grossStep)
		step *= MIN_STEP_ZOOM;

	//最小的取下限
	min = static_cast<int>(std::floor(min / step) * step);

	//最大的取上限
	max = static_cast<int>(std::ceil(max / step) * step);

	//获得最后的块的个数
	numTicks = static_cast<int>(max - min);

	//不能小于最小的块个数
	if (numTicks < MIN_TRICK) numTicks = MIN_TRICK;
}
