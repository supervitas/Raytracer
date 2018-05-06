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

    Sphere(const Vec3f &center, const float &radius, Vec3f diffuse, float reflection = 0, float refraction = 0) :
            center(center), radius(radius), diametr(radius * radius) {

        this->diffuseColor = diffuse;
        this->reflection = reflection;
        this->refraction = refraction;
    }

    void getSurfaceData(const Vec3f &hit, Vec3f &normal) const override {
        normal = (hit - center).normalize();
    }

    bool intersect(const Vec3f &orig, const Vec3f &dir, float &tNear) const override {
        Vec3f L = orig - center;
        float a = dir.dot(dir);
        float b = 2 * dir.dot(L);
        float c = L.dot(L) - diametr;

        float discriminant = b * b - 4 * a * c;

        if (discriminant < 0) return false;


        float t0, t1;
        if (discriminant == 0)  {
            t0 = t1 = static_cast<float>(-0.5 * b / a);
        } else {
            float q = (b > 0) ?
                      -0.5 * (b + sqrt(discriminant)) :
                      -0.5 * (b - sqrt(discriminant));

            t0 = q / a;
            t1 = c / q;
        }

        if (t0 > t1) std::swap(t0, t1);

        if (t0 < 0) {
            t0 = t1; // if t0 is negative, let's use t1 instead
            if (t0 < 0) return false; // both t0 and t1 are negative
        }

        tNear = t0;

        return true;
    }
};


#endif //RAYTRACER_SPHERE_H
