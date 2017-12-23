//
// Created by Виталий on 24.12.2017.
//

#include "Sphere.h"

bool Sphere::intersects() {
    return false;
}

Sphere::Sphere(Vec3f Center, float Radius, Vec3i Color) {
    this->center = Center;
    this->radius = Radius;
    this->color = Color;
}
