#ifndef MATH_BEIZER_HHP
#define MATH_BEIZER_HHP

#include <QPointF>
#include <iterator>
#include <cstddef>
#include <tuple>
#include <memory>

namespace Lipuma
{
	struct PointTangent
	{
		QPointF point;
		QPointF tangent;
	};
	class BeizerCurve
	{
	public:
		// A curve iterator that iterates over n points and returns b(n) at each value
		struct PointTangentIterator
		{
			using iterator_category = std::input_iterator_tag;
			using value_type = PointTangent;

		public:
			explicit PointTangentIterator(const BeizerCurve *curve, int segments, qreal start, qreal end);
			PointTangentIterator &operator++();
			PointTangentIterator operator++(int);
			friend bool operator==(const PointTangentIterator &a, const PointTangentIterator &b);
			friend bool operator!=(const PointTangentIterator &a, const PointTangentIterator &b);
			PointTangent operator*() const;
			const std::unique_ptr<PointTangent> operator->() const;

		private:
			const BeizerCurve *curve;
			qreal offset() const;
			int segments;
			int currentSegment;
			qreal start;
			qreal end;
		};

		BeizerCurve(QPointF, QPointF, QPointF, QPointF);
		BeizerCurve();

		QPointF getPoint(const qreal) const;
		PointTangent getPointTangent(const qreal) const;
		PointTangentIterator sweepCurveIterator(const int) const;
		PointTangentIterator end() const;

		void setPtA(QPointF);
		void setPtB(QPointF);
		void setPtC(QPointF);
		void setPtD(QPointF);

		QPointF getPtA();
		QPointF getPtB();
		QPointF getPtC();
		QPointF getPtD();

		qreal length() const;

	private:
		QPointF ptA, ptB, ptC, ptD;
	};
}

#endif