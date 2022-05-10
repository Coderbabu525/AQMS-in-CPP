# Minimum version of CMake required to build this project
cmake_minimum_required(VERSION 3.5)

# Name of the project
project(aqms VERSION 1.0.0 DESCRIPTION "C++ Project of Air Quality Monitoring System")

# Add all the source files needed to build the executable
add_executable(aqmsb src/AQMS.cpp src/AirQualitySensor.cpp src/PollutantsLevelObserver.cpp src/SpotAirPollutionInformer.cpp src/CityAirPollutionInformer.cpp)

target_compile_features(aqmsb PRIVATE cxx_std_20)

include_directories(include/)