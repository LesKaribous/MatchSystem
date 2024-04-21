cmake_minimum_required(VERSION 3.2)


project(KaribousBrainSystem)


option(BUILD_3RD_PARTY "Build 3rdparty" ON)

if(BUILD_3RD_PARTY)
    add_subdirectory(3rdparty)
endif(BUILD_3RD_PARTY)


add_subdirectory(src)
