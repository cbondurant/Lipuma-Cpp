#include <tool/fractalCurveTool.hpp>

#include <QGraphicsView>
#include <QMouseEvent>
#include <QWheelEvent>

#include <drawable/fractalCurve.hpp>

namespace Lipuma {
	FractalCurveTool::FractalCurveTool(){
		curve = nullptr;
		isDrawing = false;
	}

	void FractalCurveTool::mousePressEvent(QMouseEvent *e, QGraphicsView *view){
		if (e->button() == Qt::LeftButton){
			QPointF canvaspos = view->mapToScene(e->pos());
			curve = new FractalCurve(canvaspos, canvaspos);
			view->scene()->addItem(curve);
			view->scene()->clearSelection();
			isDrawing = true;
			e->accept();
		}else{
			e->ignore();
		}
	}

	void FractalCurveTool::mouseMoveEvent(QMouseEvent *e, QGraphicsView *view){
		QPointF canvaspos = view->mapToScene(e->pos());
		if (isDrawing) {
			curve->setEnd(canvaspos);
			e->accept();
		}else{
			e->ignore();
		}
	}

	void FractalCurveTool::mouseReleaseEvent(QMouseEvent *e, QGraphicsView */* view */){
		// Im not sure if I should unset the line here.
		if (isDrawing){
			isDrawing = false;
			e->accept();
		}else{
			e->ignore();
		}
	}

	void FractalCurveTool::wheelEvent(QWheelEvent *e, QGraphicsView */* view */){
		if (isDrawing){
			float freq = curve->getFrequency();
			if (e->angleDelta().y() > 0){
				if (freq > 0){
					curve->setFrequency(freq / 0.9);
				}
			}else{
				curve->setFrequency(freq * 0.9);
			}
			e->accept();
		}else{
			e->ignore();
		}
	}
}
