add_executable(tests
        adapter.test.cpp
        color.test.cpp
)
target_link_libraries(tests PRIVATE graphics GTest::gmock_main)

include(GoogleTest)
gtest_discover_tests(tests)