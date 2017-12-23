//
// Created by Виталий on 12.12.2017.
//

#include "Raytracer.h"

Raytracer::Raytracer(int frameBufferWidth, int frameBufferHeight, Scene &Scene, Camera &Camera): scene(Scene), camera(Camera) {
    this->frameBufferHeight = frameBufferHeight;
    this->frameBufferWidth = frameBufferWidth;
}



std::shared_ptr<Vec3f> Raytracer::render() {
    std::shared_ptr<Vec3f> image(new Vec3f[frameBufferWidth * frameBufferHeight], std::default_delete<Vec3f[]>());

    for (int i = 0; i < frameBufferHeight; i++) {
        for (int j = 0; j < frameBufferWidth; j++) {
//            for (auto &renderable : scene.renderables) {
//
//            }
        }
    }

    return image;
}
