add_executable(tests redactor.test.cpp)
target_link_libraries(tests PRIVATE
        console
        document
        documentItem
        export
        image
        paragraph
        resource
        GTest::gmock_main)

include(GoogleTest)
gtest_discover_tests(tests)