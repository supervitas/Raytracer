//
// Created by Виталий on 10.12.2017.
//

#ifndef RAYTRACER_SPHERE_H
#define RAYTRACER_SPHERE_H


#include "../Math/Vec3.h"
#include "Renderable.h"
#include "../Math/global.h"

class Sphere : public Renderable {
public:
    Vec3f center;
    float radius, radius2;

    Sphere(const Vec3f &c, const float &r) : center(c), radius(r), radius2(r * r) {}


    bool intersect(const Vec3f &orig, const Vec3f &dir, float &tnear, uint32_t &index, Vec2f &uv) const {
        Vec3f L = orig - center;
        float a = dotProduct(dir, dir);
        float b = 2 * dotProduct(dir, L);
        float c = dotProduct(L, L) - radius2;
        float t0, t1;
        if (!solveQuadratic(a, b, c, t0, t1)) return false;
        if (t0 < 0) t0 = t1;
        if (t0 < 0) return false;
        tnear = t0;

        return true;
    }
    void getSurfaceProperties(const Vec3f &P, const Vec3f &I, const uint32_t &index, const Vec2f &uv, Vec3f &N, Vec2f &st) const
    { N = normalize(P - center); }
};


#endif //RAYTRACER_SPHERE_H
