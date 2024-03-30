cmake_minimum_required(VERSION 3.2)

# Version du langage
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Export command for clangd
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

find_package(ydlidar_sdk REQUIRED)

find_package(Boost COMPONENTS system filesystem REQUIRED)

INCLUDE_DIRECTORIES(
  ${YDLIDAR_SDK_INCLUDE_DIRS}
)

link_directories(${YDLIDAR_SDK_LIBRARY_DIRS})

# Exemple d'application
add_library(Lidar SHARED
    lidar.cpp
)

# Liaison avec la bibliothèque
target_link_libraries(Lidar
  ${OpenCV_LIBS} 
  ${YDLIDAR_SDK_LIBRARIES}
)

