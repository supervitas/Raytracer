//
// Created by Виталий on 26.03.2018.
//

#ifndef RAYTRACER_VEC2_H
#define RAYTRACER_VEC2_H


template<typename T>
class Vec2 {
public:
    T x, y;

    Vec2() : x(0), y(0) {}
    Vec2(T x, T y) : x(x), y(y) {}
    Vec2(T x) : x(x), y(x) {}
    Vec2 operator * (const float &r) const { return Vec2(x * r, y * r); }
    Vec2 operator + (const Vec2 &v) const { return Vec2(x + v.x, y + v.y); }
};

typedef Vec2<float> Vec2f;

#endif //RAYTRACER_VEC2_H
