#include "tool/tool.hpp"

#include <QGraphicsView>
#include <QMouseEvent>
#include <QWheelEvent>


namespace Lipuma {
	Tool::Tool() {}
	void Tool::enableEvent(QGraphicsView */* view */) {}
	void Tool::disableEvent(QGraphicsView */* view */) {}
	void Tool::mousePressEvent(QMouseEvent *e, QGraphicsView */* view */) {e->ignore();}
	void Tool::mouseReleaseEvent(QMouseEvent *e, QGraphicsView */* view */) {e->ignore();}
	void Tool::mouseDoubleClickEvent(QMouseEvent *e, QGraphicsView */* view */) {e->ignore();}
	void Tool::mouseMoveEvent(QMouseEvent *e, QGraphicsView */* view */) {e->ignore();}
	void Tool::wheelEvent(QWheelEvent *e, QGraphicsView */* view */) {e->ignore();}
}
