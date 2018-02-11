//
// Created by Виталий on 26.01.2018.
//

#ifndef RAYTRACER_LIGHT_H
#define RAYTRACER_LIGHT_H


#include "../Math/Vec3.h"

class Light {
public:
    Vec3f position;
    float intencity;
    Vec3f color;
    Light(Vec3f position, float intensity, Vec3f color) {
        this->position = position;
        this->intencity = intensity;
        this->color = Vec3f(color.x / 255, color.y / 255, color.z / 255);
    };
};


#endif //RAYTRACER_LIGHT_H
