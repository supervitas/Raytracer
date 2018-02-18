#include <vector>
#include "GL/GL.h"
#include "Primitives/Sphere.h"
#include "Renderer/Raytracer.h"
#include "Camera/Camera.h"
#include "Scene/Scene.h"
#include "TaskManager/TaskManager.h"
#include "Lights/Light.h"


int main() {
    auto taskManager = std::make_unique<TaskManager>();

    auto gl = std::make_unique<GL>();
    auto scene = std::make_unique<Scene>();
    auto camera = std::make_unique<Camera>(Vec3f(), Vec3f(0, 0, 1), 60);

    auto raytracer = std::make_unique<Raytracer>(gl->frameBufferWidth, gl->frameBufferHeight, *scene, *camera, *taskManager);

    auto sphere = std::make_unique<Sphere>(Vec3f(-5.5f, 0, -25), 3, Vec3f(0, 240, 0), 0.7, 0.3);
    auto sphere2 = std::make_unique<Sphere>(Vec3f(2.5f, 0, -25), 3, Vec3f(100, 240, 0), 0.3, 0.9);
    auto sphere3 = std::make_unique<Sphere>(Vec3f(0, 20, -25), 15, Vec3f(10, 120, 150), 0.3, 0.9);

    auto light = std::make_unique<Light>(Vec3f(0, 15, -30), 0.78, Vec3f(255, 255, 255));


    scene->Add(*sphere);
    scene->Add(*sphere2);
    scene->Add(*sphere3);

    scene->AddLight(*light);


    std::vector<Vec3f> image;
    image.reserve(gl->frameBufferWidth * gl->frameBufferHeight);

    while (!glfwWindowShouldClose(gl->window)) {
        raytracer->render(image);
        gl->renderToScreen(image);
    }

    return 0;
}