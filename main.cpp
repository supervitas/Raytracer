#include <vector>
#include "GL/GL.h"
#include "Primitives/Sphere.h"
#include "Renderer/Raytracer.h"
#include "Camera/Camera.h"
#include "Scene/Scene.h"
#include "TaskManager/TaskManager.h"
#include "Lights/Light.h"
#include "Primitives/Plane.h"


int main() {
    auto taskManager = std::make_unique<TaskManager>();

    auto gl = std::make_unique<GL>();
    auto scene = std::make_unique<Scene>();
    auto camera = std::make_unique<Camera>(Vec3f(), Vec3f(0, 0, 1), 60);

    auto raytracer = std::make_unique<Raytracer>(gl->frameBufferWidth, gl->frameBufferHeight, *scene, *camera, *taskManager);


    auto sphere = std::make_unique<Sphere>(Vec3f(0, 0, -25), 6, Vec3f(0.7, 0.2, 0.6));
    auto sphere2 = std::make_unique<Sphere>(Vec3f(-2, 0, -25), 6, Vec3f(0.3, 0.5, 0.9));

    auto plane = std::make_unique<Plane>(Vec3f(0, 0, 0), Vec3f(0, -1.f, 0), Vec3f(0.2, 0.2, 0.2));

    auto light = std::make_unique<Light>(Vec3f(-20, 70, 20), 0.5);
    auto light2 = std::make_unique<Light>(Vec3f(30, 50, -12), 1);


    scene->Add(*plane);

    scene->Add(*sphere);
    scene->Add(*sphere2);


    scene->AddLight(*light);
    scene->AddLight(*light2);


    std::vector<Vec3f> image;
    image.reserve(gl->frameBufferWidth * gl->frameBufferHeight);

    while (!glfwWindowShouldClose(gl->window)) {
        raytracer->render(image);
        gl->renderToScreen(image);
    }


    return 0;
}