//
// Created by Виталий on 23.12.2017.
//

#ifndef RAYTRACER_SCENE_H
#define RAYTRACER_SCENE_H


#include <vector>
#include "../Primitives/Renderable.h"
#include "../Lights/Light.h"

class Scene {
private:
    std::vector<std::unique_ptr<Light>> lights;
    std::vector<std::unique_ptr<Renderable>> renderables;
public:
    std::vector<std::unique_ptr<Renderable>> const&  Renderables();
    std::vector<std::unique_ptr<Light>> const& Lights();
    void Add(std::unique_ptr<Renderable> renderable);
    void AddLight(std::unique_ptr<Light> light);
};


#endif //RAYTRACER_SCENE_H
