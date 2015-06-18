#ifndef __PLOT__SETTINGS__H__
#define __PLOT__SETTINGS__H__

#if defined _MSC_VER && _MSC_VER > 1000
	#pragma once
#endif


//最后修改时间 2015/1/13 15:08
class plotSettings{

	const static size_t DEFAULT_MIN_X = 0x00000000u;
	const static size_t DEFAULT_MIN_Y = 0x00000000u;
	const static size_t DEFAULT_MAX_Y = 0x0000000Au;
	const static size_t DEFAULT_MAX_X = 0x0000000Au;
	const static size_t DEFAULT_TRICK = 0x00000005u;
	const static size_t MIN_TRICK	  = 0x00000004u;
	const static size_t MAX_STEP_ZOOM = 0x00000005u;
	const static size_t MIN_STEP_ZOOM = 0x00000002u;
public:
	plotSettings();

	void scroll(int, int);
	void adjust();

	double spanX()const { return m_maxX - m_minX; }
	double spanY()const { return m_maxY - m_minY; }

	double minX()const { return m_minX; }
	double minY()const { return m_minY; }
	double maxX()const { return m_maxX; }
	double maxY()const	{ return m_maxY; }

	void setMinX(const int x) { m_minX = x; }
	void setMaxX(const int x) { m_maxX = x; }

	void setMinY(const int y) { m_minY = y; }
	void setMaxY(const int y) { m_maxY = y; }

	int numXTicks()const { return m_numXTicks; }
	int numYTicks()const { return m_numYTicks; }

private:
	double m_minX;
	double m_maxX;
	int	   m_numXTicks;

	double m_minY;
	double m_maxY;
	int	   m_numYTicks;
private:
	static void adjustAxis(double&, double&, int&);
};



#endif