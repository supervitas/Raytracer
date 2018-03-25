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
    Vec3(T xx) : x(xx), y(xx), z(xx) {}
    Vec3() : x(T(0)), y(T(0)), z(T(0)) {};

    Vec3& normalize() {
        T nor2 = length2();
        if (nor2 > 0) {
            T invNor = 1 / sqrt(nor2);
            x *= invNor, y *= invNor, z *= invNor;
        }
        return *this;
    }

    Vec3& set(T x, T y, T z) {
        this->x = x;
        this->y = y;
        this->z = z;

        return *this;
    }

    T length2() const {
        return x * x + y * y + z * z;
    }

    friend std::ostream & operator << (std::ostream &os, const Vec3<T> &v) {
        os << "[" << v.x << " " << v.y << " " << v.z << "]";
        return os;
    }

    T dot(const Vec3<T> &v) const { return x * v.x + y * v.y + z * v.z; }
    Vec3<T> operator * (const T &f) const { return Vec3<T>(x * f, y * f, z * f); }
    Vec3<T> operator * (const Vec3<T> &v) const { return Vec3<T>(x * v.x, y * v.y, z * v.z); }
    Vec3<T> operator - (const Vec3<T> &v) const { return Vec3<T>(x - v.x, y - v.y, z - v.z); }
    Vec3<T> operator + (const Vec3<T> &v) const { return Vec3<T>(x + v.x, y + v.y, z + v.z); }
    Vec3<T>& operator += (const Vec3<T> &v) { x += v.x, y += v.y, z += v.z; return *this; }
    Vec3<T>& operator *= (const Vec3<T> &v) { x *= v.x, y *= v.y, z *= v.z; return *this; }
    Vec3<T> operator - () const { return Vec3<T>(-x, -y, -z); }
    friend Vec3 operator * (const float &r, const Vec3<T> &v)
    { return Vec3(v.x * r, v.y * r, v.z * r); }
};

typedef Vec3<float> Vec3f;

#endif //RAYTRACER_VEC3_H
