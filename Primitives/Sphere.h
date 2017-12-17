//
// Created by Виталий on 10.12.2017.
//

#ifndef RAYTRACER_SPHERE_H
#define RAYTRACER_SPHERE_H


#include "../Math/Vec3.h"

class Sphere {
public:
    Vec3f center;
    float radius;
    Vec3i color;

    Sphere(Vec3f &Center, float Radius, Vec3i &Color) : center(Center), radius(Radius), color(Color) {};


};


#endif //RAYTRACER_SPHERE_H
