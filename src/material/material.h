//
// Created by helmholtz on 2022/8/29.
//

#ifndef RAY_TRACING_REST_LIFE_MATERIAL_H
#define RAY_TRACING_REST_LIFE_MATERIAL_H


#include "../ray.h"
#include "../hit_record.h"
#include "../vec3.h"

class hit_record;

class material
{
public:
    virtual bool scatter(const ray &i, ray &s, const hit_record &rec, color &attenuation) = 0;
    virtual color emission(const ray &i, const hit_record &rec) = 0;
};


#endif //RAY_TRACING_REST_LIFE_MATERIAL_H
