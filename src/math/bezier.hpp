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
	class BezierCurve
	{
	public:
		// A curve iterator that iterates over n points and returns b(n) at each value
		struct PointTangentIterator
		{
			using iterator_category = std::input_iterator_tag;
			using value_type = PointTangent;

		public:
			PointTangentIterator(const BezierCurve* curve);
			virtual ~PointTangentIterator();
			virtual PointTangentIterator &operator++();
			PointTangentIterator operator++(int);
			friend bool operator==(const PointTangentIterator &a, const PointTangentIterator &b);
			friend bool operator!=(const PointTangentIterator &a, const PointTangentIterator &b);
			virtual PointTangent operator*() const;
			virtual const std::unique_ptr<PointTangent> operator->() const;
			const BezierCurve* getCurve() const;

		private:
			const BezierCurve* _curve;
		};

		struct StandardPointTangentIterator : public PointTangentIterator
		{
			using iterator_category = std::input_iterator_tag;
			using value_type = PointTangent;

		public:
			StandardPointTangentIterator(const BezierCurve *curve, int segments, qreal start, qreal end);
			PointTangentIterator &operator++() override;
			PointTangent operator*() const override;
			const std::unique_ptr<PointTangent> operator->() const override;

		private:
			qreal offset() const;
			int segments;
			int currentSegment;
			qreal start;
			qreal end;
		};

		struct LinearPointTangentIterator : public PointTangentIterator
		{
			using iterator_category = std::input_iterator_tag;
			using value_type = PointTangent;

		public:
			LinearPointTangentIterator(const BezierCurve *curve, int segments, int subSegments, qreal start, qreal end);
			PointTangentIterator &operator++() override;
			PointTangent operator*() const override;
			const std::unique_ptr<PointTangent> operator->() const override;

		private:
			int segments;
			int currentSegment;
			int subSegments;
			int currentSubsegment;
			qreal curLen;
			QPointF prevPoint;
			qreal start;
			qreal end;
		};

		BezierCurve(QPointF, QPointF, QPointF, QPointF);
		BezierCurve();

		QPointF getPoint(const qreal) const;
		PointTangent getPointTangent(const qreal) const;
		PointTangentIterator sweepCurveIterator(const int) const;

		PointTangentIterator end() const;

		LinearPointTangentIterator LinearSweepCurveIterator(const int) const;

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