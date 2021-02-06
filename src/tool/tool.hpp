#ifndef TOOL_TOOL_HHP
#define TOOL_TOOL_HHP

#include <QGraphicsView>
#include <QMouseEvent>
#include <QWheelEvent>

namespace Lipuma {
/*
	Pure virtual interface for reimplementing swappable mouse behavior.
*/
	class Tool {
	public:
		Tool();

		// Events for the brush to handle

		// Called when the tool is activated in the canvas
		virtual void enableEvent(QGraphicsView *view);

		// Called when a different tool is selected while this one is
		virtual void disableEvent(QGraphicsView *view);

		// Passthroughs of Qt events when tool active
		virtual void mousePressEvent(QMouseEvent *e, QGraphicsView *view);
		virtual void mouseReleaseEvent(QMouseEvent *e, QGraphicsView *view);
		virtual void mouseDoubleClickEvent(QMouseEvent *e, QGraphicsView *view);
		virtual void mouseMoveEvent(QMouseEvent *e, QGraphicsView *view);

		virtual void wheelEvent(QWheelEvent *e, QGraphicsView *view);

		// Brush settings interface
	};
}

#endif // TOOL_TOOL_HHP
