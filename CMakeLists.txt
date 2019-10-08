cmake_minimum_required(VERSION 3.14)
project(min)

set(CMAKE_CXX_STANDARD 17)


# tbb
include(external/tbb/cmake/TBBBuild.cmake)
tbb_build(TBB_ROOT ${CMAKE_CURRENT_SOURCE_DIR}/external/tbb CONFIG_DIR TBB_DIR MAKE_ARGS tbb_cpf=1)
find_package(TBB REQUIRED tbb_preview)


add_subdirectory(external/fmt)
add_subdirectory(external/pugixml)
include_directories(external/stb)
include_directories(external/fmt)
include_directories(external/eigen)
include_directories(external/pugixml/src)

include_directories(include)
file(GLOB coreSrc
        include/min/*.h
        include/min/core/*.h
        include/min/math/*.h
        include/min/common/*.h
        src/core/*.cc
        src/math/*.cc)

set(MIN_LIBS
        fmt
        ${TBB_IMPORTED_TARGETS}
        pugixml)


add_executable(min src/main.cpp
        ${coreSrc})

target_link_libraries(min
        ${MIN_LIBS})
