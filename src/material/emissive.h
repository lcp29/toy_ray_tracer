//
// Created by helmholtz on 2022/8/30.
//

#ifndef RAY_TRACING_REST_LIFE_EMISSIVE_H
#define RAY_TRACING_REST_LIFE_EMISSIVE_H

#include "material.h"

class emissive : public material
{
private:
    color c;
public:
    explicit emissive(color c): c(c) {};
    bool scatter(const ray &i, ray &s, const hit_record &rec, color &attenuation) override { return false; };
    color emission(const ray &i, const hit_record &rec) override { return c; };
};


#endif //RAY_TRACING_REST_LIFE_EMISSIVE_H
