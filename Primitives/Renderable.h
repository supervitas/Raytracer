//
// Created by Виталий on 23.12.2017.
//

#ifndef RAYTRACER_RENDERABLE_H
#define RAYTRACER_RENDERABLE_H

#include "../Math/Vec3.h"
#include "../Math/Vec2.h"

enum MaterialType { DIFFUSE_AND_GLOSSY, REFLECTION_AND_REFRACTION, REFLECTION };


class Renderable {
public:
    Renderable() : materialType(DIFFUSE_AND_GLOSSY),
            ior(1.3), Kd(0.8), Ks(0.2), diffuseColor(0.2), specularExponent(25) {}
    virtual ~Renderable() = default;

    virtual bool intersect(const Vec3f &, const Vec3f &, float &, uint32_t &, Vec2f &) const = 0;
    virtual void getSurfaceProperties(const Vec3f &, const Vec3f &, const uint32_t &, const Vec2f &, Vec3f &, Vec2f &) const = 0;
    virtual Vec3f evalDiffuseColor(const Vec2f &) const { return diffuseColor; }
    // material properties
    MaterialType materialType;
    float ior;
    float Kd, Ks;
    Vec3f diffuseColor{};
    float specularExponent;
};


#endif //RAYTRACER_RENDERABLE_H
