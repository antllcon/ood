add_executable(shape-factory main.cpp)

target_sources(shape-factory PRIVATE
    "lib/Common.h"
    "lib/Shape.h"
    "lib/Canvas.h"
    "lib/PictureDraft.h"   
    "lib/Painter.h" 
    "lib/Designer.h" 
    "lib/ShapeFactory.h"
    "lib/IShapeFactory.h"
)

target_include_directories(shape-factory PRIVATE lib)

add_executable(shape-factory-test test/test.cpp)

target_sources(shape-factory-test PRIVATE
        "lib/Common.h"
        "lib/Shape.h"
        "lib/Canvas.h"
        "lib/PictureDraft.h"
        "lib/Painter.h"
        "lib/Designer.h"
        "lib/ShapeFactory.h"
        "lib/IShapeFactory.h"
)

target_include_directories(shape-factory-test PRIVATE lib test)

target_link_libraries(shape-factory-test PRIVATE gtest_main gmock_main)
enable_testing()
add_test(NAME shape-factory-tests COMMAND shape-factory-test)