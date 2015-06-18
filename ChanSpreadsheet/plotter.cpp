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

//��ɫ��ǳ����
const QColor plotter::s_colorForIds[COLOR_FOR_IDS_SIZE] = {
	Qt::blue,Qt::green,Qt::cyan,Qt::yellow,Qt::magenta,Qt::red
};

plotter::plotter(QWidget *parent)
	: QWidget(parent){

	//���ߵ�ɫ���ð�������Ϊ�ػ洰�ڲ����Ľ�ɫ
	setBackgroundRole(QPalette::Dark);

	//�Ӵ��ڲ����Ӹ����ڼ̳���Ӧ�ı���ɫ
	setAutoFillBackground(true);

	//��С�Ĳ���
	setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);

	//ͨ����������tab���뽹��
	setFocusPolicy(Qt::StrongFocus);

	//������Ƥ��ڲ��ɼ�
	m_rubberBandIsShown = false;

	//�Ŵ�ť
	m_zoomInButton = new QToolButton(this);
	m_zoomInButton->setIcon(QIcon("src/in.png"));
	m_zoomInButton->adjustSize();
	connect(m_zoomInButton, SIGNAL(clicked()), this, SLOT(zoomIn()));

	//��С��ť
	m_zoomOutButton = new QToolButton(this);
	m_zoomOutButton->setIcon(QIcon("src/out.png"));
	m_zoomOutButton->adjustSize();
	connect(m_zoomOutButton, SIGNAL(clicked()), this, SLOT(zoomOut()));

	setplotSettings(plotSettings());//Ĭ������
}

void plotter::setplotSettings(const plotSettings& settings){
	
	//ʹ�ö�ջֻ���һ��
	m_zoomStack.clear();
	m_zoomStack.push_back(settings);

	//��ǰ��plotsetting 
	m_curZoom = 0u;
	
	//���ð�ť����
	m_zoomInButton->hide();
	m_zoomOutButton->hide();

	//ˢ��ӳ��
	refreshPixmap();
}


void plotter::zoomOut(){

	//��ͷ��
	if (m_curZoom <= 0) return;

	//��С�۵�����
	--m_curZoom;
	m_zoomOutButton->setEnabled(m_curZoom > 0);
	m_zoomInButton->setEnabled(true);
	m_zoomInButton->show();

	//ˢ��ӳ��
	refreshPixmap();
}

void plotter::zoomIn(){

	//�����ĩ�˾Ͳ�����
	if (m_curZoom >= static_cast<int>(m_zoomStack.size()) - 1) return;
	
	//�Ŵ�۵�����
	++m_curZoom;
	m_zoomInButton->setEnabled(m_curZoom < static_cast<int>(m_zoomStack.size()) - 1);
	m_zoomOutButton->setEnabled(true);
	m_zoomOutButton->show();

	//ˢ��ӳ��
	refreshPixmap();
}

void plotter::setCurveData(const size_t key, const QPointFVec& data){

	//��ӻ��滻�µ�����
	m_curvesMap[key] = data;

	refreshPixmap();
}

void plotter::clearCurve(const size_t key){

	//ɾ������
	QPointFVecMap::iterator it = m_curvesMap.find(key);
	
	//���û���ҵ�
	if (it == m_curvesMap.end()) return;
	
	m_curvesMap.erase(it);

	refreshPixmap();
}

void plotter::paintEvent(QPaintEvent* /** event */){
	//���� 
	QStylePainter painter(this);

	//����pixmap
	painter.drawPixmap(0, 0, m_pixmap);

	if (m_rubberBandIsShown){

		//��û�������ɫ�����γɷ���
		painter.setPen(palette().dark().color());

		//��С��ȥһ ��������һ��һ���ص�����
		painter.drawRect(m_rubberBandRect.normalized().adjusted(0,0,-1,-1));
	}

	//�������˽���
	if (hasFocus()){
		//����ѡ���
		QStyleOptionFocusRect option;
		option.initFrom(this);

		//��������ɫ
		option.backgroundColor = palette().dark().color();

		//����ԭ����ͼ
		painter.drawPrimitive(QStyle::PE_FrameFocusRect, option);
	}
}

void plotter::resizeEvent(QResizeEvent* /* event*/){
	//����������ڴ��ڲ����ı��С �Լ�������ʱ�����
	int x = width() - (
		m_zoomInButton->width() + m_zoomOutButton->width() + BUTTON_BLANK * 2
		);

	m_zoomInButton->move(x, BUTTON_BLANK);
	m_zoomOutButton->move(x + BUTTON_BLANK + m_zoomInButton->width(), BUTTON_BLANK);

	refreshPixmap();
}

void plotter::mousePressEvent(QMouseEvent* event){
	if (event->button() != Qt::LeftButton) return;

	//������������
	//�����Ч����
	QRect rect(MARGIN, MARGIN, width() - 2 * MARGIN, height() - 2 * MARGIN);

	//���������Ч����
	if (rect.contains(event->pos())){
		//��Ƥ����������ʾ��
		m_rubberBandIsShown = true;

		//�������Ͻ�����
		m_rubberBandRect.setTopLeft(event->pos());
		//�������½�����
		m_rubberBandRect.setBottomRight(event->pos());

		//������Ƥ������
		updateRubberBandRegion();

		//���õ�ǰ�������״
		setCursor(Qt::CrossCursor);
	}
}

void plotter::mouseMoveEvent(QMouseEvent* event){

	//�����û��ʹ����Ƥ���ֱ�ӷ���
	if (!m_rubberBandIsShown) return;

	//������Ƥ��
	updateRubberBandRegion();

	//�������½ǵ�����
	m_rubberBandRect.setBottomRight(event->pos());

	//������Ƥ��
	updateRubberBandRegion();
}

void plotter::mouseReleaseEvent(QMouseEvent* event){

	//������µ������ ����ʹ������Ƥ���
	if ((event->button() == Qt::LeftButton) &&
		m_rubberBandIsShown){

		//���ڿ���ȡ����
		m_rubberBandIsShown = false;

		//����
		updateRubberBandRegion();

		//�ָ����
		unsetCursor();

		//���һ�㻯�ľ���
		QRect rect = m_rubberBandRect.normalized();

		//�������û�����ˣ�����ֻ��Ϊ���ô��ھ۽�
		if ((rect.width() < MIN_WIDTH_HEIGHT) || (rect.height() < MIN_WIDTH_HEIGHT))
			return;

		//��Ϊ���������������������ģ����Ҫ��ȥ
		rect.translate(-MARGIN, -MARGIN);

		//֮ǰ����������
		plotSettings prevSetting = m_zoomStack[m_curZoom];

		//���µ���������
		plotSettings setting;

		//��������
		double x = prevSetting.spanX() / (width() - 2 * MARGIN);
		double y = prevSetting.spanY() / (height() - 2 * MARGIN);

		setting.setMinX(prevSetting.minX() + x * rect.left());
		setting.setMaxX(prevSetting.minX() + x * rect.right());

		setting.setMinY(prevSetting.maxY() - y * rect.bottom());
		setting.setMaxY(prevSetting.maxY() - y * rect.top());

		//����
		setting.adjust();

		//ѹ��ջ
		m_zoomStack.push_back(setting);

		//�Ŵ�
		zoomIn();
	}
}

void plotter::keyPressEvent(QKeyEvent* event){

	//�����¼�
	switch (event->key()){
	case Qt::Key_Plus: // + Ϊ�Ŵ�
		zoomIn();
		break;
	case Qt::Key_Minus: //- Ϊ��С
		zoomOut();
		break;
	case Qt::Key_Left: // ��������Ϊ��ת
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
	default: // ����ʱ����Ȼ��ԭ���Ľ��д���
		QWidget::keyPressEvent(event);
		break;
	}
}


void plotter::wheelEvent(QWheelEvent* event){

	//qt �ԽǶȵİ˱�
	int degrees = event->delta() / MOUSE_MAGNIFICATION;
	//15��Ϊһ������
	int ticks = degrees / MOUSE_STEP;

	//����Ǵ�ֱ����
	if (event->orientation() == Qt::Horizontal)
		m_zoomStack[m_curZoom].scroll(ticks, 0);
	else m_zoomStack[m_curZoom].scroll(0, ticks);

	//ˢ��
	refreshPixmap();
}

void plotter::updateRubberBandRegion(){
	//�����Ƥ������
	QRect rect	  = m_rubberBandRect.normalized();

	//�õ���Ƥ��Ŀ��
	int width	  = rect.width();
	int heigth	  = rect.height();

	//�����Ƥ����������
	int leftTopX  = rect.left();
	int rightTopX = rect.right();

	int topY	  = rect.top();
	int bottomY   = rect.bottom();

	//������Ƥ��߿�
	update(leftTopX, topY, width, 1);
	update(leftTopX, topY, 1, heigth);
	update(leftTopX, bottomY, width, 1);
	update(rightTopX, topY, 1, heigth);
}

void plotter::refreshPixmap(){
	//������С
	m_pixmap = QPixmap(size());

	//��������Ƿ�ʵ�ĵģ���Ҫ����ƫ����
	m_pixmap.fill(this, 0, 0);

	//����
	QPainter painter(&m_pixmap);

	//���û���ʹ�õĻ��ʱ���ɫ������
	painter.initFrom(this);

	//��ʼ����
	drawGrid(&painter);
	drawCurves(&painter);

	//ԤԼһ�������¼�
	update();
}

void plotter::drawGrid(QPainter* painter){
	
	//��û�ͼ��
	QRect rect(MARGIN, MARGIN, width() - 2 * MARGIN, height() - 2 * MARGIN);

	//������ڲ����� ��������ͼ��
	if (!rect.isValid()) return;

	//��õ�ǰ�����Ŵ�С
	plotSettings settings = m_zoomStack[m_curZoom];

	//��ñ�
	QPen quiteDarkPen	  = palette().dark().color().light();
	QPen lightPen		  = palette().light().color();

	//���x y ��̶�
	double label		  = 0;
	int x				  = 0;
	int y				  = 0;
	
	for (int i = 0; i <= settings.numXTicks(); ++i){

		//��� x ����
		x = rect.left() + (i * (rect.width() - 1) / settings.numXTicks());

		//����x���ϵı�ǩ
		label = settings.minX() + (i * settings.spanX() / settings.numXTicks());

		//���û����ߵı�
		painter->setPen(quiteDarkPen);

		//����
		painter->drawLine(x, rect.top(), x, rect.bottom());

		//���û�x�������С���ߵı�
		painter->setPen(lightPen);

		//��С����
		painter->drawLine(x, rect.bottom(), x, rect.bottom() + SHORT_LENGTH);

		//�������
		painter->drawText(x - MARGIN, rect.bottom() + SHORT_LENGTH, X_LABEL_WIDTH, X_LABEL_HEIGHT,
			Qt::AlignHCenter | Qt::AlignTop, QString::number(label));
	}

	for (int i = 0; i <= settings.numYTicks(); ++i){

		//���Y����
		y = rect.bottom() - (i * (rect.height() - 1) / settings.numYTicks());

		//����̶�
		label = settings.minY() + (i * settings.spanY() / settings.numYTicks());

		//���û���
		painter->setPen(quiteDarkPen);

		//��������
		painter->drawLine(rect.left(), y, rect.right(), y);

		//���û��� ��С����
		painter->setPen(lightPen);

		//����Ϊ5��С����
		painter->drawLine(rect.left() - SHORT_LENGTH, y, rect.left(), y);

		//���Ͽ̶�
		painter->drawText(rect.left() - MARGIN, y - 2 * SHORT_LENGTH, Y_LABEL_WIDTH, Y_LABEL_HEIGHT,
			Qt::AlignRight | Qt::AlignVCenter, QString::number(label));
	}

	//��ӱ���
	painter->drawText(width() / 2, Y_CHART_TITLE, m_chartTitle);
	painter->drawText(X_Y_TITLE, Y_Y_TITLE, m_yTitle);
	painter->drawText(width() - X_FIXED_X_TITLE, height() - Y_FIXED_X_TITLE, m_xTitle);

	//���Ͼ���
	painter->drawRect(rect.adjusted(0, 0, -1, -1));
}

void plotter::drawCurves(QPainter* painter){

	QRect rect(MARGIN, MARGIN, width() - 2 * MARGIN, height() - 2 * MARGIN);
	if (!rect.isValid()) return;

	//֮ǰ������
	plotSettings settings = m_zoomStack[m_curZoom];

	//����м�Ļ�ͼ��
	painter->setClipRect(rect.adjusted(+1, +1, -1, -1));

	//����ӳ���е�ÿ��ͼ
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

		//�������С����һ����ɫ
		painter->setPen(s_colorForIds[vec.size() % COLOR_FOR_IDS_SIZE]);

		//����ͼ��
		painter->drawPolyline(polyline);
	});
}

void plotter::drawChart(const chartSettings& settings,const QStringListVec& itemsVec){

	//���x y ������Դ��λ��
	int x						= settings.getX().unicode() - 'A';
	int y						= settings.getY().unicode() - 'A';

	//��ñ���
	m_xTitle					= settings.getXTitle();
	m_yTitle					= settings.getYTitle();
	m_chartTitle				= settings.getChartTitle();

	//��ŵ������
	QPointFVec pointVec;

	//x y ����
	const QStringList& xRows			= itemsVec[x];
	const QStringList& yRows			= itemsVec[y];

	QStringList::const_iterator xIt	= xRows.cbegin();

	//�������е�ÿ���㶼װ��������
	std::for_each(yRows.cbegin(), yRows.cend(), [&](const QString& item){

		//������ݵ� ������ڴ��������qt���� ����ĸ�ʽ�ܱȴ�������ݺ�
		pointVec.emplace_back(xIt->toDouble(), item.toDouble());

		//ͬ��x������
		++xIt;
	});

	//�����������

	const size_t slot = std::hash<std::string>()(m_chartTitle.toStdString());

	//�鿴�Ƿ��Ѿ�����
	QPointFVecMap::iterator it = m_curvesMap.find(slot);

	//����Ѿ�����
	if (it != m_curvesMap.end()){

		//�������󴰿�
		QMessageBox::warning(this, tr("Chan Spreadsheet"), 
			tr("the name %1 has been already existed").arg(m_chartTitle));
		return;
	}

	//��ŵ�map
	setCurveData(slot, pointVec);
}

void plotter::clearAllCurve(){

	//������еļ�¼
	m_curvesMap.clear();

	//��ձ���
	m_xTitle.clear();
	m_yTitle.clear();
	m_chartTitle.clear();
}