cmake_minimum_required(VERSION 3.6)

set(CMAKE_CXX_STANDARD 11)

find_package(OpenCV REQUIRED)

include_directories(${OpenCV_INCLUDE_DIRS})

set(core_SRC
    ../lib/prettyprint.hpp
    image/imagelav.hpp
    image/imagemaker.cpp
    image/imagemaker.h
    image/imgreader.cpp
    image/imgreader.h
    image/preprocessor.h
    image/preprocessor.cpp
    retina/retinalimage.cpp
    retina/retinalimage.h
    retina/RetinaUtils.cpp
    retina/RetinaUtils.h
    featuredetection/Corner.cpp
    featuredetection/Corner.h
    featuredetection/Feature.cpp
    featuredetection/Feature.h
    ml/kmeans/KMeans.cpp
    ml/kmeans/KMeans.h
    ml/datamaker/DataMaker.cpp
    ml/datamaker/DataMaker.h
    ml/svm/mSVM.cpp
    ml/svm/mSVM.h
    ml/knearest/KNearest.cpp
    ml/knearest/KNearest.h
    util.cpp
    util.h
    main.cpp)

add_library(core ${core_SRC})
add_executable(exe main.cpp)

target_link_libraries(exe core ${OpenCV_LIBS})
