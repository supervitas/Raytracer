//
// Created by Виталий on 10.12.2017.
//

#ifndef RAYTRACER_RAYTRACER_H
#define RAYTRACER_RAYTRACER_H

#include <algorithm>
#include <fstream>
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

private:
    Vec3f trace(const Vec3f &orig, const Vec3f &dir, uint32_t depth);

public:
    void setBackgroundColor(Vec3f const &bc);
    Vec3f const& bacgroundColor() const;
};


#endif //RAYTRACER_RAYTRACER_H
