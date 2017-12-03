//
// Created by Виталий on 03.12.2017.
//

#ifndef RAYTRACER_GL_H
#define RAYTRACER_GL_H

#include <GLFW/glfw3.h>


class GL {
private:
    GLFWwindow *window;

public:
    GL(int width = 640, int height = 480);
    void run();
};


#endif //RAYTRACER_GL_H
