//
// Created by Виталий on 23.12.2017.
//

#ifndef RAYTRACER_RENDERABLE_H
#define RAYTRACER_RENDERABLE_H

#include "../Math/Vec3.h"


class Renderable {
public:
    float opacity = 1;
    float reflectivity = 1;
    Vec3f color;
    Vec3f center;
    Vec3f emissionColor;
    virtual bool intersects(const Vec3f &rayorig, const Vec3f &raydir, float &t0, float &t1) const = 0;
};


#endif //RAYTRACER_RENDERABLE_H
