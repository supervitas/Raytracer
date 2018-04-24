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


    auto sphere = std::make_unique<Sphere>(Vec3f(0, 5, -25), 6, Vec3f(0.7, 0.2, 0.6));
    auto sphere2 = std::make_unique<Sphere>(Vec3f(-2, 5, -25.2f), 6, Vec3f(0.3, 0.5, 0.9));
    auto box = std::make_unique<Box>(Vec3f(1, 0, -5), Vec3f(-1, 2, -10), Vec3f(0.31, 0.21, 0.15));



    auto plane = std::make_unique<Box>(Vec3f(8, -3, 0), Vec3f(-8, -2, -25), Vec3f(0.5, 0.7, 0.9));

    auto light = std::make_unique<Light>(Vec3f(0, 50, -50), 0.9);
    auto light2 = std::make_unique<Light>(Vec3f(0, 10, 0), 1);

//    auto pla = std::make_unique<Sphere>(Vec3f(0, -10, -25), 10, Vec3f(0.7, 0.2, 0.6));
//    scene->Add(*pla);


    scene->Add(*plane);

//    scene->Add(*sphere);
//    scene->Add(*sphere2);
    scene->Add(*box);


//    scene->AddLight(*light);
    scene->AddLight(*light2);


    std::vector<Vec3f> image;
    image.reserve(gl->frameBufferWidth * gl->frameBufferHeight);

    while (!glfwWindowShouldClose(gl->window)) {
        raytracer->render(image);
        gl->renderToScreen(image);
    }


    return 0;
}