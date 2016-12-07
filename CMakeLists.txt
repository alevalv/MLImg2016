cmake_minimum_required(VERSION 3.6)
project(MacLea)

set(CMAKE_CXX_STANDARD 11)

find_package(OpenCV REQUIRED)

set(SOURCE_FILES
    src/imagelav.hpp
    src/imagemaker.cpp
    src/imagemaker.h
    src/imgreader.cpp
    src/imgreader.h
    src/retinalimage.cpp
    src/retinalimage.h
    src/svm.cpp
    src/util.cpp
    src/util.h
    src/vessel_extraction.cpp)

add_executable(MacLea ${SOURCE_FILES})

target_link_libraries( MacLea ${OpenCV_LIBS}$)