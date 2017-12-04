//
// Created by Виталий on 03.12.2017.
//

#include "GL.h"
#include <cstdlib>
#include <iostream>
#include <array>

GL::GL(int width, int height) {

    if (!glfwInit()) throw 'Error with creating context';

    this->width = width;
    this->height = height;

    window = glfwCreateWindow(width, height, "Raytracer", nullptr, nullptr);


    if (!window) {
        glfwTerminate();
        throw 'Error with creating window';
    }
}

void GL::run() {
    struct RGBType {
        float r;
        float g;
        float b;
    };

    glfwMakeContextCurrent(window);

    int frameBufferWidth, frameBufferHeight;
    glfwGetFramebufferSize(window, &frameBufferWidth, &frameBufferHeight);

    std::unique_ptr<RGBType[]> pixels(new RGBType[frameBufferWidth * frameBufferHeight]);

    for (int i = 0; i < frameBufferWidth * frameBufferHeight; i++) {
        pixels[i].r = 1;
        pixels[i].g = 1;
        pixels[i].b = 1;
    }


    while (!glfwWindowShouldClose(window)) {
        glDrawPixels(frameBufferWidth, frameBufferHeight, GL_RGB, GL_FLOAT, pixels.get());
        glClear( GL_COLOR_BUFFER_BIT );


        glfwSwapBuffers(window);
        glfwPollEvents();
    }
    glfwTerminate();
}
