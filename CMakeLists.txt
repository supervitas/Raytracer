cmake_minimum_required(VERSION 3.9)
project(Raytracer)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

find_package(OpenGL REQUIRED)

set(SOURCE_FILES main.cpp GL.cpp GL.h Vec3.h Primitives/Sphere.h Renderer/Raytracer.h)
add_executable(Raytracer ${SOURCE_FILES})

target_link_libraries(Raytracer glfw ${GLFW_LIBRARIES} ${OPENGL_LIBRARY})