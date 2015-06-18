#ifndef PLOTTER_H
#define PLOTTER_H

#include <QtWidgets/QWidget>
#include <unordered_map>
#include <vector>
#include <qpixmap.h>
#include "plotSettings.h"

class chartSettings;

class QToolButton;

class QStringList;

class plotter : public QWidget
{
	Q_OBJECT
		
private:
	typedef std::vector<QPointF>					QPointFVec;
	typedef std::vector<plotSettings>				PlotSettiongsVec;
	typedef std::unordered_map<size_t, QPointFVec>	QPointFVecMap;
	const static size_t MARGIN						= 0x00000032u;
	const static size_t MIN_WIDTH					= 0x00000006u * MARGIN;
	const static size_t MIN_HEIGHT					= 0x00000004u * MARGIN;
	const static size_t HINT_WIDTH					= 0x0000000Cu * MARGIN;
	const static size_t HINT_HEIGHT					= 0x00000008u * MARGIN;
	const static size_t BUTTON_BLANK				= 0x00000005u;//放大缩小按钮之间的空白
	const static size_t MIN_WIDTH_HEIGHT			= 0x00000004u;//橡皮筋最小的范围 防止用户无心使用橡皮筋功能
	const static size_t MOUSE_STEP					= 0x0000000Fu;//鼠标滚动度数的步长
	const static size_t MOUSE_MAGNIFICATION			= 0x00000008u;//鼠标滚轮的角度放大倍数
	const static size_t SHORT_LENGTH				= 0x00000005u;//x y 轴上小短线的长度
	const static size_t X_LABEL_WIDTH				= 0x00000064u;//x 轴上标签的宽
	const static size_t X_LABEL_HEIGHT				= 0x00000014u;//x 轴上标签的高
	const static size_t Y_LABEL_WIDTH				= MARGIN - 0x00000005u;
	const static size_t Y_LABEL_HEIGHT				= X_LABEL_HEIGHT;
	const static size_t COLOR_FOR_IDS_SIZE			= 0X00000006u;//折线颜色的种类
	const static QColor s_colorForIds[COLOR_FOR_IDS_SIZE];//存放所有将要显示的折线的颜色
	const static size_t Y_CHART_TITLE				= 0x0000000Fu;//表格标题的y坐标
	const static size_t X_Y_TITLE					= 0x00000006u;//Y轴标题的x坐标
	const static size_t Y_Y_TITLE					= 0x0000002Bu;//y坐标
	const static size_t X_FIXED_X_TITLE				= 0x0000002Fu;//X轴标题的X偏移坐标
	const static size_t Y_FIXED_X_TITLE				= 0x00000010u;//y偏移坐标

	typedef std::vector<QStringList> QStringListVec;
public:
	plotter(QWidget *parent = NULL);
	~plotter() = default;

public:
	void setplotSettings(const plotSettings&);
	void setCurveData(const size_t, const QPointFVec&);
	void clearCurve(const size_t);

	void clearAllCurve();

	QSize minimumSizeHint()const { return QSize(MIN_WIDTH, MIN_HEIGHT); }
	QSize sizeHint()const { return QSize(HINT_WIDTH, HINT_HEIGHT); }

	//获得 x y  chart 的标题
	const QString& xTitle()const { return m_xTitle; }
	const QString& yTitle()const { return m_yTitle; }
	const QString& chartTitle()const { return m_chartTitle; }

	//设置 x y chart　的标题
	void setXTitle(const QString& xTit) { m_xTitle = xTit; }
	void setYTitle(const QString& yTit) { m_yTitle = yTit; }
	void setChartTitle(const QString& chartTit) { m_chartTitle = chartTit; }

	//画出表格 第一个是关于表格的设置问题　　第二个是传过来的内容　根据设置和内容进行绘制表格
	void drawChart(const chartSettings&,const QStringListVec&);

public slots:
	void zoomIn();//放大
	void zoomOut();//缩小

protected:
	void paintEvent(QPaintEvent*);
	void resizeEvent(QResizeEvent*);
	void mousePressEvent(QMouseEvent*);
	void mouseMoveEvent(QMouseEvent*);
	void mouseReleaseEvent(QMouseEvent*);
	void keyPressEvent(QKeyEvent*);
	void wheelEvent(QWheelEvent*);

private:
	void updateRubberBandRegion();//更新橡皮筋选择框
	void refreshPixmap();//刷新像素映射
	void drawGrid(QPainter*);
	void drawCurves(QPainter*);

private:
	int				 m_curZoom;//当前缩放
	bool			 m_rubberBandIsShown;
	QRect			 m_rubberBandRect;
	QPixmap			 m_pixmap;
	QPointFVecMap	 m_curvesMap;
	QToolButton*	 m_zoomInButton;
	QToolButton*	 m_zoomOutButton;
	PlotSettiongsVec m_zoomStack;//缩放堆栈
	QString			 m_xTitle;//x轴的标题
	QString			 m_yTitle;//y轴的标题
	QString          m_chartTitle;//图标的标题
};

#endif // PLOTTER_H
