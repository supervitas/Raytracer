
#include <vector>
#include "GL.h"
#include "Primitives/Sphere.h"
#include "Renderer/Raytracer.h"


int main() {
    auto gl = new GL();
    auto raytracer = Raytracer(gl->frameBufferWidth, gl->frameBufferHeight);

    std::vector<Sphere> spheres;
    // position, radius, surface color, reflectivity, transparency, emission color
    spheres.emplace_back(Vec3f( 0.0, -10004, -20), 10000, Vec3f(0.20, 0.20, 0.20), 0, 0.0);
    spheres.emplace_back(Vec3f( 0.0, 0, -20),     4, Vec3f(1.00, 0.32, 0.36), 1, 0.5);
    spheres.emplace_back(Vec3f( 5.0, -1, -15),     2, Vec3f(0.90, 0.76, 0.46), 1, 0.0);
    spheres.emplace_back(Vec3f( 5.0, 0, -25),     3, Vec3f(0.65, 0.77, 0.97), 1, 0.0);
    spheres.emplace_back(Vec3f(-5.5f, 0, -15),     3, Vec3f(0.90, 0.90, 0.90), 1, 0.0);
    // light
    spheres.emplace_back(Vec3f( 0.0, 20, -30),     3, Vec3f(0.00, 0.00, 0.00), 0, 0.0, Vec3f(3));

    auto image = raytracer.render(spheres);

    gl->renderToScreen(image);

    return 0;
}
