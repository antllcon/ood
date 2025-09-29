add_executable(priority main.cpp)

target_sources(priority PRIVATE
        lib/Observer.h
        lib/WeatherData.h
)

target_include_directories(priority PRIVATE lib)


add_executable(priority-test test/test.cpp)

target_sources(priority-test PRIVATE
        lib/Observer.h
        lib/WeatherData.h
)

target_include_directories(priority-test PRIVATE lib test)

target_link_libraries(priority-test PRIVATE gtest_main gmock_main)
enable_testing()
add_test(NAME prioritys-test COMMAND priority-test)