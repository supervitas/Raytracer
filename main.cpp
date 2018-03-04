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


    auto sphere = std::make_unique<Sphere>(Vec3f(5.0, -1, -15), 2, Vec3f(255, 100, 120), 0.0, 1);
    auto sphere2 = std::make_unique<Sphere>(Vec3f(0.0, 0, -20), 4, Vec3f(230, 180, 60), 0.5, 1);
    auto sphere3 = std::make_unique<Sphere>(Vec3f(5.0,      0, -25), 3, Vec3f(90, 150, 245), 0, 1);
    auto sphere4 = std::make_unique<Sphere>(Vec3f(-5.5f, 0, -15), 3, Vec3f(240, 240, 240), 0, 1);

    auto bigSphere = std::make_unique<Sphere>(Vec3f(0.0, -10004, -20), 10000, Vec3f(100, 100, 100), 0, 0);


    auto light = std::make_unique<Light>(Vec3f(0, 15, 0), 1, Vec3f(255, 255, 255));


    scene->Add(*sphere);
    scene->Add(*sphere2);
    scene->Add(*sphere3);
    scene->Add(*sphere4);
    scene->Add(*bigSphere);

    scene->AddLight(*light);


    std::vector<Vec3f> image;
    image.reserve(gl->frameBufferWidth * gl->frameBufferHeight);

    while (!glfwWindowShouldClose(gl->window)) {
        raytracer->render(image);
        gl->renderToScreen(image);
    }


    return 0;
}