add_executable(tests composite.test.cpp)
target_link_libraries(tests PRIVATE shapes GTest::gmock_main shapes)

include(GoogleTest)
gtest_discover_tests(tests)