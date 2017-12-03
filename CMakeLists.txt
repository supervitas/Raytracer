cmake_minimum_required(VERSION 3.9)
project(Raytracer)

find_package(OpenGL REQUIRED)


set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -O2 -Wall -Wextra -std=c++11")

set(SOURCE_FILES main.cpp)
add_executable(Raytracer ${SOURCE_FILES})

target_link_libraries(Raytracer glfw ${GLFW_LIBRARIES} ${OPENGL_LIBRARY})