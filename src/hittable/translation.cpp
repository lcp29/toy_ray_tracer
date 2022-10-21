//
// Created by helmholtz on 2022/8/31.
//

#include "translation.h"

bool translation::hit(const ray &r, float tmin, float tmax, hit_record &rec) const
{
    bool h = obj->hit(ray(r.o() - trans, r.d()), tmin, tmax, rec);
    rec.p = rec.p + trans;
    return h;
}

aabb translation::get_aabb()
{
    return aabb(obj->get_aabb().c0 + trans, obj->get_aabb().c1 + trans);
}
