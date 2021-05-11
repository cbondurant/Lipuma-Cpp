#include "fractalLine.hpp"

#include <cmath>
#include <random>

#include <FastNoise/FastNoise.h>
#include <QColor>
#include <QGraphicsItem>
#include <QPainter>
#include <QRectF>
#include <QStyleOptionGraphicsItem>
#include <QWidget>

#include "drawable/editPoint.hpp"
#include "pointHelper.hpp"

namespace Lipuma {

	std::default_random_engine FractalLine::rand;

	void FractalLine::initalizeNoise(){
		noise = FastNoise::New<FastNoise::FractalFBm>();
		noise->SetSource(FastNoise::New<FastNoise::Simplex>());
		frequency = 0.02;
		noise->SetOctaveCount(5);
		noise->SetLacunarity(2.0f);
		noise->SetGain(.9);
	}

	void FractalLine::initalizeEditPoints(){
		startPt = new EditPoint();
		startPt->setParentItem(this);
		startPt->setVisible(false);
		connect(startPt, &EditPoint::pointMoved, this, &FractalLine::setStart);
		endPt = new EditPoint();
		endPt->setParentItem(this);
		endPt->setVisible(false);
		connect(endPt, &EditPoint::pointMoved, this, &FractalLine::setEnd);
	}

	FractalLine::FractalLine(QPointF s, QPointF e){
		seed = FractalLine::rand();
		setFlag(QGraphicsItem::ItemIsSelectable);
		initalizeEditPoints();
		initalizeNoise();
		setStart(s);
		setEnd(e);
	}

	FractalLine::FractalLine(QDataStream& stream){
		stream >> seed;
		setFlag(QGraphicsItem::ItemIsSelectable);
		initalizeNoise();
		initalizeEditPoints();
		QPointF pt;
		stream >> pt;
		setStart(pt);
		stream >> pt;
		setEnd(pt);
		stream >> frequency;
	}

	void FractalLine::write(QDataStream& stream){
		stream << DrawableType();
		stream << seed;
		stream << mapToScene(start);
		stream << mapToScene(end);
		stream << frequency;
	}

	qint8 FractalLine::DrawableType(){
		return DrawableSerializeTypes::SerializeFractalLine;
	}

	QRectF FractalLine::boundingRect() const {
		return QRectF(start.x()-5,-HEIGHT,end.x()+10,HEIGHT*2);
	}

	void FractalLine::setStart(QPointF s){
		// Store end location to keep end in place.
		QPointF gEnd = mapToScene(end);
		setPos(s);
		setEnd(gEnd);
	}

	void FractalLine::setEnd(QPointF e){
		QPointF delta = e - pos();
		qreal distance = Lipuma::distance(delta);
		qreal theta = atan2l(delta.y(), delta.x());
		// TODO: I do not know if M_PIl is a reliable constant, as it is compiler defined
		setRotation((theta/M_PIl)*180.0L);
		end = QPointF(distance,0);
		prepareGeometryChange();
		endPt->setPos(end);
	}

	float FractalLine::getFrequency(){
		return frequency;
	}

	QVariant FractalLine::itemChange(GraphicsItemChange change, const QVariant &val){
		QGraphicsItem::itemChange(change, val);
		if (change == ItemSelectedChange && scene()){
			startPt->setVisible(val.toBool());
			endPt->setVisible(val.toBool());
		}
		return val;
	}

	void FractalLine::setFrequency(float f){
		frequency = f;
		prepareGeometryChange();
		update();
	}

	void FractalLine::paint(QPainter *painter, const QStyleOptionGraphicsItem */* option */, QWidget */* widget */){
		painter->setRenderHint(QPainter::Antialiasing, true);
		// Set highlight color if selected
		if (isSelected()){
			painter->setPen(QColor(255,0,0));
		}

		// Dont draw really really short lines
		if (end.x() < 0.1) return;

		// Figure out the number of points to render the line with
		const int POINTS = end.x() / PERIOD;
		float curve[((POINTS+8)/8)*8] = {}; // Round to nearest multiple of 8, fastnoise runs better with it
		noise->GenUniformGrid2D(curve,0,0,((POINTS+8)/8)*8,1,frequency,seed);

		// Generate path
		QPainterPath path;
		// First and last point need to always be at zero, so skip the 0th element and the final element
		for (int i = 1; i < POINTS; i++){
			QPointF point = Lipuma::lerp(start, QPointF(POINTS*PERIOD,0), static_cast<float>(i)/static_cast<float>(POINTS));
			point += QPointF(0, curve[i-1]*HEIGHT);
			path.lineTo(point);
		}
		// Draw final point
		path.lineTo(end);
		painter->drawPath(path);
		//painter->drawPath(shape());
		//painter->drawRect(boundingRect());
	}
}
