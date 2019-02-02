#include <vector>
#include "GL/GL.h"
#include "Primitives/Sphere.h"
#include "Renderer/Raytracer.h"
#include "Camera/Camera.h"
#include "Scene/Scene.h"
#include "TaskManager/TaskManager.h"
#include "Lights/Light.h"
#include "Primitives/Box.h"

int main() {
    auto taskManager = std::make_unique<TaskManager>();

    auto gl = std::make_unique<GL>();
    auto scene = std::make_unique<Scene>();
    auto camera = std::make_unique<Camera>(Vec3f(), Vec3f(0, 0, 1), 60);

    auto raytracer = std::make_unique<Raytracer>(gl->frameBufferWidth, gl->frameBufferHeight, *scene, *camera, *taskManager);

    auto sphere = std::make_unique<Sphere>(Vec3f(2, 3, -13), 3, Vec3f(0.7, 0.2, 0.6));
    auto sphere2 = std::make_unique<Sphere>(Vec3f(-1, 0, -8.2f), 1, Vec3f(0.3, 0.5, 0.9), 0.9, 0.9);
    sphere2->ior = 1.5;
    auto sphere3 = std::make_unique<Sphere>(Vec3f(1, 2, -7.2f), 1, Vec3f(0.1, 0.8, 0.4), 0.1, 0.9);
    sphere3->ior = 1.8;



    auto plane = std::make_unique<Box>(Vec3f(8, -3, 0), Vec3f(-8, -2, -25), Vec3f(0.3, 0.1, 0.4));

    auto light = std::make_unique<Light>(Vec3f(-20, 70, 20), 0.5);
    auto light2 = std::make_unique<Light>(Vec3f(0, 50, -13), 1);


    scene->Add(std::move(plane));

    scene->Add(std::move(sphere));
    scene->Add(std::move(sphere2));
    scene->Add(std::move(sphere3));


    scene->AddLight(std::move(light));
    scene->AddLight(std::move(light2));


    std::vector<Vec3f> image;
    image.reserve(static_cast<u_int32_t>(gl->frameBufferWidth * gl->frameBufferHeight));

    while (!glfwWindowShouldClose(gl->window)) {
        raytracer->render(image);
        gl->renderToScreen(image);
    }


    return 0;
}