# Define the library
add_library(visq image.cpp io.cpp)

target_include_directories(visq PUBLIC "${CMAKE_CURRENT_SOURCE_DIR}" ${CMAKE_CURRENT_LIST_DIR}/../third_party/stb)

