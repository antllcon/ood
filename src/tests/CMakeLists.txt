add_executable(tests redactor.test.cpp)
target_link_libraries(tests PRIVATE
        paragraph
        image
        GTest::gtest_main)

include(GoogleTest)
gtest_discover_tests(tests)
