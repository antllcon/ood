add_library(canvas Canvas.cpp SvgCanvas.cpp ConsoleCanvas.cpp)
target_include_directories(canvas PUBLIC .. common)