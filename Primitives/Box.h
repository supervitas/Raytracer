//
// Created by Виталий on 08.04.2018.
//

#ifndef RAYTRACER_BOX_H
#define RAYTRACER_BOX_H

#include "Renderable.h"

class Box : public Renderable {
public:
    Vec3f min;
    Vec3f max;

    Box(const Vec3f &min, const Vec3f &max, Vec3f diffuse) :
            min(min), max(max) {
        diffuseColor = diffuse;
    }


    bool intersect(const Vec3f &orig, const Vec3f &dir, float &tNear, float &tFar) const override {
        Vec3f dirfrac = Vec3f();
        dirfrac.x = 1.0f / dir.x;
        dirfrac.y = 1.0f / dir.y;
        dirfrac.z = 1.0f / dir.z;

        float t1 = (min.x - orig.x) * dirfrac.x;
        float t2 = (max.x - orig.x) * dirfrac.x;
        float t3 = (min.y - orig.y) * dirfrac.y;
        float t4 = (max.y - orig.y) * dirfrac.y;
        float t5 = (min.z - orig.z) * dirfrac.z;
        float t6 = (max.z - orig.z) * dirfrac.z;

        float tmin = std::max(std::max(std::min(t1, t2), std::min(t3, t4)), std::min(t5, t6));
        float tmax = std::min(std::min(std::max(t1, t2), std::max(t3, t4)), std::max(t5, t6));

// if tmax < 0, ray (line) is intersecting AABB, but the whole AABB is behind us if tmin > tmax, ray doesn't intersect AABB
        if (tmax < 0 || tmin > tmax) {
            return false;
        }

        tFar = tmin;
        tNear = tmax;

        return true;
    }
};

#endif //RAYTRACER_BOX_H
