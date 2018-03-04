//
// Created by Виталий on 04.03.2018.
//

#ifndef RAYTRACER_PLANE_H
#define RAYTRACER_PLANE_H


#include "Renderable.h"

class Plane : public Renderable {
private:

public:
    Plane(Vec3f center, float radius, Vec3f color, float opacity, float reflectivity);
    bool intersects(const Vec3f &rayorig, const Vec3f &raydir, float &t0, float &t1) const;

};


#endif //RAYTRACER_PLANE_H
