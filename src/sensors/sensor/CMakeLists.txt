cmake_minimum_required(VERSION 3.2)

# Version du langage
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Export command for clangd
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)


add_library(Sensor SHARED 
    src/sensor.cpp
    src/sensorCapture.cpp
    src/sensor.h
)

target_include_directories(Sensor PUBLIC
    $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/src>
)

# Liaison avec la bibliothèque
target_link_libraries(Sensor PUBLIC 
  Configuration
  Logger
)

