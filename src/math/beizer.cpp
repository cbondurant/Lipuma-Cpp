#include <memory>

#include "math/beizer.hpp"
#include "math/points.hpp"

namespace Lipuma
{
	BeizerCurve::PointTangentIterator::PointTangentIterator(const BeizerCurve *curve, int segments, qreal start, qreal end) : curve(curve), segments(segments), start(start), end(end), currentSegment(0){}

	BeizerCurve::PointTangentIterator &BeizerCurve::PointTangentIterator::operator++()
	{
		currentSegment += 1;
		return *this;
	}

	BeizerCurve::PointTangentIterator BeizerCurve::PointTangentIterator::operator++(int)
	{
		BeizerCurve::PointTangentIterator retval = *this;
		++(*this);
		return retval;
	}

	PointTangent BeizerCurve::PointTangentIterator::operator*() const
	{
		const qreal x = static_cast<float>(currentSegment) / static_cast<float>(segments);
		return curve->getPointTangent(x);
	}

	const std::unique_ptr<PointTangent> BeizerCurve::PointTangentIterator::operator->() const
	{
		const qreal x = static_cast<float>(currentSegment) / static_cast<float>(segments);
		std::unique_ptr<PointTangent> ret(new PointTangent(curve->getPointTangent(x)));
		return ret;
	}

	bool operator==(const BeizerCurve::PointTangentIterator &a, const BeizerCurve::PointTangentIterator &b)
	{
		return (a.offset() == b.offset());
	}

	bool operator!=(const BeizerCurve::PointTangentIterator &a, const BeizerCurve::PointTangentIterator &b)
	{
		return !(a == b);
	}

	qreal BeizerCurve::PointTangentIterator::offset() const
	{
		if (currentSegment > segments | segments == 0)
		{
			return -1;
		}
		return static_cast<qreal>(currentSegment) / static_cast<qreal>(segments);
	}

	QPointF BeizerCurve::getPoint(const qreal x) const
	{
		const QPointF bc = Lipuma::lerp(ptB, ptC, x);
		const QPointF abbc = Lipuma::lerp(Lipuma::lerp(ptA, ptB, x), bc, x);
		const QPointF bccd = Lipuma::lerp(bc, Lipuma::lerp(ptC, ptD, x), x);
		return Lipuma::lerp(abbc, bccd, x);
	}

	PointTangent BeizerCurve::getPointTangent(const qreal x) const
	{
		const QPointF bc = Lipuma::lerp(ptB, ptC, x);
		const QPointF abbc = Lipuma::lerp(Lipuma::lerp(ptA, ptB, x), bc, x);
		const QPointF bccd = Lipuma::lerp(bc, Lipuma::lerp(ptC, ptD, x), x);
		return PointTangent{Lipuma::lerp(abbc, bccd, x), abbc - bccd};
	}

	BeizerCurve::PointTangentIterator BeizerCurve::sweepCurveIterator(const int elements) const
	{
		return BeizerCurve::PointTangentIterator(this, elements, 0, 1);
	}

	BeizerCurve::BeizerCurve(QPointF a, QPointF b, QPointF c, QPointF d) : ptA(a), ptB(b), ptC(c), ptD(d) {}
	BeizerCurve::BeizerCurve() : ptA(QPointF()), ptB(QPointF()), ptC(QPointF()), ptD(QPointF()) {}

	BeizerCurve::PointTangentIterator BeizerCurve::end() const
	{
		return sweepCurveIterator(0);
	}

	qreal BeizerCurve::length() const
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

	void BeizerCurve::setPtA(QPointF pt) { ptA = pt; }
	void BeizerCurve::setPtB(QPointF pt) { ptB = pt; }
	void BeizerCurve::setPtC(QPointF pt) { ptC = pt; }
	void BeizerCurve::setPtD(QPointF pt) { ptD = pt; }

	QPointF BeizerCurve::getPtA() { return ptA; }
	QPointF BeizerCurve::getPtB() { return ptB; }
	QPointF BeizerCurve::getPtC() { return ptC; }
	QPointF BeizerCurve::getPtD() { return ptD; }
}