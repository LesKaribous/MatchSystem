cmake_minimum_required(VERSION 3.2)

project(CameraCalibration VERSION 0.0.1) 

# Version du langage
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Export command for clangd
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

# Recherche d'OpenCV
find_package(OpenCV REQUIRED)

# find_package(yaml-cpp REQUIRED)

find_package(Boost COMPONENTS system filesystem REQUIRED)


# # Définir la bibliothèque
# add_library(RecordingCamera SHARED
#     src/RecordingCamera.cpp
# )

# # Ajouter des en-têtes inclus
# target_include_directories(RecordingCamera
#     PUBLIC
#     ${OpenCV_INCLUDE_DIRS}
#     ${catkin_INCLUDE_DIRS}
# )

# target_link_libraries(RecordingCamera PUBLIC 
#     ${OpenCV_LIBS} 
#     yaml-cpp
#     ${Boost_FILESYSTEM_LIBRARY}
#     ${Boost_SYSTEM_LIBRARY}
# )


# Exemple d'application
add_executable(CameraCalibration
    src/main.cpp
)

# Liaison avec la bibliothèque
target_link_libraries(CameraCalibration
  ${OpenCV_LIBS} 
)

