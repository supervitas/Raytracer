//
// Created by Виталий on 23.12.2017.
//

#ifndef RAYTRACER_RENDERABLE_H
#define RAYTRACER_RENDERABLE_H

#include "../Math/Vec3.h"


class Renderable {
public:
    Vec3i color;
    virtual bool intersects() = 0;
};


#endif //RAYTRACER_RENDERABLE_H
