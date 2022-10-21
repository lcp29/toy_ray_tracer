//
// Created by helmholtz on 2022/8/31.
//

#ifndef RAY_TRACING_REST_LIFE_RECTANGLE_XZ_H
#define RAY_TRACING_REST_LIFE_RECTANGLE_XZ_H

#include "hittable.h"

class rectangle_xz : public hittable
{
private:
    float y;
    float x0, z0, x1, z1;
    shared_ptr<material> mat;
public:
    rectangle_xz(float x0, float z0, float x1, float z1, float y, shared_ptr<material> mat): x0(x0), x1(x1), z0(z0), z1(z1), y(y), mat(mat) {};
    bool hit(const ray &r, float tmin, float tmax, hit_record &rec) const override;
    aabb get_aabb() override;
};


#endif //RAY_TRACING_REST_LIFE_RECTANGLE_XZ_H
