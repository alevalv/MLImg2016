cmake_minimum_required(VERSION 3.6)

set(CMAKE_CXX_STANDARD 11)

find_package(OpenCV REQUIRED)

include_directories(${OpenCV_INCLUDE_DIRS})

set(core_SRC
    imagelav.hpp
    imagemaker.cpp
    imagemaker.h
    imgreader.cpp
    imgreader.h
    retinalimage.cpp
    retinalimage.h
    svm.cpp
    util.cpp
    util.h
    vessel_extraction.cpp
        ml/kmeans/KMeans.cpp
    ml/kmeans/KMeans.h
    ml/kmeans/element/Element.cpp
    ml/kmeans/element/Element.h
        main.cpp preprocessor.h preprocessor.cpp featuredetection/Harris.cpp featuredetection/Harris.h)

add_library(core ${core_SRC})
add_executable(exe main.cpp)

target_link_libraries(exe core ${OpenCV_LIBS})