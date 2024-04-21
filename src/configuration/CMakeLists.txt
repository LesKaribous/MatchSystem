cmake_minimum_required(VERSION 3.2)

# Version du langage
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Export command for clangd
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

find_package(yaml-cpp REQUIRED)
find_package(Boost COMPONENTS system filesystem REQUIRED)

# Exemple d'application
add_library(Configuration SHARED
    src/configuration.cpp
)

target_include_directories(Configuration PUBLIC
    $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/src>
)

# Liaison avec la bibliothèque
target_link_libraries(Configuration
  Logger
  yaml-cpp
)

# add_subdirectory(test)
