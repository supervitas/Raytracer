cmake_minimum_required(VERSION 3.9)
project(Raytracer)

find_package(OpenGL REQUIRED)


set(SOURCE_FILES main.cpp GL.cpp GL.h)
add_executable(Raytracer ${SOURCE_FILES})

target_link_libraries(Raytracer glfw ${GLFW_LIBRARIES} ${OPENGL_LIBRARY})