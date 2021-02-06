add_library(widget
	toolSelector.cpp
	canvas.cpp
)

target_link_libraries(widget Qt5::Gui Qt5::Widgets)