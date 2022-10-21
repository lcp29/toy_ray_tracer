//
// Created by helmholtz on 2022/8/29.
//

#ifndef RAY_TRACING_REST_LIFE_SPHERE_H
#define RAY_TRACING_REST_LIFE_SPHERE_H

#include "hittable.h"
#include "../material/material.h"
#include <memory>

using std::shared_ptr;

class sphere : public hittable
{
private:
    vec3 position;
    float radius;
    shared_ptr<material> mat;
public:
    sphere(vec3 position, float radius, shared_ptr<material> mat): position(position), radius(radius), mat(mat) {};
    bool hit(const ray &r, float tmin, float tmax, hit_record &rec) const override;
    aabb get_aabb() override;
};


#endif //RAY_TRACING_REST_LIFE_SPHERE_H
