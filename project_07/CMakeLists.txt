cmake_minimum_required(VERSION 3.20)

project(Program)

set(CMAKE_CXX_STANDART 14)

set(PROJECT_DIR ${CMAKE_SOURCE_DIR})

set(PROJECT_INCLUDE_DIR ${PROJECT_DIR}/include)

set(PROJECT_SOURCE_DIR ${PROJECT_DIR}/src)

set(PROJECT_SOURCES
    ${PROJECT_SOURCE_DIR}/main.cpp
    ${PROJECT_SOURCE_DIR}/ShaderProgram.cpp
    ${PROJECT_SOURCE_DIR}/glad.c
    )

set(PROJECT_HEADERS
    ${PROJECT_INCLUDE_DIR}/ShaderProgram.hpp
    )

set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} -framework OpenGL -framework IOKit -framework Cocoa")

find_package(glfw3 3.3.4 REQUIRED)
find_package(glm REQUIRED)

include_directories(${PROJECT_INCLUDE_DIR})

add_executable(${PROJECT_NAME} ${PROJECT_SOURCES})

target_link_libraries(${PROJECT_NAME} glfw)