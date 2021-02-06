add_library(drawable
	editPoint.cpp
	fractalLine.cpp
	fractalCurve.cpp
)

target_link_libraries(drawable Qt5::Gui Qt5::Widgets FastNoise)