#include <QPointF>

#include "math/points.hpp"

namespace Lipuma{
	/*
		Linear Interpolation
		from x=0 => x=1 interpolates from a to b
		This function extrapolates for values outside of [0,1]
		Clamp your inputs if clamped behavior is needed.
	*/
	QPointF lerp(QPointF a, QPointF b, qreal x){
		return (a*(1-x) + b* x);
	}

	/*
		Normalizes a 2d vector represented as a QPointF to unit length
	*/
	QPointF normalize(QPointF p){
		if (p.isNull()) return QPointF();
		qreal d = sqrt(std::fabs(QPointF::dotProduct(p,p)));
		return p/d;
	}

	// Computes the euclidan distance of a vector
	qreal distance(QPointF p){
		return sqrt(std::fabs(QPointF::dotProduct(p,p)));
	}
}