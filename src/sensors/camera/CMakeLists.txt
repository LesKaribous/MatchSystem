cmake_minimum_required(VERSION 3.2)

# Version du langage
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Export command for clangd
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

# Recherche d'OpenCV
find_package(OpenCV REQUIRED)

find_package(Ceres REQUIRED)

# find_package(yaml-cpp REQUIRED)

find_package(Boost COMPONENTS system filesystem REQUIRED)


# Exemple d'application
add_library(Camera SHARED
    src/camera.cpp
    src/camera_calib.cpp
)

target_include_directories(Camera PUBLIC
  $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/src>
  ${OpenCV_INCLUDE_DIRS}
)

# Liaison avec la bibliothèque
target_link_libraries(Camera PUBLIC 
  Sensor
  ${OpenCV_LIBS} 
)


# Exemple d'application
add_executable(CameraCalibration
    main.cpp
)

# Liaison avec la bibliothèque
target_link_libraries(CameraCalibration
  ${OpenCV_LIBS} 
  Ceres::ceres
)

