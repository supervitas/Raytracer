//
// Created by Виталий on 23.12.2017.
//

#ifndef RAYTRACER_SCENE_H
#define RAYTRACER_SCENE_H


#include <vector>
#include "../Primitives/Renderable.h"

class Scene {
public:
    std::vector<Renderable*> renderables;
    void Add(Renderable &renderable);
};


#endif //RAYTRACER_SCENE_H
