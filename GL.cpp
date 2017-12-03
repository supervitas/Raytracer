//
// Created by Виталий on 03.12.2017.
//

#include "GL.h"

GL::GL(int width, int height) {
    if (!glfwInit()) throw 'Error with creating context';

    window = glfwCreateWindow(width, height, "Raytracer", NULL, NULL);

    if (!window) {
        glfwTerminate();
        throw 'Error with creating window';
    }

    /* Make the window's context current */
    glfwMakeContextCurrent(window);
}

void GL::run() {
    glfwMakeContextCurrent(window);

    /* Loop until the user closes the window */
    while (!glfwWindowShouldClose(window)) {
        /* Render here */
        glClear(GL_COLOR_BUFFER_BIT);

        /* Swap front and back buffers */
        glfwSwapBuffers(window);

        /* Poll for and process events */
        glfwPollEvents();
    }

    glfwTerminate();
}
