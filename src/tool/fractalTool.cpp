#include <tool/fractalTool.hpp>

#include <QGraphicsView>
#include <QMouseEvent>
#include <QWheelEvent>

#include <drawable/fractalLine.hpp>

namespace Lipuma {
	FractalTool::FractalTool(){
		line = nullptr;
		isDrawing = false;
	}

	void FractalTool::mousePressEvent(QMouseEvent *e, QGraphicsView *view){
		if (e->button() == Qt::LeftButton){
			QPointF canvaspos = view->mapToScene(e->pos());
			line = new FractalLine(canvaspos, canvaspos);
			view->scene()->addItem(line);
			view->scene()->clearSelection();
			isDrawing = true;
			e->accept();
		}else{
			e->ignore();
		}
	}

	void FractalTool::mouseMoveEvent(QMouseEvent *e, QGraphicsView *view){
		QPointF canvaspos = view->mapToScene(e->pos());
		if (isDrawing) {
			line->setEnd(canvaspos);
			e->accept();
		}else{
			e->ignore();
		}
	}

	void FractalTool::mouseReleaseEvent(QMouseEvent *e, QGraphicsView */* view */){
		// Im not sure if I should unset the line here.
		if (isDrawing){
			isDrawing = false;
			e->accept();
		}else{
			e->ignore();
		}
	}

	void FractalTool::wheelEvent(QWheelEvent *e, QGraphicsView */* view */){
		if (isDrawing){
			float freq = line->getFrequency();
			if (e->angleDelta().y() > 0){
				if (freq > 0){
					line->setFrequency(freq / 0.9);
				}
			}else{
				line->setFrequency(freq * 0.9);
			}
			e->accept();
		}else{
			e->ignore();
		}
	}
}
