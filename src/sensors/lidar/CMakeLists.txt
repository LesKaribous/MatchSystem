cmake_minimum_required(VERSION 3.2)

# Version du langage
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Export command for clangd
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

find_package(ydlidar_sdk REQUIRED)

INCLUDE_DIRECTORIES(
  ${YDLIDAR_SDK_INCLUDE_DIRS}
)

link_directories(${YDLIDAR_SDK_LIBRARY_DIRS})

# Exemple d'application
add_library(Lidar SHARED
    src/lidar.cpp
)

target_include_directories(Lidar PUBLIC
    $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/src>
    ${YDLIDAR_SDK_INCLUDE_DIRS}
)

# Liaison avec la bibliothèque
target_link_libraries(Lidar PUBLIC 
  ${YDLIDAR_SDK_LIBRARIES}
  Configuration
  Logger
  Sensor
)

## TEST

add_executable(test_lidar test/test_lidar.cpp)
target_include_directories(test_lidar PUBLIC
    ${YDLIDAR_SDK_INCLUDE_DIRS}
)

# Liaison avec la bibliothèque
target_link_libraries(test_lidar PUBLIC 
  ${YDLIDAR_SDK_LIBRARIES}
)

