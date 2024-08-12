cmake_minimum_required(VERSION 3.10)
project(CarSpeedEstimator)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

find_package(OpenCV REQUIRED)

include_directories(${OpenCV_INCLUDE_DIRS} include)

add_executable(CarSpeedEstimator main.cpp CarTracker.cpp)

target_link_libraries(CarSpeedEstimator ${OpenCV_LIBS})

