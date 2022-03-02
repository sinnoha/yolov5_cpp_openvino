cmake_minimum_required(VERSION 3.5)
project(detect_box)
set(CMAKE_CXX_STANDARD 11)

set(LIBRARY_OUTPUT_PATH ${CMAKE_SOURCE_DIR}/lib)
set(EXECUTABLE_OUTPUT_PATH ${CMAKE_SOURCE_DIR}/bin)

include_directories(${CMAKE_SOURCE_DIR}/include)

add_compile_options("-g")

add_subdirectory(src)

add_executable(detect_box main.cpp)

target_link_libraries(detect_box
        ${OpenCV_LIBS}
        Detector_lib
        Utils_lib
)
