//
// Created by Виталий on 12.12.2017.
//
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

Vec3f Raytracer::trace(const Vec3f &orig, const Vec3f &dir, int depth) {
    auto hitColor = Vec3f(this->backgroundColor);

    if (depth > MAX_RAY_DEPTH) return hitColor;

    Renderable *hitObject = nullptr;

    float tNear = INFINITY;
    for (auto &renderable : this->scene.renderables) {
        float near = 0;
        if(renderable->intersect(orig, dir, near) && tNear > near) {
            hitObject = renderable;
            tNear = near;
        }
    }


    if (!hitObject) return hitColor;


    Vec3f hitPoint = orig + dir * tNear;
    Vec3f normal;

    hitColor = 0;

    hitObject->getSurfaceData(hitPoint, normal);

    auto bias = 1;

    if (hitObject->reflection > 0 && hitObject->refraction == 0) {
        float kr;
        fresnel(dir, normal, hitObject->ior, kr);
        Vec3f reflectionDirection = reflect(dir, normal);
        Vec3f reflectionRayOrig = (reflectionDirection.dot(normal) < 0) ?
                                  hitPoint + normal * bias :
                                  hitPoint - normal * bias;

        hitColor = trace(reflectionRayOrig, reflectionDirection, depth + 1) * kr;
    }

    if (hitObject->reflection > 0 && hitObject->refraction > 0) {
        Vec3f reflectionDirection = reflect(dir, normal).normalize();
        Vec3f refractionDirection = refract(dir, normal, hitObject->ior);
        Vec3f reflectionRayOrig = (reflectionDirection.dot(normal) < 0) ?
                                  hitPoint - normal * bias :
                                  hitPoint + normal * bias;

        Vec3f refractionRayOrig = (refractionDirection.dot(normal) < 0) ?
                                  hitPoint - normal * bias :
                                  hitPoint + normal * bias;
        Vec3f reflectionColor = trace(reflectionRayOrig, reflectionDirection, depth + 1);
        Vec3f refractionColor = trace(refractionRayOrig, refractionDirection, depth + 1);

        float kr;
        fresnel(dir, normal, hitObject->ior, kr);
        hitColor = reflectionColor * kr + refractionColor * (1 - kr);

    }

        Vec3f shadowPointOrig = dir.dot(normal) < 0 ? hitPoint + normal * bias : hitPoint - normal * bias;

        for (auto &light : this->scene.lights) {
            auto lightDirection = (light->position - hitPoint).normalize();
            bool inLight = true;

            for (auto &renderable : this->scene.renderables) {
                if (renderable->intersect(shadowPointOrig, lightDirection, tNear)) {
                    inLight = false;
                    break;
                }
            }

            Vec3f lightAmt = (1 - !inLight) * light->intensity * std::max(float(0), lightDirection.dot(normal));

            Vec3f specularColor = powf(std::max(float(0), normal.dot(lightDirection)), hitObject->specularExponent) *
                                  light->intensity;

            hitColor += lightAmt * hitObject->diffuseColor * hitObject->Kd + specularColor * hitObject->Ks;


    }

    return  hitColor;
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

float clamp(const float &lo, const float &hi, const float &v) { return std::max(lo, std::min(hi, v)); }

Vec3f Raytracer::reflect(const Vec3f &I, const Vec3f &N) {
    return I - 2 * I.dot(N) * N;
}

Vec3f Raytracer::refract(const Vec3f &I, const Vec3f &N, const float &ior) {
    float cosi = clamp(-1, 1, I.dot(N));
    float etai = 1, etat = ior;
    Vec3f n = N;
    if (cosi < 0) { cosi = -cosi; } else { std::swap(etai, etat); n= -N; }
    float eta = etai / etat;
    float k = 1 - eta * eta * (1 - cosi * cosi);
    return k < 0 ? 0 : eta * I + (eta * cosi - sqrtf(k)) * n;
}


void Raytracer::fresnel(const Vec3f &I, const Vec3f &N, const float &ior, float &kr) {
    float cosi = clamp(-1, 1, I.dot(N));
    float etai = 1, etat = ior;
    if (cosi > 0) {  std::swap(etai, etat); }
    // Compute sini using Snell's law
    float sint = etai / etat * sqrtf(std::max(0.f, 1 - cosi * cosi));
    // Total internal reflection
    if (sint >= 1) {
        kr = 1;
    } else {
        float cost = sqrtf(std::max(0.f, 1 - sint * sint));
        cosi = fabsf(cosi);
        float Rs = ((etat * cosi) - (etai * cost)) / ((etat * cosi) + (etai * cost));
        float Rp = ((etai * cosi) - (etat * cost)) / ((etai * cosi) + (etat * cost));
        kr = (Rs * Rs + Rp * Rp) / 2;
    }
    // As a consequence of the conservation of energy, transmittance is given by:
    // kt = 1 - kr;
}

void Raytracer::setBackgroundColor(Vec3f const &bc) {
    this->backgroundColor = bc;
}

Vec3f const &Raytracer::bacgroundColor() const {
    return this->backgroundColor;
}
