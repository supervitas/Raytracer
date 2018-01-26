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
    Light(Vec3f position, float intensity) {
        this->position = position;
        this->intencity = intensity;
    };
};


#endif //RAYTRACER_LIGHT_H
