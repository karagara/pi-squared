cmake_minimum_required(VERSION 2.8 FATAL_ERROR)
project("Pi2 Robot Controller")

set(raspicam_DIR /usr/local/lib/cmake)
set(CMAKE_CXX_FLAGS "-I/usr/local/include -L/usr/local/lib -lwiringPi -lraspicam -lraspicam_cv")

include_directories(${CMAKE_CURRENT_SOURCE_DIR})

find_package(OpenCV REQUIRED)
find_package(raspicam CONFIG REQUIRED)
add_subdirectory(pi2core)

add_executable(testExec main.cc)
target_link_libraries(testExec pi2core ${OpenCV_LIBS} ${raspicam_LIBS})
