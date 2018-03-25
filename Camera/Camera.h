//
// Created by Виталий on 17.12.2017.
//

#ifndef RAYTRACER_CAMERA_H
#define RAYTRACER_CAMERA_H


#include "../Math/Vec3.h"

class Camera {
public:
    Vec3f position;
    float fov;
    float angle;

    Camera(Vec3f position, Vec3f direction, float fov = 60);

};


#endif //RAYTRACER_CAMERA_H
