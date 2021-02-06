#ifndef TOOL_FRACTAL_CURVE_HPP
#define TOOL_FRACTAL_CURVE_HPP

#include <QGraphicsView>
#include <QMouseEvent>
#include <QWheelEvent>

#include "drawable/fractalCurve.hpp"
#include "tool/tool.hpp"

namespace Lipuma {

	/*
		This tool implements a click-drag interface for drawing brushes
	*/
	class FractalCurveTool : public Tool{
	public:
		FractalCurveTool();

		void mousePressEvent(QMouseEvent *e, QGraphicsView *view) override;
		void mouseReleaseEvent(QMouseEvent *e, QGraphicsView *view) override;
		void mouseMoveEvent(QMouseEvent *e, QGraphicsView *view) override;
		void wheelEvent(QWheelEvent *e, QGraphicsView *view) override;
	private:
		FractalCurve *curve;
		bool isDrawing;
	};
}

#endif //TOOL_FRACTALTOOL_HPP
