//
// Created by helmholtz on 2022/8/29.
//

#include "dielectric.h"

inline vec3 refraction(const vec3 &d, const vec3 &n, float nio_ratio)
{
    auto t_perp = nio_ratio * (d - n * (n.dot(d)));
    auto t_para = -n * sqrt(1 - t_perp.length_squared());
    return t_perp + t_para;
}

inline vec3 reflection(const vec3 &d, const vec3 &n)
{
    return d - 2 * n * d.dot(n);
}

inline float schlick_reflection_rate(float nr, float c)
{
    auto r0 = (nr - 1) / (nr + 1);
    r0 *= r0;
    auto cosine_coe = 1 - c;
    cosine_coe *= cosine_coe;
    cosine_coe *= cosine_coe;
    cosine_coe *= 1 - c;
    return r0 + (1 - r0) * cosine_coe;
}

bool dielectric::scatter(const ray &i, ray &s, const hit_record &rec, color &attenuation)
{
    attenuation = c;
    if (rec.from_inside)
    {
        auto transport_distance =(rec.p - i.o()).length();
        attenuation = attenuation * exp(-density * transport_distance);
    }
    auto d = i.d().normalize();
    auto n = rec.from_inside ? - rec.normal : rec.normal;
    auto nr = rec.from_inside ? 1 / nio_ratio : nio_ratio;
    auto cos_i = - d.dot(n);
    auto sin_i_2 = 1 - cos_i * cos_i;
    if (nr * nr * sin_i_2 > 1)
    {
        s.setd(reflection(d, n));
        s.seto(rec.p + s.d() * 0.0000001);
        return true;
    }
    // schlick
    if (schlick_reflection_rate(nr, cos_i) > random_float_0_1())
    {
        s.setd(reflection(d, n));
        s.seto(rec.p + s.d() * 0.0000001);
    }
    else
    {
        s.setd(refraction(d, n, nr));
        s.seto(rec.p + s.d() * 0.0000001);
    }
    return true;
}
