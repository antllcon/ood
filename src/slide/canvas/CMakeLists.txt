add_library(canvas SvgCanvas.cpp ConsoleCanvas.cpp IDrawable.h)
target_include_directories(canvas PUBLIC .. common)
