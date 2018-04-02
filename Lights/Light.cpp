//
// Created by Виталий on 26.01.2018.
//

#include "Light.h"

Light::Light(Vec3f position, float intensity, Vec3f color) {
    this->position = position;
    this->intensity = intensity;
    this->color = Vec3f(color.x / 255, color.y / 255, color.z / 255);
}
