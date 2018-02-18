#ifndef RAYTRACER_GL_H
#define RAYTRACER_GL_H

#include "GL/glew.h"
#include <GLFW/glfw3.h>
#include "../Math/Vec3.h"


class GL {
private:
    GLuint fullScreenQuad;
    GLuint texture;
    GLuint vao, vbo, ibo;
    GLint textureLocation;
public:
    GL(int width = 640, int height = 480);
    ~GL();
public:
    GLFWwindow *window;
    int frameBufferWidth;
    int frameBufferHeight;
    void renderToScreen(const std::vector<Vec3f> &renderTargetPixels);

private:
    GLuint loadShader(const GLchar *vertexPath, const GLchar *fragmentPath);
    void setUpFullScreenQuad();
};


#endif //RAYTRACER_GL_H
