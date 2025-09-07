add_executable(state SimUDuck.cpp)

target_sources(state PRIVATE
        lib/Duck/Fly/IFlyBehavior.h
        lib/Duck/Fly/FlyNoWay.h
        lib/Duck/Fly/FlyWithWings.h
        lib/Duck/Quack/IQuackBehavior.h
        lib/Duck/Quack/MuteQuack.h
        lib/Duck/Quack/SoundSqueak.h
        lib/Duck/Quack/SoundQuack.h
        lib/Duck/Dance/IDanceBehavior.h
        lib/Duck/Dance/DanceNoWay.h
        lib/Duck/Dance/DanceWaltz.h
        lib/Duck/Dance/DanceMinuet.h
        lib/Duck/MallardDuck.h
        lib/Duck/RedheadDuck.h
        lib/Duck/ModelDuck.h
        lib/Duck/RubberDuck.h
        lib/Duck/DecoyDuck.h
        lib/Duck/Duck.h
        lib/DuckFunctions.h
)

target_include_directories(state PRIVATE lib)


add_executable(state-test test/test.cpp)

target_sources(state-test PRIVATE
        lib/Duck/Fly/IFlyBehavior.h
        lib/Duck/Fly/FlyNoWay.h
        lib/Duck/Fly/FlyWithWings.h
        lib/Duck/Quack/IQuackBehavior.h
        lib/Duck/Quack/MuteQuack.h
        lib/Duck/Quack/SoundSqueak.h
        lib/Duck/Quack/SoundQuack.h
        lib/Duck/Dance/IDanceBehavior.h
        lib/Duck/Dance/DanceNoWay.h
        lib/Duck/Dance/DanceWaltz.h
        lib/Duck/Dance/DanceMinuet.h
        lib/Duck/Duck.h
        lib/DuckFunctions.h
)

target_include_directories(state-test PRIVATE lib test)

target_link_libraries(state-test PRIVATE gtest_main gmock_main)
enable_testing()
add_test(NAME dance-test COMMAND state-test)