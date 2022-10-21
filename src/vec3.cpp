//
// Created by helmholtz on 2022/8/29.
//

#include "vec3.h"

vec3 vec3::normalize() const
{
    return vec3(_x, _y, _z) * inv_length();
}

vec3 operator*(float a, const vec3 &b)
{
    return {a*b._x, a * b._y, a * b._z};
}

float vec3::inv_length() const
{
    return 1.0 / sqrt(_x * _x + _y * _y + _z * _z);
}

vec3 operator-(const vec3 &a)
{
    return {-a._x, -a._y, -a._z};
}

vec3 vec3::cross(const vec3 &b) const
{
    return {_y * b._z - _z * b._y, _z * b._x - _x * b._z, _x * b._y - _y * b._x};
}

float vec3::dot(const vec3 &b) const
{
    return _x * b._x + _y * b._y + _z * b._z;
}

float vec3::length() const
{
    return sqrt(_x * _x + _y * _y + _z * _z);
}

float vec3::length_squared() const
{
    return _x * _x + _y * _y + _z * _z;
}

vec3 vec3::random_vec_in_a_sphere()
{
    float r = random_float_0_1();
    float theta = random_float_0_1();
    float phi = random_float_0_1();
    r = pow(r, 1.0 / 3);
    theta = acos(1 - 2 * theta);
    phi *= 6.28318531;
    return {r * sin(theta) * cos(phi), r * sin(theta) * sin(phi), r * cos(theta)};
}

vec3 vec3::random_vec_in_a_hemisphere(const vec3 &n)
{
    auto r = random_vec_in_a_sphere();
    if (r.dot(n) < 0)
        r = r - 2 * n * r.dot(n);
    return r;
}

float vec3::operator[](const int i) const
{
    switch (i)
    {
        case 0:
            return _x;
        case 1:
            return _y;
        case 2:
            return _z;
        default:
            return 0;
    }
}

float &vec3::operator[](const int i)
{
    switch (i)
    {
        case 0:
            return _x;
        case 1:
            return _y;
        default:
            return _z;
    }
}
