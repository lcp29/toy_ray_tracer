//
// Created by helmholtz on 2022/8/31.
//

#ifndef RAY_TRACING_REST_LIFE_CUBOID_H
#define RAY_TRACING_REST_LIFE_CUBOID_H

#include "hittable.h"
#include "hittable_list.h"
#include "rectangle_xy.h"
#include "rectangle_xz.h"
#include "rectangle_yz.h"

class cuboid : public hittable
{
private:
    vec3 _c0, _c1;
    hittable_list surfaces;
    shared_ptr<material> mat;
public:
    cuboid(const vec3 &c0, const vec3 &c1, shared_ptr<material> mat);
    bool hit(const ray &r, float tmin, float tmax, hit_record &rec) const override;
    aabb get_aabb() override;
};


#endif //RAY_TRACING_REST_LIFE_CUBOID_H
