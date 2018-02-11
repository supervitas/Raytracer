#ifndef RAYTRACER_GL_H
#define RAYTRACER_GL_H

#include <GLFW/glfw3.h>
#include "../Math/Vec3.h"


class GL {
private:
    int width;
    int height;
    GLuint fullScreenQuad;

public:
    GLFWwindow *window;
    int frameBufferWidth;
    int frameBufferHeight;
    GL(int width = 640, int height = 480);
    void renderToScreen(std::shared_ptr<Vec3f> result);

private:
    GLuint loadShader(const GLchar *vertexPath, const GLchar *fragmentPath);
};


#endif //RAYTRACER_GL_H
