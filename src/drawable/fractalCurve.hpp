#ifndef DRAWABLE_FRACTAL_CURVE_HPP
#define DRAWABLE_FRACTAL_CURVE_HPP

#include <random>
#include <iostream>

#include <FastNoise/FastNoise.h>
#include <QGraphicsObject>
#include <QDataStream>
#include <QPointF>
#include <QRectF>

#include "drawable/editPoint.hpp"
#include "drawable/drawable.hpp"
#include "math/beizer.hpp"

namespace Lipuma
{

	/*
		Fractally deformed line with configurable deformation settings.

		Lacunarity: how much the frequency increases each iteration.
		Gain: how much the amplitude of each iteration decreases.
	*/
	class FractalCurve : public Drawable {

	public:
		FractalCurve(QPointF, QPointF);
		FractalCurve(QDataStream&);
		void write(QDataStream&) override;
		static qint8 DrawableType();
		void initalizeEditPoints();
		void initalizeNoise();
		QRectF boundingRect() const override;
		QPainterPath shape() const override;
		void paint(QPainter *, const QStyleOptionGraphicsItem *, QWidget *) override;

		QVariant itemChange(GraphicsItemChange, const QVariant &val) override;

		// Get the rate at which fractal layers decrease in effect
		float getLacunarity();
		// Set the rate at which fractal layers decrease in effect
		void setLacunarity(float);

		// Set the starting point of the line in canvas space
		void setStart(QPointF);

		void setInnerStart(QPointF);

		// Set the endpoint of the line in canvas space
		void setEnd(QPointF);

		void setInnerEnd(QPointF);

		// Get frequency of crossing the zero per unit
		float getFrequency();
		void setFrequency(float);


		friend std::ostream& operator<<(std::ostream& os, const FractalCurve& dt);

	private:
		FastNoise::SmartNode<FastNoise::Fractal<>> noise;
		static const int SEGMENTS = 100;
		static const int PERIOD = 2;
		static const int HEIGHT = 10;

		EditPoint *startPt, *innerStartPt, *endPt, *innerEndPt;

		QPointF start, end;

		BeizerCurve curve;

		float frequency;
		qint32 seed;
		static std::default_random_engine rand;
	};
}

#endif // DRAWABLE_FRACTAL_LINE_HPP
