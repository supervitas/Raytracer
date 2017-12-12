//
// Created by Виталий on 10.12.2017.
//

#ifndef RAYTRACER_RAYTRACER_H
#define RAYTRACER_RAYTRACER_H

#include <algorithm>
#include <fstream>
#include <vector>
#include "../Vec3.h"
#include "../Primitives/Sphere.h"

#define MAX_RAY_DEPTH 5

class Raytracer {
private:
    int frameBufferWidth;
    int frameBufferHeight;
    Vec3f trace(const Vec3f &rayorig, const Vec3f &raydir, const std::vector<Sphere> &spheres, const int &depth);
    float mix(const float &a, const float &b, const float &mix);

public:
    Raytracer(int frameBufferWidth, int frameBufferHeight);
    std::shared_ptr<Vec3f> render(const std::vector<Sphere> &spheres);
};


#endif //RAYTRACER_RAYTRACER_H
