cmake_minimum_required(VERSION 3.2)

# Version du langage
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Export command for clangd
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

# QT
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_AUTOUIC ON)

if(CMAKE_VERSION VERSION_LESS "3.7.0")
    set(CMAKE_INCLUDE_CURRENT_DIR ON)
endif()

# find_package(Qt5 REQUIRED COMPONENTS Core Gui Widgets)

# Exemple d'application
add_library(KaribousApp SHARED
    src/interface.cpp
    # src/KaribousApp.ui
)

target_include_directories(KaribousApp PUBLIC
    $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/src>
)

# Liaison avec la bibliothèque
target_link_libraries(KaribousApp
    KaribousBrainSystem
    # Qt5::Core
    # Qt5::Gui
    # Qt5::Widgets
)

