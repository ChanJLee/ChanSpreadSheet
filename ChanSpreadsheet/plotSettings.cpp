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

//��ͼ������
void plotSettings::adjust(){
	adjustAxis(m_minX, m_maxX, m_numXTicks);
	adjustAxis(m_minY, m_maxY, m_numYTicks);
}

//����޸�ʱ�� 2015/1/13 15:08
void plotSettings::adjustAxis(double& min, double& max, int& numTicks){
	//����������

	//���ԵĲ���
	double grossStep = (max - min) / MIN_TRICK;

	//��þ�ȷ�Ĳ���
	double step = std::pow(10, std::floor(std::log10(grossStep)));

	//����С�ڴ��ԵĲ���
	if (MAX_STEP_ZOOM * step < grossStep)
		step *= MAX_STEP_ZOOM;
	else if (MIN_STEP_ZOOM * step < grossStep)
		step *= MIN_STEP_ZOOM;

	//��С��ȡ����
	min = static_cast<int>(std::floor(min / step) * step);

	//����ȡ����
	max = static_cast<int>(std::ceil(max / step) * step);

	//������Ŀ�ĸ���
	numTicks = static_cast<int>(max - min);

	//����С����С�Ŀ����
	if (numTicks < MIN_TRICK) numTicks = MIN_TRICK;
}
