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
    float radius;

    Sphere(Vec3f Center, float Radius, Vec3i Color);
    bool intersects();


};


#endif //RAYTRACER_SPHERE_H
