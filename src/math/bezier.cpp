#include <memory>
#include <QPainterPath>
#include <float.h>
#include "math/bezier.hpp"
#include "math/points.hpp"

namespace Lipuma
{

	const BezierCurve * BezierCurve::PointTangentIterator::getCurve() const {
		return _curve;
	}

	BezierCurve::PointTangentIterator::PointTangentIterator (const BezierCurve *curve) : _curve(curve){}

	PointTangent BezierCurve::PointTangentIterator::getPointTangentAdvance(){
		PointTangent ret = getPointTangent();
		advance();
		return ret;
	}

	bool BezierCurve::PointTangentIterator::isEmpty() const{ // Base type will never return a valid response
		return true;
	}

	void BezierCurve::PointTangentIterator::advance(){

	}

	PointTangent BezierCurve::PointTangentIterator::getPointTangent() const {
		assert(false); // This should never be called directly
		return PointTangent();
	}

	// Base PtTangent Types
	// Standard non-equidistant point tangent iterator definition begins here

	BezierCurve::StandardPointTangentIterator::StandardPointTangentIterator(const BezierCurve *curve, int segments, qreal start, qreal end) : PointTangentIterator(curve), segments(segments), start(start), end(end), currentSegment(0){}

	void BezierCurve::StandardPointTangentIterator::advance()
	{
		currentSegment += 1;
	}

	bool BezierCurve::StandardPointTangentIterator::isEmpty() const{
		return segments == 0 | currentSegment >= segments;
	}

	PointTangent BezierCurve::StandardPointTangentIterator::getPointTangent() const
	{
		if (isEmpty()){
			return PointTangent{QPointF(DBL_MAX, DBL_MAX), QPointF(DBL_MAX, DBL_MAX)};
		}
		const qreal x = static_cast<float>(currentSegment) / static_cast<float>(segments-1);
		return getCurve()->getPointTangent(x);
	}

	// Equidistant point tangent type begins here.

	BezierCurve::LinearPointTangentIterator::LinearPointTangentIterator(const BezierCurve *curve, int segments, int subSegments, qreal start, qreal end) :
	PointTangentIterator(curve), segments(segments), subSegments(subSegments),
	start(start), end(end), pathSegment(0){
		path = QPainterPath();
		for (auto i = curve->sweepCurveIterator(subSegments); !i->isEmpty(); i->advance())
		{
			path.lineTo(i->getPointTangent().point);
		}
		pathLength = path.length();
	}

	bool BezierCurve::LinearPointTangentIterator::isEmpty() const{
		return segments == 0 | pathSegment >= path.elementCount();
	}

	void BezierCurve::LinearPointTangentIterator::advance(){
		qreal step = pathLength/static_cast<float>(segments);
		qreal distToNextElement = distance(currLoc - path.elementAt(pathSegment));
		while (step >= distToNextElement){
			currLoc = path.elementAt(pathSegment);
			step -= distToNextElement;
			pathSegment += 1;
			distToNextElement = distance(currLoc - path.elementAt(pathSegment));
		}
		currLoc += normalize(path.elementAt(pathSegment) - currLoc)*step;
	}

	PointTangent BezierCurve::LinearPointTangentIterator::getPointTangent() const{
		if (isEmpty()){
			return PointTangent{QPointF(DBL_MAX, DBL_MAX), QPointF(DBL_MAX, DBL_MAX)};
		}
		return PointTangent{currLoc, currLoc - path.elementAt(pathSegment)};
	}

	QPointF BezierCurve::getPoint(const qreal x) const
	{
		const QPointF bc = Lipuma::lerp(ptB, ptC, x);
		const QPointF abbc = Lipuma::lerp(Lipuma::lerp(ptA, ptB, x), bc, x);
		const QPointF bccd = Lipuma::lerp(bc, Lipuma::lerp(ptC, ptD, x), x);
		return Lipuma::lerp(abbc, bccd, x);
	}

	PointTangent BezierCurve::getPointTangent(const qreal x) const
	{
		const QPointF bc = Lipuma::lerp(ptB, ptC, x);
		const QPointF abbc = Lipuma::lerp(Lipuma::lerp(ptA, ptB, x), bc, x);
		const QPointF bccd = Lipuma::lerp(bc, Lipuma::lerp(ptC, ptD, x), x);
		return PointTangent{Lipuma::lerp(abbc, bccd, x), abbc - bccd};
	}

	std::unique_ptr<BezierCurve::PointTangentIterator> BezierCurve::sweepCurveIterator(const int elements) const
	{
		return std::unique_ptr<BezierCurve::StandardPointTangentIterator>(new BezierCurve::StandardPointTangentIterator(this, elements, 0, 1));
	}

	std::unique_ptr<BezierCurve::PointTangentIterator> BezierCurve::sweepLinearCurveIterator(const int elements) const
	{
		return std::unique_ptr<BezierCurve::LinearPointTangentIterator>(new BezierCurve::LinearPointTangentIterator(this, elements, elements, 0, 1));
	}

	BezierCurve::BezierCurve(QPointF a, QPointF b, QPointF c, QPointF d) : ptA(a), ptB(b), ptC(c), ptD(d) {}
	BezierCurve::BezierCurve(){}

	std::unique_ptr<BezierCurve::PointTangentIterator> BezierCurve::end() const
	{
		return sweepCurveIterator(0);
	}

	qreal BezierCurve::length() const
	{
		QPointF prev = ptA;
		qreal len = 0;
		for (auto i = sweepCurveIterator(100); !i->isEmpty(); i->advance())
		{
			len += distance(prev - i->getPointTangent().point);
			prev = i->getPointTangent().point;
		}
		return len;
	}

	void BezierCurve::setPtA(QPointF pt) { ptA = pt; }
	void BezierCurve::setPtB(QPointF pt) { ptB = pt; }
	void BezierCurve::setPtC(QPointF pt) { ptC = pt; }
	void BezierCurve::setPtD(QPointF pt) { ptD = pt; }

	QPointF BezierCurve::getPtA() { return ptA; }
	QPointF BezierCurve::getPtB() { return ptB; }
	QPointF BezierCurve::getPtC() { return ptC; }
	QPointF BezierCurve::getPtD() { return ptD; }
}