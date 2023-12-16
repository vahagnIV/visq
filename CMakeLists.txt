cmake_minimum_required(VERSION 3.10)

project(VisqProject)

# Specify the C++ standard
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

include_directories(${CMAKE_CURRENT_LIST_DIR} ${CMAKE_CURRENT_LIST_DIR}/include)
# Include the subdirectories
add_subdirectory(src)
add_subdirectory(test)
add_subdirectory(examples)

