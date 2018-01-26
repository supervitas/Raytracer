//
// Created by Виталий on 23.12.2017.
//

#ifndef RAYTRACER_RENDERABLE_H
#define RAYTRACER_RENDERABLE_H

#include "../Math/Vec3.h"


class Renderable {
public:
    Vec3f color;
    float opacity = 1;
    Vec3f center;
    virtual bool intersects(const Vec3f &rayorig, const Vec3f &raydir, float &t0, float &t1) const = 0;
};


#endif //RAYTRACER_RENDERABLE_H
