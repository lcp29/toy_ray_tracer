//
// Created by helmholtz on 2022/8/29.
//

#include "lambertian.h"

bool lambertian::scatter(const ray &i, ray &s, const hit_record &rec, color &attenuation)
{
    attenuation = _attenuation;
    s.setd(rec.normal + vec3::random_vec_in_a_sphere());
    s.seto(rec.p + s.d() * 0.000001);
    return true;
}
