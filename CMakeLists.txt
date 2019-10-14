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
#find_package(assimp CONFIG REQUIRED)

add_subdirectory(external/assimp)

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
        include/min/test/*.h
        include/min/math/*.h
        include/min/min.h
        src/opengl/*.cc
        src/math/*.cc
        src/common/stb_image.cc
        )

add_library(min STATIC ${MIN_SRC})
set(MIN_INCLUDE_DIRS include CACHE STRING "include directories for min")

target_link_directories(min PRIVATE ${MIN_INCLUDE_DIRS})

target_link_libraries(min
        PRIVATE pugixml
        PRIVATE Eigen3::Eigen
        PRIVATE fmt::fmt fmt::fmt-header-only
        assimp::assimp
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
add_executable(test_linalg tests/test_linalg.cc
        )
add_executable(test_opengl tests/test_opengl.cc)

add_executable(test_assimp tests/test_assimp.cc)

add_executable(test_opengl_shader tests/test_opengl_textures.cc src/common/stb_image.cc)


target_link_libraries(test_assimp
        assimp::assimp)

target_link_libraries(test_opengl
        min
        GLEW::GLEW
        OpenGL::GL
        glfw
        )

target_link_libraries(test_opengl_shader
        min
        GLEW::GLEW
        OpenGL::GL
        glfw
        )

target_link_libraries(test_linalg
        PRIVATE Eigen3::Eigen
        PRIVATE glm
        PRIVATE min
        )
