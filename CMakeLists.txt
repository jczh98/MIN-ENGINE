cmake_minimum_required(VERSION 3.14)

project(min)

set(CMAKE_CXX_STANDARD 17)

list(APPEND CMAKE_MODULE_PATH "${CMAKE_CURRENT_SOURCE_DIR}/cmake")

find_package(OpenGL REQUIRED)

include(cmake/cmake-glfw)

add_subdirectory(external/glad)

file(GLOB IMGUI_SRC
        src/imgui/*.cpp
        src/imgui/*.h
        external/imgui/*.cpp
        external/imgui/*.h
        )

add_executable(${PROJECT_NAME} src/main.cpp ${IMGUI_SRC})

target_include_directories(${PROJECT_NAME} PUBLIC external/imgui)
target_include_directories(${PROJECT_NAME} PUBLIC external/eigen3)
target_include_directories(${PROJECT_NAME} PUBLIC ${OPENGL_INCLUDE_DIR})

target_link_libraries(${PROJECT_NAME} OpenGL::GL)
target_link_libraries(${PROJECT_NAME} glfw)
target_link_libraries(${PROJECT_NAME} glad)
target_link_libraries(${PROJECT_NAME} ${OPENGL_gl_LIBRARY})