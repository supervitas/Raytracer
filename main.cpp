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

    std::shared_ptr<Sphere> sphere(new Sphere(Vec3f(-5.5f, 0, -25), 3, Vec3f(0, 240, 0), Vec3f(100, 40, 5), 0.7, 0.3));

    std::shared_ptr<Light> light(new Light(Vec3f(-5.5f, 5, 0), 0.78));


    scene->Add(*sphere);
    scene->AddLight(*light);


    auto raytracer = Raytracer(gl->frameBufferWidth, gl->frameBufferHeight, *scene, *camera, *taskManager);

    while (!glfwWindowShouldClose(gl->window)) {
        auto image = raytracer.render();
        gl->renderToScreen(image);
    }

    glfwTerminate();

    return 0;
}
