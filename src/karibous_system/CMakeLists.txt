cmake_minimum_required(VERSION 3.2)

# Version du langage
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Export command for clangd
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

add_library(KaribousBrainSystem SHARED src/KSystem.cpp)

target_include_directories(KaribousBrainSystem PUBLIC
    $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/src>
)

# Liaison avec la bibliothèque
target_link_libraries(KaribousBrainSystem
  Logger
  Configuration
  Lidar
  Camera
)

