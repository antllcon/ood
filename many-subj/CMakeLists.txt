add_executable(many-subj main.cpp)

target_sources(many-subj PRIVATE
        lib/Observer.h
        lib/WeatherData.h
)

target_include_directories(many-subj PRIVATE lib)


add_executable(many-subj-test test/test.cpp)

target_sources(many-subj-test PRIVATE
        lib/Observer.h
        lib/WeatherData.h
)

target_include_directories(many-subj-test PRIVATE lib test)

target_link_libraries(many-subj-test PRIVATE gtest_main gmock_main)
enable_testing()
add_test(NAME many-subj-test COMMAND many-subj-test)