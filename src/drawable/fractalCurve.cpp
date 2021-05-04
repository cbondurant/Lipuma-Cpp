#include "fractalCurve.hpp"

#include <cmath>
#include <random>
#include <iostream>

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

	inline QPointF computeBeizer(const QPointF a, const QPointF b, const QPointF c, const QPointF d, qreal x){
			const QPointF bc = Lipuma::lerp(b, c, x);
			const QPointF abbc = Lipuma::lerp(Lipuma::lerp(a, b, x),bc,x);
			const QPointF bccd = Lipuma::lerp(bc,Lipuma::lerp(c, d, x),x);
			return Lipuma::lerp(abbc, bccd, x);
	}

	std::default_random_engine FractalCurve::rand;

	void FractalCurve::initalizeNoise(){
		noise = FastNoise::New<FastNoise::FractalFBm>();
		noise->SetSource(FastNoise::New<FastNoise::Simplex>());
		frequency = 0.02;
		noise->SetOctaveCount(5);
		noise->SetLacunarity(2.0f);
		noise->SetGain(.9);
	}

	void FractalCurve::initalizeEditPoints(){
		startPt = new EditPoint();
		startPt->setParentItem(this);
		startPt->setVisible(false);
		connect(startPt, &EditPoint::pointMoved, this, &FractalCurve::setStart);

		innerStartPt = new EditPoint();
		innerStartPt->setParentItem(this);
		innerStartPt->setVisible(false);
		innerStartPt->setScale(0.9);
		connect(innerStartPt, &EditPoint::pointMoved, this, &FractalCurve::setInnerStart);

		innerEndPt = new EditPoint();
		innerEndPt->setParentItem(this);
		innerEndPt->setVisible(false);
		innerEndPt->setScale(0.9);
		connect(innerEndPt, &EditPoint::pointMoved, this, &FractalCurve::setInnerEnd);

		endPt = new EditPoint();
		endPt->setParentItem(this);
		endPt->setVisible(false);
		endPt->setZValue(-1);
		connect(endPt, &EditPoint::pointMoved, this, &FractalCurve::setEnd);
	}

	FractalCurve::FractalCurve(QPointF s, QPointF e){
		seed = FractalCurve::rand();
		setFlag(QGraphicsItem::ItemIsSelectable);
		initalizeEditPoints();
		initalizeNoise();
		setStart(s);
		setEnd(e);
	}

	FractalCurve::FractalCurve(QDataStream& is){
		setFlag(QGraphicsItem::ItemIsSelectable);
		initalizeEditPoints();
		initalizeNoise();
		is >> seed;
		QPointF pt;
		is >> pt;
		setStart(pt);
		is >> pt;
		setEnd(pt);
		is >> pt;
		setInnerStart(pt);
		is >> pt;
		setInnerEnd(pt);
	}

	qint8 FractalCurve::DrawableType(){
		return DrawableSerializeTypes::SerializeFractalCurve;
	}

	void FractalCurve::write(QDataStream& os){
		os << DrawableType();
		os << (qint32)seed;
		os << mapToScene(start);
		os << mapToScene(end);
		os << mapToScene(innerStartPt->pos());
		os << mapToScene(innerEndPt->pos());
	}

	QPainterPath FractalCurve::shape() const {
		qreal length = Lipuma::distance(start-innerStartPt->pos()) + Lipuma::distance(innerStartPt->pos() - innerEndPt->pos()) + Lipuma::distance(innerEndPt->pos() - end);

		// Figure out the number of points to render the line with
		const int POINTS = length / PERIOD;

		// Generate path
		QPainterPath path;
		QPainterPathStroker s;
		s.setWidth(HEIGHT);

		// First and last point need to always be at zero, so skip the 0th element and the final element
		for (int i = 1; i < POINTS; i++){
			const qreal x = static_cast<float>(i)/static_cast<float>(POINTS);
			const QPointF point = computeBeizer(start, innerStartPt->pos(), innerEndPt->pos(), end, x);
			path.lineTo(point);
		}
		return s.createStroke(path);
	}

	QRectF FractalCurve::boundingRect() const {
		return childrenBoundingRect().marginsAdded(QMargins(5,5,5,5));
	}

	void FractalCurve::setStart(QPointF s){
		// Store end location to keep end in place.
		QPointF gEnd = mapToScene(end);
		setPos(s);
		setEnd(gEnd);
	}

	void FractalCurve::setInnerStart(QPointF s){
		innerStartPt->setPos(mapFromScene(s));
		prepareGeometryChange();
	}

	void FractalCurve::setInnerEnd(QPointF e){
		innerEndPt->setPos(mapFromScene(e));
		prepareGeometryChange();
	}

	void FractalCurve::setEnd(QPointF e){
		QPointF oldEnd = end;
		end = mapFromScene(e);
		endPt->setPos(end);
		innerEndPt->setPos(innerEndPt->pos()+ end - oldEnd);
		prepareGeometryChange();
	}

	float FractalCurve::getFrequency(){
		return frequency;
	}

	QVariant FractalCurve::itemChange(GraphicsItemChange change, const QVariant &val){
		QGraphicsItem::itemChange(change, val);
		if (change == ItemSelectedChange && scene()){
			startPt->setVisible(val.toBool());
			endPt->setVisible(val.toBool());
			innerStartPt->setVisible(val.toBool());
			innerEndPt->setVisible(val.toBool());
		}
		return val;
	}

	void FractalCurve::setFrequency(float f){
		frequency = f;
		prepareGeometryChange();
		update();
	}

	void FractalCurve::paint(QPainter *painter, const QStyleOptionGraphicsItem */* option */, QWidget */* widget */){
		painter->setRenderHint(QPainter::Antialiasing, true);
		// Set highlight color if selected
		if (isSelected()){
			painter->setPen(QColor(255,0,0));
			painter->drawLine(start, innerStartPt->pos());
			painter->drawLine(innerEndPt->pos(), end);
		}

		qreal length = Lipuma::distance(start-innerStartPt->pos()) + Lipuma::distance(innerStartPt->pos() - innerEndPt->pos()) + Lipuma::distance(innerEndPt->pos() - end);

		// Dont draw really really short lines
		if (length < 0.1) return;

		// Figure out the number of points to render the line with
		const int POINTS = length / PERIOD;
		float curve[((POINTS+8)/8)*8] = {}; // Round to nearest multiple of 8, fastnoise runs better with it
		noise->GenUniformGrid2D(curve,0,0,((POINTS+8)/8)*8,1,frequency,seed);

		// Generate path
		QPainterPath path;
		// First and last point need to always be at zero, so skip the 0th element and the final element
		for (int i = 1; i < POINTS; i++){
			const qreal x = static_cast<float>(i)/static_cast<float>(POINTS);
			const QPointF ab = Lipuma::lerp(start, innerStartPt->pos(), x);
			const QPointF bc = Lipuma::lerp(innerStartPt->pos(), innerEndPt->pos(), x);
			const QPointF cd = Lipuma::lerp(innerEndPt->pos(), end, x);
			const QPointF abbc = Lipuma::lerp(ab,bc,x);
			const QPointF bccd = Lipuma::lerp(bc,cd,x);
			QPointF point = Lipuma::lerp(abbc, bccd, x);
			QPointF perp = (abbc-bccd).transposed();
			perp.setY(-perp.y());
			point += Lipuma::normalize(perp)*(curve[i-1]*HEIGHT);
			path.lineTo(point);
		}
		// Draw final point
		path.lineTo(end);
		painter->drawPath(path);
		//painter->drawPath(shape());
		//painter->drawRect(boundingRect());
	}
}
