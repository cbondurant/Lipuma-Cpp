add_library(tool
	fractalTool.cpp
	fractalCurveTool.cpp
	selectionTool.cpp
	tool.cpp
	toolManager.cpp
)

target_link_libraries(tool Qt5::Gui Qt5::Widgets drawable)