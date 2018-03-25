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

bool Raytracer::trace(
        const Vec3f &orig, const Vec3f &dir,
        float &tNear, uint32_t &index, Vec2f &uv, Renderable **hitObject) {
    *hitObject = nullptr;

    for (auto &renderable : this->scene.renderables) {
        float tNearK = INFINITY;
        uint32_t indexK;
        Vec2f uvK;
        if (renderable->intersect(orig, dir, tNearK, indexK, uvK) && tNearK < tNear) {
            *hitObject = renderable;
            tNear = tNearK;
            index = indexK;
            uv = uvK;
        }
    }

    return (*hitObject != nullptr);
}

Vec3f Raytracer::castRay(const Vec3f &orig, const Vec3f &dir, uint32_t depth) {
    if (depth > MAX_RAY_DEPTH) {
        return Vec3f(BACKGROUND);
    }

    Vec3f hitColor = Vec3f(BACKGROUND);
    float tnear = INFINITY;
    Vec2f uv;
    uint32_t index = 0;
    Renderable *hitObject = nullptr;
    auto bias = 0.00001;
    if (trace(orig, dir, tnear, index, uv, &hitObject)) {
        Vec3f hitPoint = orig + dir * tnear;
        Vec3f N; // normal
        Vec2f st; // st coordinates
        hitObject->getSurfaceProperties(hitPoint, dir, index, uv, N, st);

        switch (hitObject->materialType) {
            case REFLECTION_AND_REFRACTION: {
                Vec3f reflectionDirection = normalize(reflect(dir, N));
                Vec3f refractionDirection = normalize(refract(dir, N, hitObject->ior));
                Vec3f reflectionRayOrig = (dotProduct(reflectionDirection, N) < 0) ?
                                          hitPoint - N * bias :
                                          hitPoint + N * bias;
                Vec3f refractionRayOrig = (dotProduct(refractionDirection, N) < 0) ?
                                          hitPoint - N * bias :
                                          hitPoint + N * bias;
                Vec3f reflectionColor = castRay(reflectionRayOrig, reflectionDirection, depth + 1);
                Vec3f refractionColor = castRay(refractionRayOrig, refractionDirection, depth + 1);
                float kr;
                fresnel(dir, N, hitObject->ior, kr);
                hitColor = reflectionColor * kr + refractionColor * (1 - kr);
                break;
            }
            case REFLECTION: {
                float kr;
                fresnel(dir, N, hitObject->ior, kr);
                Vec3f reflectionDirection = reflect(dir, N);
                Vec3f reflectionRayOrig = (dotProduct(reflectionDirection, N) < 0) ?
                                          hitPoint + N * bias :
                                          hitPoint - N * bias;
                hitColor = castRay(reflectionRayOrig, reflectionDirection, depth + 1) * kr;
                break;
            }
            default: {
                Vec3f lightAmt = 0, specularColor = 0;
                Vec3f shadowPointOrig = (dotProduct(dir, N) < 0) ?
                                        hitPoint + N * bias :
                                        hitPoint - N * bias;

                for (auto &light : this->scene.lights) {
                    Vec3f lightDir = light->position - hitPoint;
                    // square of the distance between hitPoint and the light
                    float lightDistance2 = dotProduct(lightDir, lightDir);
                    lightDir = normalize(lightDir);
                    float LdotN = std::max(0.f, dotProduct(lightDir, N));
                    Renderable *shadowHitObject = nullptr;
                    float tNearShadow = INFINITY;
                    // is the point in shadow, and is the nearest occluding object closer to the object than the light itself?
                    bool inShadow =
                            trace(shadowPointOrig, lightDir,  tNearShadow, index, uv, &shadowHitObject) &&
                            tNearShadow * tNearShadow < lightDistance2;
                    lightAmt += (1 - inShadow) * light->intensity * LdotN;
                    Vec3f reflectionDirection = reflect(-lightDir, N);
                    specularColor +=
                            powf(std::max(0.f, -dotProduct(reflectionDirection, dir)), hitObject->specularExponent) *
                                    light->intensity;
                }
                hitColor = lightAmt * hitObject->evalDiffuseColor(st) * hitObject->Kd + specularColor * hitObject->Ks;
                break;
            }
        }
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

                    image[i * frameBufferWidth + j] = castRay(camera.position, raydir, 0);
                }
            }
        };

        taskManager.AddTask(job);
    }

    taskManager.waitAll();
}
