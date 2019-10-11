cmake_minimum_required(VERSION 3.14)
project(min)

set(CMAKE_CXX_STANDARD 17)

find_package(pugixml CONFIG REQUIRED)
find_package(Eigen3 CONFIG REQUIRED)
find_package(fmt CONFIG REQUIRED)
find_package(OpenGL REQUIRED)
find_package(GLEW REQUIRED)
find_package(glfw3 CONFIG REQUIRED)
find_package(glm CONFIG REQUIRED)

# set up imgui
include_directories(external/imgui)
file(GLOB imguiSrc
        external/imgui/*.h
        external/imgui/*.cpp)

# set up min
include_directories(include)
include_directories(include/min)
FILE(GLOB MIN_SRC
        include/min/common/*.h
        include/min/opengl/*.h
        include/min/math/*.h
        include/min/min.h
        )

add_library(min STATIC ${MIN_SRC})
set_property(TARGET min PROPERTY CXX_STANDARD 17)
set(MIN_INCLUDE_DIRS include CACHE STRING "include directories for min")

target_link_directories(min PRIVATE ${MIN_INCLUDE_DIRS})

target_link_libraries(min
        PRIVATE pugixml
        PRIVATE Eigen3::Eigen
        PRIVATE fmt::fmt fmt::fmt-header-only
        )

# set up gui
FILE(GLOB MIN_GUI_SRC
        app/gui/src/gui.cc
        app/gui/src/gui.h)


add_executable(min_gui app/gui/src/main.cc
        ${MIN_GUI_SRC}
        ${imguiSrc})

target_link_libraries(min_gui
        PRIVATE OpenGL::GL
        PRIVATE GLEW::GLEW
        PRIVATE glfw
        )

# test
add_executable(test_linalg tests/test_linalg.cc)
target_link_libraries(test_linalg
        PRIVATE Eigen3::Eigen
        PRIVATE glm
        )