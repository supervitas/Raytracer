#include "GL.h"

GL::GL(int width, int height) {

    if (!glfwInit()) throw 'Error with creating context';

    this->width = width;
    this->height = height;

    window = glfwCreateWindow(width, height, "Raytracer", nullptr, nullptr);
    if (!window) {
        glfwTerminate();
        throw 'Error with creating window';
    }

    glfwMakeContextCurrent(window);
    glfwGetFramebufferSize(window, &frameBufferWidth, &frameBufferHeight);
}

void GL::renderToScreen(std::shared_ptr<Vec3f> renderTargetPixels) {
    while (!glfwWindowShouldClose(window)) {
        glClear( GL_COLOR_BUFFER_BIT );
        glDrawPixels(frameBufferWidth, frameBufferHeight, GL_RGB, GL_FLOAT, renderTargetPixels.get());

        glfwSwapBuffers(window);
        glfwPollEvents();
    }
    glfwTerminate();
}
