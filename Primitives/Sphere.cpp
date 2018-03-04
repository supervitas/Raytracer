//
// Created by Виталий on 24.12.2017.
//

#include "Sphere.h"

bool Sphere::intersects(const Vec3f &rayorig, const Vec3f &raydir, float &t0, float &t1) const {
    Vec3f l = center - rayorig;

    float tca = l.dot(raydir);
    if (tca < 0) return false;
    float d2 = l.dot(l) - tca * tca;
    if (d2 > diametr) return false;
    float thc = sqrt(diametr - d2);
    t0 = tca - thc;
    t1 = tca + thc;

    return true;
}

Sphere::Sphere(Vec3f center, float radius, Vec3f color, float opacity, float reflectivity) {
    this->center = center;
    this->color = Vec3f(color.x / 255, color.y / 255, color.z / 255);
    this->diametr = radius * radius;
    this->opacity = opacity;
    this->reflectivity = reflectivity;
}

Sphere::~Sphere() {
}
