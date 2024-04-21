cmake_minimum_required(VERSION 3.2)

add_subdirectory(logger)
add_subdirectory(configuration)
add_subdirectory(sensors)

add_subdirectory(karibous_system)
add_subdirectory(interface)


add_executable(main main.cpp)
target_link_libraries(main PUBLIC KaribousBrainSystem)
