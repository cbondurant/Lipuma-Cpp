#include "canvas.hpp"

#include <cmath>
#include <cstdlib>
#include <iostream>
#include <set>
#include <type_traits>

#include <QGraphicsView>
#include <QGraphicsItem>
#include <QFileDialog>
#include <QKeyEvent>
#include <QPointF>
#include <QPainter>

#include "drawable/fractalLine.hpp"
#include "tool/fractalTool.hpp"
#include "tool/tool.hpp"
#include "tool/toolManager.hpp"
#include "file/serializer.hpp"

namespace Lipuma {
	Canvas::Canvas(QGraphicsScene *parent) : QGraphicsView(parent){
		setBackgroundRole(QPalette::Base);
		setAutoFillBackground(true);
		setDragMode(QGraphicsView::RubberBandDrag);
		setResizeAnchor(QGraphicsView::AnchorUnderMouse);
		_currentTool = ToolManager::getFractalTool();
		setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOn);
		setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOn);


		// DEBUG: Graphics to mark the center of the scene
		/*
		scene()->addLine(-1,-1,1,1);
		scene()->addLine(-1,1,1,-1);
		scene()->addItem(new FractalLine(QPoint(110,100), QPointF(110,-100)));
		scene()->addItem(new FractalLine(QPoint(100,-110), QPointF(-100,-110)));
		scene()->addItem(new FractalLine(QPoint(-110,-100), QPointF(-110,100)));
		scene()->addItem(new FractalLine(QPoint(-100,110), QPointF(100,110)));
		*/
		setSceneRect(-1000, -1000, 2000, 2000);
	}

	void Canvas::wheelEvent(QWheelEvent *e){
		_currentTool->wheelEvent(e, this);
		if (!e->isAccepted()){
			if (e->angleDelta().y() < 0){
				scale(1.0/1.5, 1.0/1.5);
			}
			if (e->angleDelta().y() > 0){
				scale(1.5, 1.5);
			}

			if (transform().m11() < 0.1){
				scale(0.1/transform().m11(), 0.1/transform().m22());
			}

			if (transform().m11() > 10){
				scale(10/transform().m11(), 10/transform().m22());
			}
		}
	}

	void Canvas::toolSelected(Tool *tool){
		setCurrentTool(tool);
	}

	void Canvas::keyPressEvent(QKeyEvent *e){
		if (e->key() == Qt::Key_Delete || e->key() == Qt::Key_Backspace){
			auto itemList = scene()->selectedItems();
			for (auto i = itemList.begin(); i != itemList.end(); i++){
				scene()->removeItem(*i);
				delete *i;
			}
			e->accept();
		}
		if (!e->isAccepted()) QGraphicsView::keyPressEvent(e);
	}

	void Canvas::setCurrentTool(Tool *tool) {
		_currentTool->disableEvent(this);
		_currentTool = tool;
		_currentTool->enableEvent(this);
	}

	Tool *Canvas::getCurrentTool(){
		return _currentTool;
	}

	void Canvas::mouseMoveEvent(QMouseEvent *e){
		_currentTool->mouseMoveEvent(e, this);
		if (!e->isAccepted()) QGraphicsView::mouseMoveEvent(e);
	}

	void Canvas::mousePressEvent(QMouseEvent *e){
		_currentTool->mousePressEvent(e, this);
		if (!e->isAccepted()) QGraphicsView::mousePressEvent(e);
	}

	void Canvas::mouseDoubleClickEvent(QMouseEvent *e){
		_currentTool->mouseDoubleClickEvent(e, this);
		if (!e->isAccepted()) QGraphicsView::mouseDoubleClickEvent(e);
	}

	void Canvas::mouseReleaseEvent(QMouseEvent *e){
		_currentTool->mouseReleaseEvent(e, this);
		if (!e->isAccepted()) QGraphicsView::mouseReleaseEvent(e);
	}
}
