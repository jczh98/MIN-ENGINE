cmake_minimum_required(VERSION 3.14)

project(min CXX)

set(ENGINE_NAME min-engine)
set(TRACER_NAME min-tracer)

option(ASSIMP_BUILD_ASSIMP_TOOLS OFF)
option(ASSIMP_BUILD_SAMPLES OFF)
option(ASSIMP_BUILD_TESTS OFF)
set(ASSIMP_BUILD_ALL_IMPORTERS_BY_DEFAULT OFF)
set(ASSIMP_BUILD_ALL_EXPORTERS_BY_DEFAULT OFF)
set(ASSIMP_BUILD_OBJ_IMPORTER ON)
set(ASSIMP_BUILD_STL_IMPORTER ON)
set(ASSIMP_BUILD_PLY_IMPORTER ON)
set(ASSIMP_BUILD_OBJ_EXPORTER ON)

set(CMAKE_CXX_STANDARD 17)

if(MSVC)
    set(CMAKE_CXX_FLAGS  "${CMAKE_CXX_FLAGS} /std:c++17 ")
    add_definitions(-D_SILENCE_CXX17_OLD_ALLOCATOR_MEMBERS_DEPRECATION_WARNING)
    add_definitions(-D_SILENCE_CXX17_CODECVT_HEADER_DEPRECATION_WARNING)
endif()

list(APPEND CMAKE_MODULE_PATH "${CMAKE_CURRENT_SOURCE_DIR}/cmake")

find_package(OpenGL REQUIRED)

include(cmake/cmake-glfw)

add_subdirectory(external/glad)
add_subdirectory(external/assimp)
add_subdirectory(external/fmt)
add_subdirectory(external/nf)

file(GLOB IMGUI_SRC
        src/imgui/*.cpp
        src/imgui/*.h
        external/imgui/*.cpp
        external/imgui/*.h
        )

file(GLOB TRACER_SRC
        src/tracer/core/parallel.cc)

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
        src/renderer.cc
        src/camera.cc
        src/controller.cc
        src/gl_buffer.cc
        src/gl_vertex_array.cc
        src/stb_image.cc
        src/gl_texture.cc
        src/model.cc
        src/example/model_loading.h
        src/example/shadow_map.h
        src/main.cpp)

file(COPY assets
        DESTINATION ${CMAKE_CURRENT_BINARY_DIR}/bin)

add_executable(${ENGINE_NAME} ${ENGINE_SRC} ${IMGUI_SRC})
add_executable(${TRACER_NAME} ${TRACER_SRC})

set_target_properties(${ENGINE_NAME} PROPERTIES RUNTIME_OUTPUT_DIRECTORY
        "${CMAKE_CURRENT_BINARY_DIR}/bin")

target_include_directories(${ENGINE_NAME}
        PUBLIC
        external/imgui
        ${OPENGL_INCLUDE_DIR}
        external/stb
        external/assimp/include
        )

target_link_libraries(${ENGINE_NAME}
        glfw
        glad
        ${OPENGL_gl_LIBRARY}
        OpenGL::GL
        fmt::fmt
        assimp
        nf::math
        )
