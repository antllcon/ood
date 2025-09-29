add_executable(statistics main.cpp)

target_sources(statistics PRIVATE
        lib/Observer.h
        lib/WeatherData.h
)

target_include_directories(statistics PRIVATE lib)


add_executable(statistics-test test/test.cpp)

target_sources(statistics-test PRIVATE
        lib/Observer.h
        lib/WeatherData.h
)

target_include_directories(statistics-test PRIVATE lib test)

target_link_libraries(statistics-test PRIVATE gtest_main gmock_main)
enable_testing()
add_test(NAME hz-test COMMAND statistics-test)