//
// Created by helmholtz on 2022/8/29.
//

#ifndef RAY_TRACING_REST_LIFE_HITTABLE_H
#define RAY_TRACING_REST_LIFE_HITTABLE_H

#include "../ray.h"
#include "../hit_record.h"
#include "aabb.h"

class hittable
{
public:
    virtual bool hit(const ray &r, float tmin, float tmax, hit_record &rec) const = 0;
    virtual aabb get_aabb() = 0;
};


#endif //RAY_TRACING_REST_LIFE_HITTABLE_H
