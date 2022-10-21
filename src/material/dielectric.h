//
// Created by helmholtz on 2022/8/29.
//

#ifndef RAY_TRACING_REST_LIFE_DIELECTRIC_H
#define RAY_TRACING_REST_LIFE_DIELECTRIC_H

#include "material.h"
#include "../utils.h"

class dielectric : public material
{
private:
    float nio_ratio;
    color c;
    float density;
public:
    explicit dielectric(float n, color c, float d): nio_ratio(n), c(c), density(d) {};
    bool scatter(const ray &i, ray &s, const hit_record &rec, color &attenuation) override;
    color emission(const ray &i, const hit_record &rec) override { return {0, 0, 0}; };
};


#endif //RAY_TRACING_REST_LIFE_DIELECTRIC_H
