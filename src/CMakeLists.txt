cmake_minimum_required(VERSION 3.5)
project(src_lib)
set(CMAKE_CXX_STANDARD 11)

set(LIBRARY_OUTPUT_PATH ${CMAKE_SOURCE_DIR}/lib)
set(EXECUTABLE_OUTPUT_PATH ${CMAKE_SOURCE_DIR}/bin)

add_compile_options("-g")

#查找必要的依赖包
find_package(OpenCV REQUIRED)
find_package(InferenceEngine)
find_package(ngraph REQUIRED)
find_package(Boost REQUIRED COMPONENTS system filesystem)

include_directories(${Boost_INCLUDE_DIRS})
include_directories(${CMAKE_SOURCE_DIR}/include)
    
MESSAGE( STATUS "Boost_INCLUDE_DIRS = ${Boost_INCLUDE_DIRS}.")
MESSAGE( STATUS "Boost_LIBRARIES = ${Boost_LIBRARIES}.")
MESSAGE( STATUS "Boost_LIB_VERSION = ${Boost_LIB_VERSION}.")

# 编译 static lib.a
add_library (Utils_lib Utils.cpp)
add_library (Detector_lib Detector.cpp)


target_link_libraries(Utils_lib
        ${OpenCV_LIBS}
        ${Boost_LIBRARIES}
)

target_link_libraries(Detector_lib
        ${OpenCV_LIBS}
        ${InferenceEngine_LIBRARIES}
        ${ngraph_LIBRARIES}
)