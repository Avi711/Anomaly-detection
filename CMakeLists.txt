cmake_minimum_required(VERSION 3.20)
project(Anomaly_detection)

set(CMAKE_CXX_STANDARD 11)

include_directories(.)

set(Headers anomaly_detection_util.h AnomalyDetector.h SimpleAnomalyDetector.h timeseries.h)
SET(CMAKE_CXX_FLAGS -pthread)
add_executable(Anomaly_detection
        anomaly_detection_util.cpp
        anomaly_detection_util.h
        MainTrain.cpp "AnomalyDetector.cpp" "AnomalyDetector.h" SimpleAnomalyDetector.cpp SimpleAnomalyDetector.h timeseries.cpp timeseries.h minCircle.cpp minCircle.h HybridAnomalyDetector.cpp HybridAnomalyDetector.h commands.h CLI.cpp CLI.h Server.cpp Server.h)
