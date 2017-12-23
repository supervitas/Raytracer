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

#define MAX_RAY_DEPTH 5

class Raytracer {
private:
    int frameBufferWidth;
    int frameBufferHeight;
    Scene &scene;
    Camera &camera;

public:
    Raytracer(int frameBufferWidth, int frameBufferHeight, Scene &scene, Camera &camera);
    std::shared_ptr<Vec3f> render();
};


#endif //RAYTRACER_RAYTRACER_H
