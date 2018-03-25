#include <vector>
#include "GL/GL.h"
#include "Primitives/Sphere.h"
#include "Renderer/Raytracer.h"
#include "Camera/Camera.h"
#include "Scene/Scene.h"
#include "TaskManager/TaskManager.h"
#include "Lights/Light.h"
#include "Primitives/MeshTriangle.h"


int main() {
    auto taskManager = std::make_unique<TaskManager>();

    auto gl = std::make_unique<GL>();
    auto scene = std::make_unique<Scene>();
    auto camera = std::make_unique<Camera>(Vec3f(), Vec3f(0, 0, 1), 60);

    auto raytracer = std::make_unique<Raytracer>(gl->frameBufferWidth, gl->frameBufferHeight, *scene, *camera, *taskManager);


    Sphere *sph1 = new Sphere(Vec3f(-1, 0, -12), 2);
    sph1->materialType = DIFFUSE_AND_GLOSSY;
    sph1->diffuseColor = Vec3f(0.6, 0.7, 0.8);
    Sphere *sph2 = new Sphere(Vec3f(0.5, -0.5, -8), 1.5);
    sph2->ior = 1.5;
    sph2->materialType = REFLECTION_AND_REFRACTION;

    auto sphere = std::unique_ptr<Sphere>(sph1);
    auto sphere2 = std::unique_ptr<Sphere>(sph2);


    Vec3f verts[4] = {{-5,-3,-6}, {5,-3,-6}, {5,-3,-16}, {-5,-3,-16}};
    uint32_t vertIndex[6] = {0, 1, 3, 1, 2, 3};
    Vec2f st[4] = {{0, 0}, {1, 0}, {1, 1}, {0, 1}};
    auto mesh = new MeshTriangle(verts, vertIndex, 2, st);
    mesh->materialType = DIFFUSE_AND_GLOSSY;

    auto plane = std::unique_ptr<MeshTriangle>(mesh);
    scene->Add(*plane);


    auto light = std::make_unique<Light>(Vec3f(-20, 70, 20), 0.5);
    auto light2 = std::make_unique<Light>(Vec3f(30, 50, -12), 1);


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