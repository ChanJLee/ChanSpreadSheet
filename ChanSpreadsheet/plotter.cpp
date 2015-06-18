#include "plotter.h"
#include <qtoolbutton.h>
#include <QIcon>
#include <qstylepainter.h>
#include <qstyleoption.h>
#include <qstyle.h>
#include <qevent.h>
#include <algorithm>
#include <qpolygon.h>
#include <chartSettings.h>
#include <functional>
#include <qmessagebox.h>
#include <string>

//颜色由浅到深
const QColor plotter::s_colorForIds[COLOR_FOR_IDS_SIZE] = {
	Qt::blue,Qt::green,Qt::cyan,Qt::yellow,Qt::magenta,Qt::red
};

plotter::plotter(QWidget *parent)
	: QWidget(parent){

	//告诉调色板用暗分量作为重绘窗口部件的角色
	setBackgroundRole(QPalette::Dark);

	//子窗口部件从父窗口继承相应的背景色
	setAutoFillBackground(true);

	//大小的策略
	setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);

	//通过单击或者tab输入焦点
	setFocusPolicy(Qt::StrongFocus);

	//设置橡皮筋窗口不可见
	m_rubberBandIsShown = false;

	//放大按钮
	m_zoomInButton = new QToolButton(this);
	m_zoomInButton->setIcon(QIcon("src/in.png"));
	m_zoomInButton->adjustSize();
	connect(m_zoomInButton, SIGNAL(clicked()), this, SLOT(zoomIn()));

	//缩小按钮
	m_zoomOutButton = new QToolButton(this);
	m_zoomOutButton->setIcon(QIcon("src/out.png"));
	m_zoomOutButton->adjustSize();
	connect(m_zoomOutButton, SIGNAL(clicked()), this, SLOT(zoomOut()));

	setplotSettings(plotSettings());//默认设置
}

void plotter::setplotSettings(const plotSettings& settings){
	
	//使得堆栈只存放一项
	m_zoomStack.clear();
	m_zoomStack.push_back(settings);

	//当前的plotsetting 
	m_curZoom = 0u;
	
	//设置按钮隐藏
	m_zoomInButton->hide();
	m_zoomOutButton->hide();

	//刷新映射
	refreshPixmap();
}


void plotter::zoomOut(){

	//在头部
	if (m_curZoom <= 0) return;

	//缩小槽的设置
	--m_curZoom;
	m_zoomOutButton->setEnabled(m_curZoom > 0);
	m_zoomInButton->setEnabled(true);
	m_zoomInButton->show();

	//刷新映射
	refreshPixmap();
}

void plotter::zoomIn(){

	//如果在末端就不继续
	if (m_curZoom >= static_cast<int>(m_zoomStack.size()) - 1) return;
	
	//放大槽的设置
	++m_curZoom;
	m_zoomInButton->setEnabled(m_curZoom < static_cast<int>(m_zoomStack.size()) - 1);
	m_zoomOutButton->setEnabled(true);
	m_zoomOutButton->show();

	//刷新映射
	refreshPixmap();
}

void plotter::setCurveData(const size_t key, const QPointFVec& data){

	//添加或替换新的曲线
	m_curvesMap[key] = data;

	refreshPixmap();
}

void plotter::clearCurve(const size_t key){

	//删除曲线
	QPointFVecMap::iterator it = m_curvesMap.find(key);
	
	//如果没有找到
	if (it == m_curvesMap.end()) return;
	
	m_curvesMap.erase(it);

	refreshPixmap();
}

void plotter::paintEvent(QPaintEvent* /** event */){
	//画笔 
	QStylePainter painter(this);

	//绘制pixmap
	painter.drawPixmap(0, 0, m_pixmap);

	if (m_rubberBandIsShown){

		//获得画板中颜色，以形成反差
		painter.setPen(palette().dark().color());

		//大小减去一 以允许有一个一像素的轮廓
		painter.drawRect(m_rubberBandRect.normalized().adjusted(0,0,-1,-1));
	}

	//如果获得了焦点
	if (hasFocus()){
		//焦点选择框
		QStyleOptionFocusRect option;
		option.initFrom(this);

		//背景的颜色
		option.backgroundColor = palette().dark().color();

		//绘制原来的图
		painter.drawPrimitive(QStyle::PE_FrameFocusRect, option);
	}
}

void plotter::resizeEvent(QResizeEvent* /* event*/){
	//这个函数会在窗口部件改变大小 以及创建的时候调用
	int x = width() - (
		m_zoomInButton->width() + m_zoomOutButton->width() + BUTTON_BLANK * 2
		);

	m_zoomInButton->move(x, BUTTON_BLANK);
	m_zoomOutButton->move(x + BUTTON_BLANK + m_zoomInButton->width(), BUTTON_BLANK);

	refreshPixmap();
}

void plotter::mousePressEvent(QMouseEvent* event){
	if (event->button() != Qt::LeftButton) return;

	//如果按下了左键
	//获得有效区域
	QRect rect(MARGIN, MARGIN, width() - 2 * MARGIN, height() - 2 * MARGIN);

	//如果落在有效区域
	if (rect.contains(event->pos())){
		//橡皮筋区可以显示了
		m_rubberBandIsShown = true;

		//设置左上角坐标
		m_rubberBandRect.setTopLeft(event->pos());
		//设置右下角坐标
		m_rubberBandRect.setBottomRight(event->pos());

		//更新橡皮筋区域
		updateRubberBandRegion();

		//设置当前的鼠标形状
		setCursor(Qt::CrossCursor);
	}
}

void plotter::mouseMoveEvent(QMouseEvent* event){

	//如果并没有使用橡皮筋就直接返回
	if (!m_rubberBandIsShown) return;

	//更新橡皮筋
	updateRubberBandRegion();

	//设置右下角的坐标
	m_rubberBandRect.setBottomRight(event->pos());

	//更新橡皮筋
	updateRubberBandRegion();
}

void plotter::mouseReleaseEvent(QMouseEvent* event){

	//如果按下的是左键 并且使用了橡皮筋功能
	if ((event->button() == Qt::LeftButton) &&
		m_rubberBandIsShown){

		//现在可以取消了
		m_rubberBandIsShown = false;

		//更新
		updateRubberBandRegion();

		//恢复光标
		unsetCursor();

		//获得一般化的矩形
		QRect rect = m_rubberBandRect.normalized();

		//可能是用户误点了，或者只是为了让窗口聚焦
		if ((rect.width() < MIN_WIDTH_HEIGHT) || (rect.height() < MIN_WIDTH_HEIGHT))
			return;

		//因为其坐标是相对于整个坐标的，因此要减去
		rect.translate(-MARGIN, -MARGIN);

		//之前的坐标设置
		plotSettings prevSetting = m_zoomStack[m_curZoom];

		//最新的坐标设置
		plotSettings setting;

		//重置坐标
		double x = prevSetting.spanX() / (width() - 2 * MARGIN);
		double y = prevSetting.spanY() / (height() - 2 * MARGIN);

		setting.setMinX(prevSetting.minX() + x * rect.left());
		setting.setMaxX(prevSetting.minX() + x * rect.right());

		setting.setMinY(prevSetting.maxY() - y * rect.bottom());
		setting.setMaxY(prevSetting.maxY() - y * rect.top());

		//调整
		setting.adjust();

		//压入栈
		m_zoomStack.push_back(setting);

		//放大
		zoomIn();
	}
}

void plotter::keyPressEvent(QKeyEvent* event){

	//键盘事件
	switch (event->key()){
	case Qt::Key_Plus: // + 为放大
		zoomIn();
		break;
	case Qt::Key_Minus: //- 为缩小
		zoomOut();
		break;
	case Qt::Key_Left: // 上下左右为旋转
		m_zoomStack[m_curZoom].scroll(-1, 0);
		refreshPixmap();
		break;
	case Qt::Key_Right:
		m_zoomStack[m_curZoom].scroll(1, 0);
		refreshPixmap();
		break;
	case Qt::Key_Down:
		m_zoomStack[m_curZoom].scroll(0, -1);
		refreshPixmap();
		break;
	case Qt::Key_Up:
		m_zoomStack[m_curZoom].scroll(0, 1);
		refreshPixmap();
		break;
	default: // 其他时间仍然按原来的进行处理
		QWidget::keyPressEvent(event);
		break;
	}
}


void plotter::wheelEvent(QWheelEvent* event){

	//qt 以角度的八倍
	int degrees = event->delta() / MOUSE_MAGNIFICATION;
	//15度为一个步长
	int ticks = degrees / MOUSE_STEP;

	//如果是垂直滚轮
	if (event->orientation() == Qt::Horizontal)
		m_zoomStack[m_curZoom].scroll(ticks, 0);
	else m_zoomStack[m_curZoom].scroll(0, ticks);

	//刷新
	refreshPixmap();
}

void plotter::updateRubberBandRegion(){
	//获得橡皮筋区域
	QRect rect	  = m_rubberBandRect.normalized();

	//得到橡皮筋的宽高
	int width	  = rect.width();
	int heigth	  = rect.height();

	//获得橡皮筋的相关坐标
	int leftTopX  = rect.left();
	int rightTopX = rect.right();

	int topY	  = rect.top();
	int bottomY   = rect.bottom();

	//更新橡皮筋边框
	update(leftTopX, topY, width, 1);
	update(leftTopX, topY, 1, heigth);
	update(leftTopX, bottomY, width, 1);
	update(rightTopX, topY, 1, heigth);
}

void plotter::refreshPixmap(){
	//调整大小
	m_pixmap = QPixmap(size());

	//如果画笔是非实心的，就要调整偏移量
	m_pixmap.fill(this, 0, 0);

	//画笔
	QPainter painter(&m_pixmap);

	//设置画笔使用的画笔背景色和字体
	painter.initFrom(this);

	//开始绘制
	drawGrid(&painter);
	drawCurves(&painter);

	//预约一个绘制事件
	update();
}

void plotter::drawGrid(QPainter* painter){
	
	//获得绘图区
	QRect rect(MARGIN, MARGIN, width() - 2 * MARGIN, height() - 2 * MARGIN);

	//如果窗口不够大 不能容下图形
	if (!rect.isValid()) return;

	//获得当前的缩放大小
	plotSettings settings = m_zoomStack[m_curZoom];

	//获得笔
	QPen quiteDarkPen	  = palette().dark().color().light();
	QPen lightPen		  = palette().light().color();

	//标记x y 轴刻度
	double label		  = 0;
	int x				  = 0;
	int y				  = 0;
	
	for (int i = 0; i <= settings.numXTicks(); ++i){

		//获得 x 坐标
		x = rect.left() + (i * (rect.width() - 1) / settings.numXTicks());

		//设置x轴上的标签
		label = settings.minX() + (i * settings.spanX() / settings.numXTicks());

		//设置画竖线的笔
		painter->setPen(quiteDarkPen);

		//竖线
		painter->drawLine(x, rect.top(), x, rect.bottom());

		//设置画x轴上面的小短线的笔
		painter->setPen(lightPen);

		//画小短线
		painter->drawLine(x, rect.bottom(), x, rect.bottom() + SHORT_LENGTH);

		//画出标记
		painter->drawText(x - MARGIN, rect.bottom() + SHORT_LENGTH, X_LABEL_WIDTH, X_LABEL_HEIGHT,
			Qt::AlignHCenter | Qt::AlignTop, QString::number(label));
	}

	for (int i = 0; i <= settings.numYTicks(); ++i){

		//获得Y坐标
		y = rect.bottom() - (i * (rect.height() - 1) / settings.numYTicks());

		//计算刻度
		label = settings.minY() + (i * settings.spanY() / settings.numYTicks());

		//设置画笔
		painter->setPen(quiteDarkPen);

		//画出横线
		painter->drawLine(rect.left(), y, rect.right(), y);

		//设置画笔 画小短线
		painter->setPen(lightPen);

		//长度为5的小短线
		painter->drawLine(rect.left() - SHORT_LENGTH, y, rect.left(), y);

		//画上刻度
		painter->drawText(rect.left() - MARGIN, y - 2 * SHORT_LENGTH, Y_LABEL_WIDTH, Y_LABEL_HEIGHT,
			Qt::AlignRight | Qt::AlignVCenter, QString::number(label));
	}

	//添加标题
	painter->drawText(width() / 2, Y_CHART_TITLE, m_chartTitle);
	painter->drawText(X_Y_TITLE, Y_Y_TITLE, m_yTitle);
	painter->drawText(width() - X_FIXED_X_TITLE, height() - Y_FIXED_X_TITLE, m_xTitle);

	//画上矩形
	painter->drawRect(rect.adjusted(0, 0, -1, -1));
}

void plotter::drawCurves(QPainter* painter){

	QRect rect(MARGIN, MARGIN, width() - 2 * MARGIN, height() - 2 * MARGIN);
	if (!rect.isValid()) return;

	//之前的设置
	plotSettings settings = m_zoomStack[m_curZoom];

	//获得中间的绘图区
	painter->setClipRect(rect.adjusted(+1, +1, -1, -1));

	//遍历映射中的每个图
	std::for_each(m_curvesMap.begin(), m_curvesMap.end(), [&](QPointFVecMap::value_type& value) {
		
		const QPointFVec& vec = value.second;

		QPolygonF polyline;
		
		std::for_each(vec.cbegin(), vec.cend(), [&](const QPointF& point){
			double dx = point.x() - settings.minX();
			double dy = point.y() - settings.minY();

			double x = rect.left() + (dx * (rect.width() - 1) / settings.spanX());
			double y = rect.bottom() - (dy * (rect.height() - 1) / settings.spanY());

			polyline.push_back(QPointF(x, y));
		});

		//按照其大小给定一个颜色
		painter->setPen(s_colorForIds[vec.size() % COLOR_FOR_IDS_SIZE]);

		//画出图形
		painter->drawPolyline(polyline);
	});
}

void plotter::drawChart(const chartSettings& settings,const QStringListVec& itemsVec){

	//获得x y 数据来源的位置
	int x						= settings.getX().unicode() - 'A';
	int y						= settings.getY().unicode() - 'A';

	//获得标题
	m_xTitle					= settings.getXTitle();
	m_yTitle					= settings.getYTitle();
	m_chartTitle				= settings.getChartTitle();

	//存放点的容器
	QPointFVec pointVec;

	//x y 内容
	const QStringList& xRows			= itemsVec[x];
	const QStringList& yRows			= itemsVec[y];

	QStringList::const_iterator xIt	= xRows.cbegin();

	//把数据中的每个点都装进容器中
	std::for_each(yRows.cbegin(), yRows.cend(), [&](const QString& item){

		//存放数据点 如果存在错误的数据qt会解决 错误的格式总比错误的数据好
		pointVec.emplace_back(xIt->toDouble(), item.toDouble());

		//同步x的内容
		++xIt;
	});

	//计算出槽类型

	const size_t slot = std::hash<std::string>()(m_chartTitle.toStdString());

	//查看是否已经有了
	QPointFVecMap::iterator it = m_curvesMap.find(slot);

	//如果已经有了
	if (it != m_curvesMap.end()){

		//弹出错误窗口
		QMessageBox::warning(this, tr("Chan Spreadsheet"), 
			tr("the name %1 has been already existed").arg(m_chartTitle));
		return;
	}

	//存放到map
	setCurveData(slot, pointVec);
}

void plotter::clearAllCurve(){

	//清空所有的记录
	m_curvesMap.clear();

	//清空标题
	m_xTitle.clear();
	m_yTitle.clear();
	m_chartTitle.clear();
}