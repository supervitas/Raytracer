//
// Created by Виталий on 23.12.2017.
//

#ifndef RAYTRACER_RENDERABLE_H
#define RAYTRACER_RENDERABLE_H

#include "../Math/Vec3.h"
#include "../Math/Vec2.h"


class Renderable {
public:
    Renderable() : ior(1.3), Kd(0.8), Ks(0.2), diffuseColor(0.2), specularExponent(25), reflection(0), refraction(0) {}
    virtual ~Renderable() = default;
    virtual void getSurfaceData(const Vec3f &hit, Vec3f &normal) const = 0;
    virtual bool intersect(const Vec3f &orig, const Vec3f &dir, float &tNear) const = 0;

    float ior;
    float Kd, Ks;
    Vec3f diffuseColor;
    float specularExponent;
    float reflection;
    float refraction;
};


#endif //RAYTRACER_RENDERABLE_H
