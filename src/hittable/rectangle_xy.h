//
// Created by helmholtz on 2022/8/31.
//

#ifndef RAY_TRACING_REST_LIFE_RECTANGLE_XY_H
#define RAY_TRACING_REST_LIFE_RECTANGLE_XY_H


#include "hittable.h"

class rectangle_xy : public hittable
{
private:
    float z;
    float x0, y0, x1, y1;
    shared_ptr<material> mat;
public:
    rectangle_xy(float x0, float y0, float x1, float y1, float z, shared_ptr<material> mat): x0(x0), x1(x1), y0(y0), y1(y1), z(z), mat(mat) {};
    bool hit(const ray &r, float tmin, float tmax, hit_record &rec) const override;
    aabb get_aabb() override;
};


#endif //RAY_TRACING_REST_LIFE_RECTANGLE_XY_H
