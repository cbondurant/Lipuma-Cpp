#ifndef TOOL_SELECTION_TOOL_HPP
#define TOOL_SELECTION_TOOL_HPP

#include <QGraphicsView>

#include "tool/tool.hpp"

namespace Lipuma {
	class SelectionTool : public Tool{
		void mousePressEvent(QMouseEvent *e, QGraphicsView *view) override;
	};
}

#endif
