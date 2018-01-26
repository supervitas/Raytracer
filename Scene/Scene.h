//
// Created by Виталий on 23.12.2017.
//

#ifndef RAYTRACER_SCENE_H
#define RAYTRACER_SCENE_H


#include <vector>
#include "../Primitives/Renderable.h"
#include "../Lights/Light.h"

class Scene {
public:
    std::vector<Light*> lights;
    std::vector<Renderable*> renderables;

    void Add(Renderable &renderable);
    void AddLight(Light &light);
};


#endif //RAYTRACER_SCENE_H
