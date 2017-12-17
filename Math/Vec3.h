//
// Created by Виталий on 07.12.2017.
//

#ifndef RAYTRACER_VEC3_H
#define RAYTRACER_VEC3_H


#include <iostream>
#include <cmath>

template<typename T>
class Vec3 {
public:
    T x, y, z;

    Vec3(T x, T y, T z) : x(x), y(y), z(z) {}
    Vec3() : x(T(0)), y(T(0)), z(T(0)) {};



    T dot(const Vec3<T> &v) const { return x * v.x + y * v.y + z * v.z; }
    Vec3<T> operator * (const T &f) const { return Vec3<T>(x * f, y * f, z * f); }
    Vec3<T> operator * (const Vec3<T> &v) const { return Vec3<T>(x * v.x, y * v.y, z * v.z); }
    Vec3<T> operator - (const Vec3<T> &v) const { return Vec3<T>(x - v.x, y - v.y, z - v.z); }
    Vec3<T> operator + (const Vec3<T> &v) const { return Vec3<T>(x + v.x, y + v.y, z + v.z); }
    Vec3<T>& operator += (const Vec3<T> &v) { x += v.x, y += v.y, z += v.z; return *this; }
    Vec3<T>& operator *= (const Vec3<T> &v) { x *= v.x, y *= v.y, z *= v.z; return *this; }
    Vec3<T> operator - () const { return Vec3<T>(-x, -y, -z); }
};

typedef Vec3<float> Vec3f;
typedef Vec3<int> Vec3i;

#endif //RAYTRACER_VEC3_H
