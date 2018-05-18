//
// Created by Виталий on 10.12.2017.
//

#ifndef RAYTRACER_RAYTRACER_H
#define RAYTRACER_RAYTRACER_H

#include <algorithm>
#include <vector>
#include "../Math/Vec3.h"
#include "../Primitives/Sphere.h"
#include "../Scene/Scene.h"
#include "../Camera/Camera.h"
#include "../TaskManager/TaskManager.h"

#define MAX_RAY_DEPTH 5

class Raytracer {
private:
    int frameBufferWidth;
    int frameBufferHeight;
    float aspectRatio;
    float invWidth;
    float invHeight;
    float angle;
    Vec3f backgroundColor = Vec3f(0.235294, 0.67451, 0.843137);

    Scene &scene;
    Camera &camera;
    TaskManager &taskManager;

public:
    Raytracer(int frameBufferWidth, int frameBufferHeight, Scene &scene, Camera &camera,  TaskManager &taskManager);
    void render(std::vector<Vec3f> &image);
    void setBackgroundColor(Vec3f const &bc);
    Vec3f const& bacgroundColor() const;

private:
    Vec3f trace(const Vec3f &orig, const Vec3f &dir, int depth);

    void fresnel(const Vec3f &I, const Vec3f &N, const float &ior, float &kr);
    Vec3f reflect(const Vec3f &I, const Vec3f &N);
    Vec3f refract(const Vec3f &I, const Vec3f &N, const float &ior);
};


#endif //RAYTRACER_RAYTRACER_H
