cmake_minimum_required(VERSION 3.14)
project(chihaya)

set(CMAKE_CXX_STANDARD 17)

# glog
add_subdirectory(external/glog)
include_directories(external/glog/src)

file(GLOB coreSrc
        src/core/*.cc)

set(CHIHAYA_LIBS
        glog)

add_executable(chihaya src/main.cpp
        ${coreSrc})

target_link_libraries(chihaya ${CHIHAYA_LIBS})