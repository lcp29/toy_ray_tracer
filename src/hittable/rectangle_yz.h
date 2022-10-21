//
// Created by helmholtz on 2022/8/31.
//

#ifndef RAY_TRACING_REST_LIFE_RECTANGLE_YZ_H
#define RAY_TRACING_REST_LIFE_RECTANGLE_YZ_H


#include "hittable.h"

class rectangle_yz : public hittable
{
private:
    float x;
    float y0, z0, y1, z1;
    shared_ptr<material> mat;
public:
    rectangle_yz(float y0, float z0, float y1, float z1, float x, shared_ptr<material> mat): y0(y0), y1(y1), z0(z0), z1(z1), x(x), mat(mat) {};
    bool hit(const ray &r, float tmin, float tmax, hit_record &rec) const override;
    aabb get_aabb() override;
};


#endif //RAY_TRACING_REST_LIFE_RECTANGLE_YZ_H
