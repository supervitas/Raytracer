#include <vector>
#include "GL.h"
#include "Primitives/Sphere.h"
#include "Renderer/Raytracer.h"
#include "Camera/Camera.h"


int main() {
    auto gl = new GL();
    auto camera = new Camera(*new Vec3f(), *new Vec3f, 60);

    auto sphere = new Sphere(*new Vec3f(0, 0, 5), 10, *new Vec3i(255, 255, 255));

//    auto raytracer = Raytracer(gl->frameBufferWidth, gl->frameBufferHeight);

    return 0;
}
