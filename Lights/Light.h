//
// Created by Виталий on 26.01.2018.
//

#ifndef RAYTRACER_LIGHT_H
#define RAYTRACER_LIGHT_H


#include "../Math/Vec3.h"

class Light {
public:
    Vec3f position;
    float intensity;
    Vec3f color;
    Light(Vec3f position, float intensity = 1, Vec3f color = (255));
};


#endif //RAYTRACER_LIGHT_H
