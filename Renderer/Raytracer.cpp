//
// Created by Виталий on 12.12.2017.
//

#include "Raytracer.h"

Raytracer::Raytracer(int frameBufferWidth, int frameBufferHeight, Scene &Scene, Camera &Camera): scene(Scene), camera(Camera) {
    this->frameBufferHeight = frameBufferHeight;
    this->frameBufferWidth = frameBufferWidth;

    this->aspectRatio = frameBufferWidth / frameBufferHeight;
    this->invHeight = 1 / float(frameBufferHeight);
    this->invWidth = 1 / float(frameBufferWidth);

    this->angle = camera.angle;
}

Vec3f Raytracer::trace(const Vec3f &cameraPosition, const Vec3f &rayDirection, const int & depth) {
    Renderable *renderable = nullptr;

    auto result = Vec3f(0.1,0.1,0.1);

    float tnear = INFINITY;

    for (Renderable *&sceneObject : scene.renderables) {
        float t0 = INFINITY, t1 = INFINITY;


        if (sceneObject->intersects(cameraPosition, rayDirection, t0, t1)) {
            if (t0 < 0) t0 = t1;

            if (t0 < tnear) {
                tnear = t0;
                renderable = *&sceneObject;
            }
        }
    }

    if (renderable) {
        result = renderable->color;
    }


    return result;
}



std::shared_ptr<Vec3f> Raytracer::render() {
    std::shared_ptr<Vec3f> image(new Vec3f[frameBufferWidth * frameBufferHeight], std::default_delete<Vec3f[]>());
    auto ptr = image.get();

    for (int i = 0; i < frameBufferHeight; i++) {
        for (int j = 0; j < frameBufferWidth; j++) {

            auto x = static_cast<float>((2 * ((j + 0.5) * invWidth) - 1) * angle * aspectRatio);
            auto y = static_cast<float>((1 - 2 * ((i + 0.5) * invHeight)) * angle);

            Vec3f raydir(x, y, -1);
            raydir.normalize();

            auto pixel = trace(camera.position, raydir, 0);

            ptr[i * frameBufferWidth + j] = pixel;

        }
    }

    return image;
}
