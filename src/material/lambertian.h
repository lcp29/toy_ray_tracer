//
// Created by helmholtz on 2022/8/29.
//

#ifndef RAY_TRACING_REST_LIFE_LAMBERTIAN_H
#define RAY_TRACING_REST_LIFE_LAMBERTIAN_H

#include "material.h"
#include <cstdlib>

class lambertian : public material
{
public:
    lambertian(color att): _attenuation(att) {};
    bool scatter(const ray &i, ray &s, const hit_record &rec, color &attenuation) override;
    color emission(const ray &i, const hit_record &rec) override { return {0, 0, 0}; };
private:
    color _attenuation;
};


#endif //RAY_TRACING_REST_LIFE_LAMBERTIAN_H
