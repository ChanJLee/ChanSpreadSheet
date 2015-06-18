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
	const static size_t BUTTON_BLANK				= 0x00000005u;//�Ŵ���С��ť֮��Ŀհ�
	const static size_t MIN_WIDTH_HEIGHT			= 0x00000004u;//��Ƥ����С�ķ�Χ ��ֹ�û�����ʹ����Ƥ���
	const static size_t MOUSE_STEP					= 0x0000000Fu;//�����������Ĳ���
	const static size_t MOUSE_MAGNIFICATION			= 0x00000008u;//�����ֵĽǶȷŴ���
	const static size_t SHORT_LENGTH				= 0x00000005u;//x y ����С���ߵĳ���
	const static size_t X_LABEL_WIDTH				= 0x00000064u;//x ���ϱ�ǩ�Ŀ�
	const static size_t X_LABEL_HEIGHT				= 0x00000014u;//x ���ϱ�ǩ�ĸ�
	const static size_t Y_LABEL_WIDTH				= MARGIN - 0x00000005u;
	const static size_t Y_LABEL_HEIGHT				= X_LABEL_HEIGHT;
	const static size_t COLOR_FOR_IDS_SIZE			= 0X00000006u;//������ɫ������
	const static QColor s_colorForIds[COLOR_FOR_IDS_SIZE];//������н�Ҫ��ʾ�����ߵ���ɫ
	const static size_t Y_CHART_TITLE				= 0x0000000Fu;//�������y����
	const static size_t X_Y_TITLE					= 0x00000006u;//Y������x����
	const static size_t Y_Y_TITLE					= 0x0000002Bu;//y����
	const static size_t X_FIXED_X_TITLE				= 0x0000002Fu;//X������Xƫ������
	const static size_t Y_FIXED_X_TITLE				= 0x00000010u;//yƫ������

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

	//��� x y  chart �ı���
	const QString& xTitle()const { return m_xTitle; }
	const QString& yTitle()const { return m_yTitle; }
	const QString& chartTitle()const { return m_chartTitle; }

	//���� x y chart���ı���
	void setXTitle(const QString& xTit) { m_xTitle = xTit; }
	void setYTitle(const QString& yTit) { m_yTitle = yTit; }
	void setChartTitle(const QString& chartTit) { m_chartTitle = chartTit; }

	//������� ��һ���ǹ��ڱ����������⡡���ڶ����Ǵ����������ݡ��������ú����ݽ��л��Ʊ��
	void drawChart(const chartSettings&,const QStringListVec&);

public slots:
	void zoomIn();//�Ŵ�
	void zoomOut();//��С

protected:
	void paintEvent(QPaintEvent*);
	void resizeEvent(QResizeEvent*);
	void mousePressEvent(QMouseEvent*);
	void mouseMoveEvent(QMouseEvent*);
	void mouseReleaseEvent(QMouseEvent*);
	void keyPressEvent(QKeyEvent*);
	void wheelEvent(QWheelEvent*);

private:
	void updateRubberBandRegion();//������Ƥ��ѡ���
	void refreshPixmap();//ˢ������ӳ��
	void drawGrid(QPainter*);
	void drawCurves(QPainter*);

private:
	int				 m_curZoom;//��ǰ����
	bool			 m_rubberBandIsShown;
	QRect			 m_rubberBandRect;
	QPixmap			 m_pixmap;
	QPointFVecMap	 m_curvesMap;
	QToolButton*	 m_zoomInButton;
	QToolButton*	 m_zoomOutButton;
	PlotSettiongsVec m_zoomStack;//���Ŷ�ջ
	QString			 m_xTitle;//x��ı���
	QString			 m_yTitle;//y��ı���
	QString          m_chartTitle;//ͼ��ı���
};

#endif // PLOTTER_H
