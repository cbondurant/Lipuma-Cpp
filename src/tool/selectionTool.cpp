#include "tool/selectionTool.hpp"

#include "widget/canvas.hpp"

namespace Lipuma {
	void SelectionTool::mousePressEvent(QMouseEvent *e, QGraphicsView */* view */){
		e->ignore();
	}
}
