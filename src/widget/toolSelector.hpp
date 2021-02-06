#ifndef WIDGET_TOOL_SELECTOR_HPP
#define WIDGET_TOOL_SELECTOR_HPP

#include <QWidget>

#include "tool/tool.hpp"

namespace Lipuma {

class ToolSelector : public QWidget{
	Q_OBJECT

	public:
		ToolSelector(QWidget *w = nullptr);

	signals:
		void toolSelected(Tool *tool);
};

}

#endif
