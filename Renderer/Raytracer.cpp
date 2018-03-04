//
// Created by Виталий on 12.12.2017.
//

#include <thread>
#include "Raytracer.h"

float mix(const float &a, const float &b, const float &mix) {
    return b * mix + a * (1 - mix);
}

Raytracer::Raytracer(int frameBufferWidth, int frameBufferHeight, Scene &Scene, Camera &Camera, TaskManager &taskManager)
        : scene(Scene), camera(Camera), taskManager(taskManager) {

    this->frameBufferHeight = frameBufferHeight;
    this->frameBufferWidth = frameBufferWidth;

    this->aspectRatio = frameBufferWidth / frameBufferHeight;
    this->invHeight = 1 / static_cast<float>(frameBufferHeight);
    this->invWidth = 1 / static_cast<float>(frameBufferWidth);

    this->angle = camera.angle;
}

Vec3f Raytracer::trace(const Vec3f &cameraPosition, const Vec3f &rayDirection, const int &depth) {
    Renderable *renderable = nullptr;


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

    if (!renderable ) return Vec3f(2);


    Vec3f result = 0;

    Vec3f hit = cameraPosition + rayDirection * tnear;
    Vec3f normal = (hit - renderable->center).normalize();
    bool inside = false;

    float bias = 1e-4;

    if (rayDirection.dot(normal) > 0) {
        normal = -normal;
        inside = true;
    }

    if ((renderable->opacity > 0 || renderable->reflectivity > 0) && depth < MAX_RAY_DEPTH) {
        float facingratio = -rayDirection.dot(normal);
        float fresneleffect = mix(static_cast<const float &>(pow(1 - facingratio, 3)), 1, 0.1);

        Vec3f refldir = rayDirection - normal * 2 * rayDirection.dot(normal);
        refldir.normalize();

//        Vec3f reflection = renderable->reflectivity > 0 ? trace(hit + normal * bias, refldir, depth + 1) : 0;
        Vec3f reflection = 0;
        Vec3f refraction = 0;

        if (renderable->opacity > 0) {
            float ior = 1.1, eta = (inside) ? ior : 1 / ior; // are we inside or outside the surface?
            float cosi = -normal.dot(rayDirection);
            float k = 1 - eta * eta * (1 - cosi * cosi);
            Vec3f refrdir = rayDirection * eta + normal * (eta *  cosi - sqrt(k));
            refrdir.normalize();
            refraction = trace(hit - normal * bias, refrdir, depth + 1);
        }
        // the result is a mix of reflection and refraction (if the sphere is transparent)
        result = (reflection * fresneleffect + refraction * (1 - fresneleffect) * renderable->opacity) * renderable->color;
    }

    for (Light *&light : scene.lights) {
        Vec3f transmission = 1;
        Vec3f lightDirection = (light->position - hit).normalize();

        for (Renderable *&sceneObject : scene.renderables) {
            float t0, t1;
            if (sceneObject->intersects(hit + normal * bias, lightDirection, t0, t1)) {
                transmission = 0;
                break;
            }
        }

        result += renderable->color * transmission *
                  std::max(float(0), normal.dot(lightDirection)) * light->color * light->intencity;
    }

    return result;
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
