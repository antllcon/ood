add_executable(remove main.cpp)

target_sources(remove PRIVATE
        lib/Observer.h
        lib/WeatherData.h
)

target_include_directories(remove PRIVATE lib)


add_executable(remove-test test/test.cpp)

target_sources(remove-test PRIVATE
        lib/Observer.h
        lib/WeatherData.h
)

target_include_directories(remove-test PRIVATE lib test)

target_link_libraries(remove-test PRIVATE gtest_main gmock_main)
enable_testing()
add_test(NAME removes-test COMMAND remove-test)