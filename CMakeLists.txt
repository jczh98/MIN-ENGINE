cmake_minimum_required(VERSION 3.14)
project(min)

set(CMAKE_CXX_STANDARD 17)


# glog
add_subdirectory(external/glog)
add_subdirectory(external/fmt)
include_directories(external/stb)
include_directories(external/glog/src)
include_directories(external/fmt)
include_directories(external/eigen)

include_directories(include)

file(GLOB coreSrc
        include/min/*.h
        include/min/core/*.h
        include/min/math/*.h
        include/min/common/*.h
        src/core/*.cc
        src/math/*.cc)

set(MIN_LIBS
        glog
        fmt)


add_executable(min src/main.cpp
        ${coreSrc})

target_link_libraries(min ${MIN_LIBS})
