add_executable(shape-factory main.cpp)

target_sources(shape-factory PRIVATE
    "lib/Common.h"
    "lib/Shape.h"
    "lib/Canvas.h"
    "lib/PictureDraft.h"   
    "lib/Painter.h" 
    "lib/Designer.h" 
    "lib/ShapeFactory.h")

target_include_directories(shape-factory PRIVATE lib)