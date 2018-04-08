//
// Created by Виталий on 04.04.2018.
//

#ifndef RAYTRACER_PLANE_H
#define RAYTRACER_PLANE_H


#include "Renderable.h"
#include "../Math/Vec3.h"

class Plane : public Renderable {
public:
    Vec3f center;
    Vec3f normal;

    Plane(const Vec3f &center, const Vec3f &normal, Vec3f diffuse) :
            center(center), normal(normal) {
        this->center = center;
        this->normal = normal;
        diffuseColor = diffuse;
    }


    bool intersect(const Vec3f &orig, const Vec3f &dir, float &tNear, float &tFar) const override {
        auto denominator = this->normal.dot(dir);

        if (denominator > 1e-6) {
            float t = (center - orig).dot(normal);
            if (t >= 0) {
                tFar = t;
                return true;
            }

        }

        return  false;
    }
};

#endif //RAYTRACER_PLANE_H
