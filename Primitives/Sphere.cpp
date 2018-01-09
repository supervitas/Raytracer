//
// Created by Виталий on 24.12.2017.
//

#include "Sphere.h"

bool Sphere::intersects(const Vec3f &rayorig, const Vec3f &raydir, float &t0, float &t1) const {

    Vec3f l = center - rayorig;
    float tca = l.dot(raydir);
    if (tca < 0) return false;
    float d2 = l.dot(l) - tca * tca;
    if (d2 > radius2) return false;
    float thc = sqrt(radius2 - d2);
    t0 = tca - thc;
    t1 = tca + thc;

    return true;

}

Sphere::Sphere(Vec3f Center, float Radius, Vec3f Color) {
    this->center = Center;
    this->radius = Radius;
    this->color = Vec3f(Color.x / 255, Color.y / 255, Color.z / 255);
    this->radius2 = Radius * Radius;
}
