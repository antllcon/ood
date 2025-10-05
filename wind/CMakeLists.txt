add_executable(wind main.cpp)

target_sources(wind PRIVATE
        lib/Displays.h
        lib/Observer.h
        lib/Statistics.h
        lib/WeatherStations.h
        lib/WeatherDataTypes.h
)

target_include_directories(wind PRIVATE lib)


add_executable(wind-test test/test.cpp)

target_sources(wind-test PRIVATE
        lib/Displays.h
        lib/Observer.h
        lib/Statistics.h
        lib/WeatherStations.h
        lib/WeatherDataTypes.h
)

target_include_directories(wind-test PRIVATE lib test)

target_link_libraries(wind-test PRIVATE gtest_main gmock_main)
enable_testing()
add_test(NAME winds-test COMMAND wind-test)