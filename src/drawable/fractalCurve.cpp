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

#include "math/bezier.hpp"
#include "drawable/editPoint.hpp"
#include "math/points.hpp"



namespace Lipuma {

	inline QPointF computeBeizer(const QPointF a, const QPointF b, const QPointF c, const QPointF d, qreal x){
			const QPointF bc = Lipuma::lerp(b, c, x);
			const QPointF abbc = Lipuma::lerp(Lipuma::lerp(a, b, x),bc,x);
			const QPointF bccd = Lipuma::lerp(bc,Lipuma::lerp(c, d, x),x);
			return Lipuma::lerp(abbc, bccd, x);
	}

	std::default_random_engine FractalCurve::rand;

	void FractalCurve::initalizeNoise(){
		seed = FractalCurve::rand();
		setFlag(QGraphicsItem::ItemIsSelectable);
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
		QPointF a,b,c,d;
		is >> a >> b >> c >> d;
		curve = BezierCurve(a,b,c,d);
		setStart(a);
		setEnd(b);
		setInnerStart(b);
		setInnerEnd(d);
		is >> frequency;
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

		os << frequency;
	}
	QPainterPath FractalCurve::shape() const
	{
		qreal length = curve.length();

		// Figure out the number of points to render the line with
		const int POINTS = length / PERIOD;

		// Generate path
		QPainterPath path;
		QPainterPathStroker s;
		s.setWidth(HEIGHT);

		// First and last point need to always be at zero, so skip the 0th element and the final element
		for (auto i = curve.sweepCurveIterator(POINTS); !i->isEmpty(); i->advance())
		{
			path.lineTo(i->getPointTangent().point);
		}
		return s.createStroke(path);
	}

	QRectF FractalCurve::boundingRect() const
	{
		return childrenBoundingRect().marginsAdded(QMargins(5, 5, 5, 5));
	}

	void FractalCurve::setStart(QPointF s)
	{
		// Store end location to keep end in place.
		QPointF gEnd = mapToScene(end);
		setPos(s);
		setEnd(gEnd);
	}

	void FractalCurve::setInnerStart(QPointF s)
	{
		innerStartPt->setPos(mapFromScene(s));
		curve.setPtB(innerStartPt->pos());
		prepareGeometryChange();
	}

	void FractalCurve::setInnerEnd(QPointF e)
	{
		innerEndPt->setPos(mapFromScene(e));
		curve.setPtC(innerEndPt->pos());
		prepareGeometryChange();
	}

	void FractalCurve::setEnd(QPointF e)
	{
		QPointF oldEnd = end;
		end = mapFromScene(e);
		endPt->setPos(end);
		curve.setPtD(endPt->pos());
		innerEndPt->setPos(innerEndPt->pos() + end - oldEnd);
		curve.setPtC(innerEndPt->pos());
		prepareGeometryChange();
	}

	float FractalCurve::getFrequency()
	{
		return frequency;
	}

	QVariant FractalCurve::itemChange(GraphicsItemChange change, const QVariant &val)
	{
		QGraphicsItem::itemChange(change, val);
		if (change == ItemSelectedChange && scene())
		{
			startPt->setVisible(val.toBool());
			endPt->setVisible(val.toBool());
			innerStartPt->setVisible(val.toBool());
			innerEndPt->setVisible(val.toBool());
		}
		return val;
	}

	void FractalCurve::setFrequency(float f)
	{
		frequency = f;
		prepareGeometryChange();
		update();
	}

	void FractalCurve::paint(QPainter *painter, const QStyleOptionGraphicsItem * /* option */, QWidget * /* widget */)
	{
		painter->setRenderHint(QPainter::Antialiasing, true);
		// Set highlight color if selected
		if (isSelected())
		{
			painter->setPen(QColor(255, 0, 0));
			painter->drawLine(start, innerStartPt->pos());
			painter->drawLine(innerEndPt->pos(), end);
		}

		qreal length = curve.length();

		// Figure out the number of points to render the line with
		const int POINTS = length / PERIOD;
		// Dont draw really really short lines
		if (length < 1)
			return;
		std::vector<float> curveNoise = std::vector<float>(((POINTS + 8) / 8) * 8); // Round to nearest multiple of 8, fastnoise runs better with it
		noise->GenUniformGrid2D(curveNoise.data(), 0, 0, ((POINTS + 8) / 8) * 8, 1, frequency, seed);

		// Generate path
		QPainterPath path;

		std::vector<float>::iterator ci = curveNoise.begin();
		for (auto i = curve.sweepLinearCurveIterator(POINTS); !i->isEmpty(); i->advance())
		{
			QPointF point = i->getPointTangent().point;
			QPointF perp = i->getPointTangent().tangent.transposed();
			perp.setY(-perp.y());
			point += Lipuma::normalize(perp) * ((*ci++) * HEIGHT);
			path.lineTo(point);
		}
		// Draw final point
		path.lineTo(end);
		painter->drawPath(path);
		//painter->drawPath(shape());
		//painter->drawRect(boundingRect());
	}
}
