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

	BezierCurve::PointTangentIterator::~PointTangentIterator(){}

	BezierCurve::PointTangentIterator &BezierCurve::PointTangentIterator::operator++(){
		return *this;
	}
	BezierCurve::PointTangentIterator BezierCurve::PointTangentIterator::operator++(int)
	{
		BezierCurve::PointTangentIterator retval = *this;
		++(*this);
		return retval;
	}
	PointTangent BezierCurve::PointTangentIterator::operator*() const {
		assert(false); // This should never be called directly
		return PointTangent();
	}
	const std::unique_ptr<PointTangent> BezierCurve::PointTangentIterator::operator->() const {
		// For some reason the return of -> has to be dereferenceable, so cast it to a unique_ptr so it cleans itself up afterwards, no leaks.
		std::unique_ptr<PointTangent> ret(new PointTangent(**this));
		return ret;
	}

	// Comparison between point tangent types
	bool operator==(const BezierCurve::PointTangentIterator &a, const BezierCurve::PointTangentIterator &b)
	{
		return ((a->point == b->point) & (a.getCurve() == b.getCurve()));
	}

	bool operator!=(const BezierCurve::PointTangentIterator &a, const BezierCurve::PointTangentIterator &b)
	{
		return !(a == b);
	}

	// Base PtTangent Types

	// Standard non-equidistant point tangent iterator definition begins here

	BezierCurve::StandardPointTangentIterator::StandardPointTangentIterator(const BezierCurve *curve, int segments, qreal start, qreal end) : PointTangentIterator(curve), segments(segments), start(start), end(end), currentSegment(0){}

	BezierCurve::PointTangentIterator &BezierCurve::StandardPointTangentIterator::operator++()
	{
		currentSegment += 1;
		return *this;
	}


	PointTangent BezierCurve::StandardPointTangentIterator::operator*() const
	{
		if (segments == 0 | currentSegment >= segments){
			return PointTangent{QPointF(DBL_MAX, DBL_MAX), QPointF(DBL_MAX, DBL_MAX)};
		}
		const qreal x = static_cast<float>(currentSegment) / static_cast<float>(segments);
		return getCurve()->getPointTangent(x);
	}

	// Equidistant point tangent type begins here.

	BezierCurve::LinearPointTangentIterator::LinearPointTangentIterator(const BezierCurve *curve, int segments, int subSegments, qreal start, qreal end) :
	PointTangentIterator(curve), segments(segments), subSegments(subSegments),
	start(start), end(end){
		currentSegment=0;
		path = QPainterPath();
		for (BezierCurve::PointTangentIterator& i = curve->sweepCurveIterator(subSegments); i != curve->end(); ++i)
		{
			path.lineTo(i->point);
		}
	}

	BezierCurve::PointTangentIterator& BezierCurve::LinearPointTangentIterator::operator++(){
		currentSegment += 1;
		return *this;
	}

	PointTangent BezierCurve::LinearPointTangentIterator::operator*() const{
		if (segments == 0 | currentSegment >= segments){
			return PointTangent{QPointF(DBL_MAX, DBL_MAX), QPointF(DBL_MAX, DBL_MAX)};
		}
		const qreal x = static_cast<float>(currentSegment) / static_cast<float>(segments);
		return PointTangent{path.pointAtPercent(x), QPointF(1,path.slopeAtPercent(x))};
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

	BezierCurve::StandardPointTangentIterator& BezierCurve::sweepCurveIterator(const int elements) const
	{
		BezierCurve::StandardPointTangentIterator* it = new BezierCurve::StandardPointTangentIterator(this, elements, 0, 1);
		return *it;
	}

	BezierCurve::LinearPointTangentIterator& BezierCurve::sweepLinearCurveIterator(const int elements) const
	{
		// the log is used for the subelement count because otherwise iterating through it becomes very very inefficent.
		BezierCurve::LinearPointTangentIterator* it = new BezierCurve::LinearPointTangentIterator(this, elements, log(elements)*5, 0, 1);
		return *it;
	}

	BezierCurve::BezierCurve(QPointF a, QPointF b, QPointF c, QPointF d) : ptA(a), ptB(b), ptC(c), ptD(d) {}
	BezierCurve::BezierCurve(){}

	BezierCurve::PointTangentIterator& BezierCurve::end() const
	{
		return sweepCurveIterator(0);
	}

	qreal BezierCurve::length() const
	{
		QPointF prev = ptA;
		qreal len = 0;
		for (BezierCurve::PointTangentIterator &i = sweepCurveIterator(100); i != end(); ++i)
		{
			len += distance(prev - i->point);
			prev = i->point;
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