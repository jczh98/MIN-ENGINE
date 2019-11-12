cmake_minimum_required(VERSION 3.14)

project(min CXX)

set(CMAKE_CXX_STANDARD 17)

list(APPEND CMAKE_MODULE_PATH "${CMAKE_CURRENT_SOURCE_DIR}/cmake")

find_package(OpenGL REQUIRED)

include(cmake/cmake-glfw)

add_subdirectory(external/glad)
add_subdirectory(external/fmt)
add_subdirectory(external/nf)

file(GLOB IMGUI_SRC
        src/imgui/*.cpp
        src/imgui/*.h
        external/imgui/*.cpp
        external/imgui/*.h
        )

file(GLOB ENGINE_SRC
        src/common.h
        src/log.h
        src/gl_shader.cc
        src/input.cc
        src/events/*
        src/time_step.h
        src/window.cc
        src/gl_context.cc
        src/layer_stack.cc
        src/imgui_layer.cc
        src/application.cc
        src/controller.cc
        src/camera.cc
        src/main.cpp)

file(COPY assets
        DESTINATION ${CMAKE_CURRENT_BINARY_DIR}/bin)

add_executable(${PROJECT_NAME} ${ENGINE_SRC} ${IMGUI_SRC})

set_target_properties(${PROJECT_NAME} PROPERTIES RUNTIME_OUTPUT_DIRECTORY
        "${CMAKE_CURRENT_BINARY_DIR}/bin")

target_include_directories(${PROJECT_NAME} PUBLIC external/imgui)
target_include_directories(${PROJECT_NAME} PUBLIC ${OPENGL_INCLUDE_DIR})

target_link_libraries(${PROJECT_NAME} OpenGL::GL)
target_link_libraries(${PROJECT_NAME} glfw)
target_link_libraries(${PROJECT_NAME} glad)
target_link_libraries(${PROJECT_NAME} ${OPENGL_gl_LIBRARY})
target_link_libraries(${PROJECT_NAME} fmt::fmt)
target_link_libraries(${PROJECT_NAME} nf::math)
