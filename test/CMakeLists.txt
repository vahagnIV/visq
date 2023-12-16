# Enable testing with Google Test
enable_testing()
find_package(GTest REQUIRED)

# Define the test executable
add_executable(visq_test image_test.cpp)

# Specify include directories
target_include_directories(visq_test PRIVATE "${PROJECT_SOURCE_DIR}/src")

# Link the test executable against the Google Test libraries and visq library
target_link_libraries(visq_test GTest::GTest GTest::Main visq)

# Add the tests
add_test(NAME visq_test COMMAND visq_test)

