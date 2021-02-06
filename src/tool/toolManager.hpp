#ifndef TOOL_TOOL_MANAGER_HPP
#define TOOL_TOOL_MANAGER_HPP

#include "tool/fractalTool.hpp"
#include "tool/selectionTool.hpp"
#include "tool/fractalCurveTool.hpp"

namespace Lipuma {
	// The tool manager is a purely static class
	// All methods allow access to singleton tool objects.
	class ToolManager{
	public:
		static FractalTool* getFractalTool();
		static FractalCurveTool* getFractalCurveTool();
		static SelectionTool* getSelectionTool();
	private:
		static FractalTool* _FractalTool;
		static SelectionTool* _SelectionTool;
		static FractalCurveTool* _FractalCurveTool;
	};
}
#endif
