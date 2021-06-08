#ifndef DRAWABLE_FRACTAL_LINE_HPP
#define DRAWABLE_FRACTAL_LINE_HPP

#include <random>

#include <FastNoise/FastNoise.h>
#include <QGraphicsObject>
#include <QPointF>
#include <QRectF>

#include "drawable/editPoint.hpp"
#include "drawable/drawable.hpp"

namespace Lipuma {

	/*
		Fractally deformed line with configurable deformation settings.

		Lacunarity: how much the frequency increases each iteration.
		Gain: how much the amplitude of each iteration decreases.
	*/
	class FractalLine : public Drawable {

	public:
		FractalLine(QPointF, QPointF);
		FractalLine(QDataStream&);
		static qint8 DrawableType();
		void initalizeNoise();
		void initalizeEditPoints();
		void write(QDataStream&);
		QRectF boundingRect() const override;
		void paint(QPainter *, const QStyleOptionGraphicsItem *, QWidget *);

		QVariant itemChange(GraphicsItemChange, const QVariant &val) override;

		// Get the rate at which fractal layers decrease in effect
		float getLacunarity();
		// Set the rate at which fractal layers decrease in effect
		void setLacunarity(float);

		// Set the starting point of the line in canvas space
		void setStart(QPointF);

		// Set the endpoint of the line in canvas space
		void setEnd(QPointF);

		// Get frequency of crossing the zero per unit
		float getFrequency();
		void setFrequency(float);

	private:
		FastNoise::SmartNode<FastNoise::Fractal<>> noise;
		static const int SEGMENTS = 100;
		static const int PERIOD = 2;
		static const int HEIGHT = 10;

		EditPoint *startPt, *endPt;

		QPointF start, end;

		float frequency;
		int seed;
		static std::default_random_engine rand;
	};
}

#endif // DRAWABLE_FRACTAL_LINE_HPP
