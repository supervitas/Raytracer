#include <vector>
#include "GL.h"
#include "Primitives/Sphere.h"
#include "Renderer/Raytracer.h"
#include "Camera/Camera.h"
#include "Scene/Scene.h"


int main() {
    std::shared_ptr<GL> gl(new GL);
    std::shared_ptr<Scene> scene(new Scene);
    std::shared_ptr<Camera> camera(new Camera(Vec3f(), Vec3f(), 60));


    std::shared_ptr<Sphere> sphere(new Sphere(Vec3f(0, 0, 5), 10, Vec3i(140, 140, 200)));


    scene->Add(*sphere);


    auto raytracer = Raytracer(gl->frameBufferWidth, gl->frameBufferHeight, *scene, *camera);

    return 0;
}
