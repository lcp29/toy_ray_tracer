//
// Created by helmholtz on 2022/8/30.
//

#include "metal.h"

inline vec3 reflection(const vec3 &d, const vec3 &n)
{
    return d - 2 * n * d.dot(n);
}

bool metal::scatter(const ray &i, ray &s, const hit_record &rec, color &attenuation)
{
    attenuation = _attenuation;
    s.setd(reflection(i.d().normalize(), rec.normal) + vec3::random_vec_in_a_sphere() * _fuzziness);
    s.seto(rec.p + s.d() * 0.000001);
    return true;
}
