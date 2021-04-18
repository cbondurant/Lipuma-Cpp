#ifndef POINT_HELPER_HPP
#define POINT_HELPER_HPP

#include <QPointF>
#include <cmath>
#include <algorithm>

namespace Lipuma{
	/*
		Linear Interpolation
		from x=0 => x=1 interpolates from a to b
		This function extrapolates for values outside of [0,1]
		Clamp your inputs if clamped behavior is needed.
	*/
	QPointF lerp(QPointF a, QPointF b, qreal x);

	/*
		Normalizes a 2d vector represented as a QPointF to unit length
	*/
	QPointF normalize(QPointF p);

	// Computes the euclidan distance of a vector
	qreal distance(QPointF p);
}

#endif // POINT_HELPER_HPP
