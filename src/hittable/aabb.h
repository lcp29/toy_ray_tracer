//
// Created by helmholtz on 2022/8/31.
//

#ifndef RAY_TRACING_REST_LIFE_AABB_H
#define RAY_TRACING_REST_LIFE_AABB_H

#include "../vec3.h"
#include "../ray.h"
#include <algorithm>

class aabb
{
public:
    vec3 c0, c1;
    aabb() = default;
    aabb(const vec3 &c0, const vec3 &c1)
    {
        this->c0 = {fmin(c0.x(), c1.x()), fmin(c0.y(), c1.y()), fmin(c0.z(), c1.z())};
        this->c1 = {fmax(c0.x(), c1.x()), fmax(c0.y(), c1.y()), fmax(c0.z(), c1.z())};
    };
    bool hit(const ray &i, float tmin, float tmax) const;
    static aabb merge(const aabb &a, const aabb &b);
};


#endif //RAY_TRACING_REST_LIFE_AABB_H
