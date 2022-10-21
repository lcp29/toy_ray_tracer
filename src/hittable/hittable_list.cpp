//
// Created by helmholtz on 2022/8/29.
//

#include "hittable_list.h"

using std::numeric_limits;

bool hittable_list::hit(const ray &r, float tmin, float tmax, hit_record &rec) const
{
    hit_record final_rec;
    bool if_hit = false;
    for (auto &h : hittables)
    {
        if(h->hit(r, tmin, tmax, rec))
        {
            tmax = rec.t;
            if_hit = true;
        }
    }
    return if_hit;
}

aabb hittable_list::get_aabb()
{
    float float_min = numeric_limits<float>::min();
    float float_max = numeric_limits<float>::max();
    aabb box({float_max, float_max, float_max}, {float_min, float_min, float_min});
    bool available = false;
    for (auto &h : hittables)
    {
        if (!available)
        {
            box = h->get_aabb();
            available = true;
            continue;
        }
        aabb t = h->get_aabb();
        box = aabb::merge(box, t);
    }
    return box;
}
