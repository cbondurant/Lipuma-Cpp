#include <memory>

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
		assert(false); // This should never be called directly
		return std::unique_ptr<PointTangent>();
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
		const qreal x = static_cast<float>(currentSegment) / static_cast<float>(segments);
		return getCurve()->getPointTangent(x);
	}

	const std::unique_ptr<PointTangent> BezierCurve::StandardPointTangentIterator::operator->() const
	{
		const qreal x = static_cast<float>(currentSegment) / static_cast<float>(segments);
		std::unique_ptr<PointTangent> ret(new PointTangent(getCurve()->getPointTangent(x)));
		return ret;
	}


	qreal BezierCurve::StandardPointTangentIterator::offset() const
	{
		if (currentSegment > segments | segments == 0)
		{
			return -1;
		}
		return static_cast<qreal>(currentSegment) / static_cast<qreal>(segments);
	}


	// Equidistant point tangent type begins here.

	BezierCurve::LinearPointTangentIterator::LinearPointTangentIterator(const BezierCurve *curve, int segments, int subSegments, qreal start, qreal end) :
	PointTangentIterator(curve), segments(segments), subSegments(subSegments),
	start(start), end(end){

	}

	BezierCurve::PointTangentIterator& BezierCurve::LinearPointTangentIterator::operator++(){
		prevPoint = (*this)->point;
		currentSubsegment += 1;
		return *this;
	}

	PointTangent BezierCurve::LinearPointTangentIterator::operator*() const{

	}

	const std::unique_ptr<PointTangent> BezierCurve::LinearPointTangentIterator::operator->() const{

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

	BezierCurve::PointTangentIterator BezierCurve::sweepCurveIterator(const int elements) const
	{
		return BezierCurve::StandardPointTangentIterator(this, elements, 0, 1);
	}

	BezierCurve::BezierCurve(QPointF a, QPointF b, QPointF c, QPointF d) : ptA(a), ptB(b), ptC(c), ptD(d) {}
	BezierCurve::BezierCurve() {}

	BezierCurve::PointTangentIterator BezierCurve::end() const
	{
		return sweepCurveIterator(0);
	}

	qreal BezierCurve::length() const
	{
		QPointF prev = ptA;
		qreal len = 0;
		for (auto i = sweepCurveIterator(100); i != end(); ++i)
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