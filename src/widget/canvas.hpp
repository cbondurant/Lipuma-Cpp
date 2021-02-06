#ifndef CANVAS_HPP
#define CANVAS_HPP

#include <QGraphicsView>
#include <QGraphicsItem>
#include <QPointF>
#include <QWheelEvent>
#include <QKeyEvent>

#include "tool/tool.hpp"
namespace Lipuma {
	/*
		Subclass of the QGraphics view.
		Intends to override and improve panning behavior.
	*/
	class Canvas : public QGraphicsView {
		Q_OBJECT

	public:
		explicit Canvas(QGraphicsScene *parent = nullptr);

		// Provide the current tool
		Tool *getCurrentTool();
		// Set the currently used tool
		void setCurrentTool(Tool *brush);

	protected:
		void wheelEvent(QWheelEvent *e) override;
		void mouseMoveEvent(QMouseEvent *e) override;
		void mousePressEvent(QMouseEvent *e) override;
		void mouseReleaseEvent(QMouseEvent *e) override;
		void mouseDoubleClickEvent(QMouseEvent *e) override;
		void keyPressEvent(QKeyEvent *e) override;

	public slots:
		void toolSelected(Tool *tool);

	private:
		Tool *_currentTool;
		QPointF _offset;
		bool _isPanning;
		QPoint _panPrev;
	};

}
#endif // CANVAS_HPP
