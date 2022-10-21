//
// Created by helmholtz on 2022/8/29.
//

#ifndef RAY_TRACING_REST_LIFE_VEC3_H
#define RAY_TRACING_REST_LIFE_VEC3_H

#include "utils.h"
#include <cmath>

class vec3
{
private:
    float _x, _y, _z;
public:
    vec3() : _x(0), _y(0), _z(0)
    {};

    vec3(float x, float y, float z) : _x(x), _y(y), _z(z)
    {};

    vec3 normalize() const;

    float inv_length() const;

    float length() const;

    float length_squared() const;

    vec3 cross(const vec3 &b) const;

    float dot(const vec3 &b) const;

    float x() const { return _x; };

    float y() const { return _y; };

    float z() const { return _z; };

    static vec3 random_vec_in_a_sphere();

    static vec3 random_vec_in_a_hemisphere(const vec3 &n);

    vec3 operator+(const vec3 &b) const
    { return {_x + b._x, _y + b._y, _z + b._z}; };

    vec3 operator-(const vec3 &b) const
    { return {_x - b._x, _y - b._y, _z - b._z}; };

    vec3 operator*(const vec3 &b) const
    { return {_x * b._x, _y * b._y, _z * b._z}; };

    vec3 operator/(const vec3 &b) const
    { return {_x / b._x, _y / b._y, _z / b._z}; };

    vec3 operator*(const float b) const
    { return {_x * b, _y * b, _z * b}; };

    vec3 operator/(const float b) const
    { return {_x / b, _y / b, _z / b}; };

    friend vec3 operator*(float a, const vec3 &b);

    friend vec3 operator-(const vec3 &a);

    float operator[](const int i) const;
    float& operator[](const int i);
};

using color = vec3;

#endif //RAY_TRACING_REST_LIFE_VEC3_H
