# Define the library

set(TRANSFORM_SOURCES 
        transform/filters/gaussian_filter.cpp
        transform/filters/gradient.cpp
        transform/fft.cpp
        utils/midpoint_circle.cpp
        utils/draw_keypoints.cpp)

add_library(visq 
     image.cpp io.cpp
     ${TRANSFORM_SOURCES}
)

target_include_directories(visq PUBLIC
        "${CMAKE_CURRENT_SOURCE_DIR}"
        ${CMAKE_CURRENT_LIST_DIR}/../third_party/stb)

