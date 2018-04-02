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

Vec3f Raytracer::trace(const Vec3f &orig, const Vec3f &dir, uint32_t depth) {
    auto hitColor = Vec3f(this->backgroundColor);
    Renderable *hitObject = nullptr;

    float tNear = INFINITY;
    float far = INFINITY;
    for (auto &renderable : this->scene.renderables) {
        if(renderable->intersect(orig, dir, tNear, far) && tNear > far) {
            hitObject = renderable;

        }
    }

    if (depth > MAX_RAY_DEPTH) return hitColor;

    auto bias = 0.00001;

    if (hitObject) {
        hitColor = hitObject->diffuseColor;
    }

    return hitColor;
}


void Raytracer::render(std::vector<Vec3f> &image) {
    auto heightPerThread = frameBufferHeight / taskManager.concurentThreads;

    for (int threadsNumber = 0; threadsNumber < taskManager.concurentThreads; threadsNumber++) {
        std::function<void()> job = [this, &image, threadsNumber, heightPerThread] {
            auto startHeight = heightPerThread * threadsNumber;
            auto endHeight = startHeight + heightPerThread;

            for (int i = startHeight; i < endHeight; i++) {
                for (int j = 0; j < frameBufferWidth; j++) {
                    auto x = static_cast<float>((2 * ((j + 0.5) * invWidth) - 1) * angle * aspectRatio);
                    auto y = static_cast<float>((1 - 2 * ((i + 0.5) * invHeight)) * angle);

                    Vec3f raydir(x, y, -1);
                    raydir.normalize();

                    image[i * frameBufferWidth + j] = trace(camera.position, raydir, 0);
                }
            }
        };

        taskManager.AddTask(job);
    }

    taskManager.waitAll();
}

void Raytracer::setBackgroundColor(Vec3f const &bc) {
    this->backgroundColor = bc;
}

Vec3f const &Raytracer::bacgroundColor() const {
    return this->backgroundColor;
}
