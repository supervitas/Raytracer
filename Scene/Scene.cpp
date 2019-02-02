//
// Created by Виталий on 23.12.2017.
//

#include "Scene.h"
#include <vector>


void Scene::Add(std::unique_ptr<Renderable> renderable) {
    renderables.push_back(std::move(renderable));
}

void Scene::AddLight(std::unique_ptr<Light> light) {
    lights.push_back(std::move(light));
}

std::vector<std::unique_ptr<Renderable>> const& Scene::Renderables() {
    return renderables;
}

std::vector<std::unique_ptr<Light>> const& Scene::Lights() {
    return lights;
}
