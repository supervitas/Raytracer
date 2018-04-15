//
// Created by Виталий on 10.12.2017.
//

#ifndef RAYTRACER_SPHERE_H
#define RAYTRACER_SPHERE_H


#include "../Math/Vec3.h"
#include "Renderable.h"

class Sphere : public Renderable {
public:
    Vec3f center;
    float diametr;
    float radius;

    Sphere(const Vec3f &center, const float &radius, Vec3f diffuse) :
            center(center), radius(radius), diametr(radius * radius) {
        diffuseColor = diffuse;
    }

    void getSurfaceData(const Vec3f &hit, Vec3f &normal) const override {
        normal = (hit - center).normalize();
    }

    bool intersect(const Vec3f &orig, const Vec3f &dir, float &tNear, float &tFar) const override {
        Vec3f L = orig - center;
        float a = dir.dot(dir);
        float b = 2 * dir.dot(L);
        float c = L.dot(L) - diametr;

        float discriminant = b * b - 4 * a * c;

        if (discriminant < 0) return false;

        if (discriminant == 0)  {
            tNear = tFar = static_cast<float>(-0.5 * b / a);
        } else {
            float q = (b > 0) ?
                      -0.5 * (b + sqrt(discriminant)) :
                      -0.5 * (b - sqrt(discriminant));
            tNear = q / a;
            tFar = c / q;
        }

        return true;
    }
};


#endif //RAYTRACER_SPHERE_H
