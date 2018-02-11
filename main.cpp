#include <vector>
#include "GL/GL.h"
#include "Primitives/Sphere.h"
#include "Renderer/Raytracer.h"
#include "Camera/Camera.h"
#include "Scene/Scene.h"
#include "TaskManager/TaskManager.h"
#include "Lights/Light.h"


int main() {
    std::shared_ptr<GL> gl(new GL);
    std::shared_ptr<Scene> scene(new Scene);
    std::shared_ptr<Camera> camera(new Camera(Vec3f(), Vec3f(0, 0, 1), 60));

    std::shared_ptr<TaskManager> taskManager(new TaskManager);

    std::shared_ptr<Sphere> sphere(new Sphere(Vec3f(-5.5f, 0, -25), 3, Vec3f(0, 240, 0), 0.7, 0.3));
    std::shared_ptr<Sphere> sphere2(new Sphere(Vec3f(2.5f, 0, -25), 3, Vec3f(100, 240, 0), 0.3, 0.9));
    std::shared_ptr<Sphere> sphere3(new Sphere(Vec3f(0, 20, -25), 15, Vec3f(10, 120, 150), 0.3, 0.9));

    std::shared_ptr<Light> light(new Light(Vec3f(0, 20, -30), 0.78, Vec3f(255, 255, 255)));


    scene->Add(*sphere);
    scene->Add(*sphere2);
    scene->Add(*sphere3);

    scene->AddLight(*light);


    auto raytracer = Raytracer(gl->frameBufferWidth, gl->frameBufferHeight, *scene, *camera, *taskManager);

    while (!glfwWindowShouldClose(gl->window)) {
        auto image = raytracer.render();
        gl->renderToScreen(image);
    }

    glfwTerminate();

    return 0;
}
