add_executable(shape main.cpp)

target_sources(shape PRIVATE
        lib/BaseShape.cpp
        lib/BaseShape.h

        lib/Color/Color.cpp
        lib/Color/Color.h
        lib/CommandProcessor.cpp
        lib/CommandProcessor.h
        lib/ICanvas.h
        lib/IShape.h
        lib/Picture.cpp
        lib/Picture.h
        lib/Point.h
        lib/ShapeCreator.h
        lib/SvgCanvas.cpp
        lib/SvgCanvas.h
        lib/Circle.cpp
        lib/Circle.h
        #lib/Rectangle.cpp
        lib/Rectangle.h
        #lib/Triangle.cpp
        lib/Triangle.h
        #lib/Line.cpp
        lib/Line.h
        #lib/TextShape.cpp
        lib/TextShape.h
        lib/ShapeCreator.cpp
        lib/IDrawStrategy.h
)

target_include_directories(shape PRIVATE
        lib
        lib/Color
)

target_include_directories(shape PRIVATE lib)

#add_executable(state-test test/test.cpp)
#
#target_sources(state-test PRIVATE
#        lib/Duck/Fly/IFlyBehavior.h
#        lib/Duck/Fly/FlyNoWay.h
#        lib/Duck/Fly/FlyWithWings.h
#        lib/Duck/Quack/IQuackBehavior.h
#        lib/Duck/Quack/MuteQuack.h
#        lib/Duck/Quack/SoundSqueak.h
#        lib/Duck/Quack/SoundQuack.h
#        lib/Duck/Dance/IDanceBehavior.h
#        lib/Duck/Dance/DanceNoWay.h
#        lib/Duck/Dance/DanceWaltz.h
#        lib/Duck/Dance/DanceMinuet.h
#        lib/Duck/Duck.h
#        lib/DuckFunctions.h
#)
#
#target_include_directories(state-test PRIVATE lib test)
#
#target_link_libraries(state-test PRIVATE gtest_main gmock_main)
#enable_testing()
#add_test(NAME dance-test COMMAND state-test)