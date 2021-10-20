cmake_minimum_required(VERSION 3.20)
project(Anomaly_detection)

set(CMAKE_CXX_STANDARD 14)

include_directories(.)

add_executable(Anomaly_detection
        anomaly_detection_util.cpp
        anomaly_detection_util.h
        main.cpp)
