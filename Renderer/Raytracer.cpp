//
// Created by Виталий on 12.12.2017.
//

#include <thread>
#include "Raytracer.h"

Raytracer::Raytracer(int frameBufferWidth, int frameBufferHeight, Scene &Scene, Camera &Camera, TaskManager &taskManager)
        : scene(Scene), camera(Camera), taskManager(taskManager) {

    this->frameBufferHeight = frameBufferHeight;
    this->frameBufferWidth = frameBufferWidth;

    this->aspectRatio = frameBufferWidth / frameBufferHeight;
    this->invHeight = 1 / static_cast<float>(frameBufferHeight);
    this->invWidth = 1 / static_cast<float>(frameBufferWidth);

    this->angle = camera.angle;
}

Vec3f Raytracer::trace(const Vec3f &cameraPosition, const Vec3f &rayDirection, const int & depth) {
    Renderable *renderable = nullptr;

    auto result = Vec3f(0.1, 0.1, 0.1);

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

    if (!renderable) return result;

    Vec3f phit = cameraPosition + rayDirection * tnear; // point of intersection
    Vec3f nhit = phit - renderable->center; // normal at the intersection point
    nhit.normalize();
    float bias = 1e-4; // add some bias to the point from which we will be tracing

    auto surfaceColor = Vec3f();

    for (Renderable *&sceneObject : scene.renderables) {
        if (sceneObject->emissionColor.x > 0) {

            auto transmission = Vec3f(1,1,1);
            Vec3f lightDirection = sceneObject->center - phit;
            lightDirection.normalize();
            for (Renderable *&sceneObjectNested : scene.renderables) {
                if (sceneObject != sceneObjectNested) {
                    float t0, t1;
                    if (sceneObjectNested->intersects(phit + nhit * bias, lightDirection, t0, t1)) {
                        transmission.x = 0;
                        transmission.y = 0;
                        transmission.z = 0;

                        break;
                    }
                }
            }
            surfaceColor += sceneObject->color * transmission *
                            std::max(float(0), nhit.dot(lightDirection)) * sceneObject->emissionColor;

        }
    }


    return surfaceColor + renderable->emissionColor;
}


std::shared_ptr<Vec3f> Raytracer::render() {
    std::shared_ptr<Vec3f> image(new Vec3f[frameBufferWidth * frameBufferHeight], std::default_delete<Vec3f[]>());
    auto ptr = image.get();

    auto heightPerThread = frameBufferHeight / taskManager.concurentThreads;

    for (int threadsNumber = 0; threadsNumber < taskManager.concurentThreads; threadsNumber++) {
        std::function<void()> job = [this, ptr, threadsNumber, heightPerThread] {
            auto startHeight = heightPerThread * threadsNumber;
            auto endHeight = startHeight + heightPerThread;

            for (int i = startHeight; i < endHeight; i++) {
                for (int j = 0; j < frameBufferWidth; j++) {
                    auto x = static_cast<float>((2 * ((j + 0.5) * invWidth) - 1) * angle * aspectRatio);
                    auto y = static_cast<float>((1 - 2 * ((i + 0.5) * invHeight)) * angle);

                    Vec3f raydir(x, y, -1);
                    raydir.normalize();

                    auto pixel = trace(camera.position, raydir, 0);

                    ptr[i * frameBufferWidth + j] = pixel;
                }
            }
        };

        taskManager.AddTask(job);
    }

    taskManager.waitAll();

    return image;
}
