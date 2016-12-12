cmake_minimum_required(VERSION 3.6)

set(CMAKE_CXX_STANDARD 11)
set(REPO ~/Maestria/MacLea/SourceCode)

project(Test)

project(Example)

include(CTest)
enable_testing()

include(${REPO}/DownloadProject/DownloadProject.cmake)
download_project(
	PROJ			googletest
	GIT_REPOSITORY		https://github.com/google/googletest.git
	GIT_TAG			master
	UPDATE_DISCONNECTED	1
)

add_subdirectory(${googletest_SOURCE_DIR} ${googletest_BINARY_DIR} EXCLUDE_FROM_ALL)

find_package(OpenCV REQUIRED)

include_directories(${OpenCV_INCLUDE_DIRS})

set(test_SRC
    ElementTest.cpp
    KMeansTest.cpp)
add_executable(runUnitTests gtest.cpp ${test_SRC})
target_link_libraries(runUnitTests gtest gmock core ${OpenCV_LIBS})
#add_test(runUnitTests runUnitTests)
