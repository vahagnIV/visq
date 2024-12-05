# Enable testing with Google Test
enable_testing()
find_package(GTest REQUIRED)

# Define the test executable
# add_executable(visq_test image_test.cpp
#         constant_border_extension_test.cpp
#         mirror_border_extension_test.cpp
#         math_test.cpp
#         utils_test.cpp)

SET(ALL_TEST_SOURCE_FILES image_test.cpp
        constant_border_extension_test.cpp
        mirror_border_extension_test.cpp
        math_test.cpp
        utils_test.cpp)

# Specify include directories
# target_include_directories(visq_test PRIVATE "${PROJECT_SOURCE_DIR}/src")

# Link the test executable against the Google Test libraries and visq library
add_executable(visq_test ${ALL_TEST_SOURCE_FILES})
target_link_libraries(visq_test GTest::GTest GTest::Main visq)

enable_testing()


gtest_add_tests(TARGET visq_test
        SOURCES ${ALL_TEST_SOURCE_FILES}
        TEST_SUFFIX Test
        WORKING_DIRECTORY ${CMAKE_SOURCE_DIR})
# Add the tests
add_test(NAME visq_test COMMAND visq_test)

