//
// Created by helmholtz on 2022/8/31.
//

#ifndef RAY_TRACING_REST_LIFE_BVH_NODE_H
#define RAY_TRACING_REST_LIFE_BVH_NODE_H

#include "hittable_list.h"
#include <limits>

class bvh_node : public hittable
{
private:
    shared_ptr<hittable> left, right;
    aabb box;
    bool aabb_valid;
public:
    explicit bvh_node(hittable_list &l): bvh_node(l.get_objects(), 0, l.get_objects().size()) {};
    bvh_node(std::vector<std::shared_ptr<hittable>> &objects, int il, int ir);
    bool hit(const ray &r, float tmin, float tmax, hit_record &rec) const override;
    aabb get_aabb() override;
};


#endif //RAY_TRACING_REST_LIFE_BVH_NODE_H
