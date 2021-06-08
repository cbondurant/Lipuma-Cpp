#ifndef MATH_BEIZER_HHP
#define MATH_BEIZER_HHP

#include <QPointF>
#include <iterator>
#include <cstddef>
#include <tuple>
#include <memory>
#include <QPainterPath>

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

		// The base class for the point tangent iterator
		struct PointTangentIterator
		{
		public:
			PointTangentIterator(const BezierCurve* curve);
			virtual void advance(); // Increment iterator
			virtual bool isEmpty() const; // returns true when at end of defined iteraton
			virtual PointTangent getPointTangent() const; // Returns current point tangent value, or ((0,0),(0,0)) if isEmpty is true.
			PointTangent getPointTangentAdvance(); // Implicitly calls getPointTangent() followed by advance()
			const BezierCurve* getCurve() const;

		private:
			const BezierCurve* _curve;
		};

		struct StandardPointTangentIterator : public PointTangentIterator
		{
		public:
			StandardPointTangentIterator(const BezierCurve *curve, int segments, qreal start, qreal end);
			void advance() override;
			PointTangent getPointTangent() const override;
			bool isEmpty() const override;

		private:
			int segments;
			int currentSegment;
			qreal start;
			qreal end;
		};

		struct LinearPointTangentIterator : public PointTangentIterator
		{
		public:
			LinearPointTangentIterator(const BezierCurve *curve, int segments, int subSegments, qreal start, qreal end);
			void advance() override;
			PointTangent getPointTangent() const override;
			bool isEmpty() const override;

		private:
			int segments;
			int currentSegment;
			int subSegments;
			QPainterPath path;
			qreal pathLength;
			int pathSegment;
			qreal pathSegmentDist;
			QPointF currLoc;
			qreal start;
			qreal end;
		};

		BezierCurve(QPointF, QPointF, QPointF, QPointF);
		BezierCurve();

		QPointF getPoint(const qreal) const;
		PointTangent getPointTangent(const qreal) const;
		std::unique_ptr<PointTangentIterator> sweepCurveIterator(const int) const;

		std::unique_ptr<PointTangentIterator> end() const;

		std::unique_ptr<PointTangentIterator> sweepLinearCurveIterator(const int) const;

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