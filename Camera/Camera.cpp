//
// Created by Виталий on 17.12.2017.
//

#include "Camera.h"

Camera::Camera(Vec3f position, Vec3f direction, float fov) {
    this->position = position;
    this->direction = direction;
    this->fov = fov;
    this->angle = static_cast<float>(tan(M_PI * 0.5 * fov / 180));
}
