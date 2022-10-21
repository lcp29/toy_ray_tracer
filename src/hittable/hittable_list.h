//
// Created by helmholtz on 2022/8/29.
//

#ifndef RAY_TRACING_REST_LIFE_HITTABLE_LIST_H
#define RAY_TRACING_REST_LIFE_HITTABLE_LIST_H

#include "hittable.h"
#include <vector>
#include <limits>

using std::vector;

class hittable_list : public hittable
{
private:
    vector<shared_ptr<hittable>> hittables;
public:
    bool hit(const ray &r, float tmin, float tmax, hit_record &rec) const override;
    void add(shared_ptr<hittable> h) { hittables.push_back(h); };
    aabb get_aabb() override;
    vector<shared_ptr<hittable>>& get_objects() { return hittables; };
};


#endif //RAY_TRACING_REST_LIFE_HITTABLE_LIST_H
