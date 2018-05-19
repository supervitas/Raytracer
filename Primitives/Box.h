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
    Vec3f center;

    Vec3f size;

    Box(const Vec3f &min, const Vec3f &max, Vec3f diffuse) :
            min(min), max(max) {
        diffuseColor = diffuse;
        center = (min + max) * 0.5;
        size.set(max.x - min.x, max.y - min.y, max.z - min.z);
    }

    void getSurfaceData(const Vec3f &hit, Vec3f &normal) const override {
        auto localPoint = hit - center;
        float min = std::numeric_limits<float>::max();

        float distance = std::abs(size.x - std::abs(localPoint.x));

        if (distance < min) {
            min = distance;
            normal.set(localPoint.x > 0 ? 1 : -1, 0, 0);
        }

        distance = std::abs(size.y - std::abs(localPoint.y));

        if (distance < min) {
            min = distance;
            normal.set(0, localPoint.y > 0 ? 1 : -1, 0);
        }

        distance = std::abs(size.z - std::abs(localPoint.z));

        if (distance < min) {
            min = distance;
            normal.set(0, 0, localPoint.z > 0 ? 1 : -1);
        }
    }

    bool intersect(const Vec3f &orig, const Vec3f &dir, float &tNear) const override {

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

        if (tmin > tmax || tmax < 0) {
            return false;
        }

        tNear = tmin;

        return true;
    }
};

#endif //RAYTRACER_BOX_H
