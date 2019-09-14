cmake_minimum_required(VERSION 3.14)
project(chihaya)

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
        include/chihaya/*.h
        include/chihaya/math/*.h
        src/core/*.cc
        src/math/*.cc)

set(CHIHAYA_LIBS
        glog
        fmt)


add_executable(chihaya src/main.cpp
        ${coreSrc})

target_link_libraries(chihaya ${CHIHAYA_LIBS})