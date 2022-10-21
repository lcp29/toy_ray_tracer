//
// Created by helmholtz on 2022/8/31.
//

#include "rectangle_yz.h"

bool rectangle_yz::hit(const ray &r, float tmin, float tmax, hit_record &rec) const
{
    auto t = (x - r.o().x()) / r.d().x();
    if (t < tmin || t > tmax)
        return false;
    auto p = r.at(t);
    if (p.y() >= y0 && p.y() <= y1 && p.z() >= z0 && p.z() <= z1)
    {
        rec.p = p;
        rec.mat = mat;
        rec.from_inside = false;
        rec.t = t;
        if (r.d().dot({1, 0, 0}) < 0)
            rec.normal = {1, 0, 0};
        else
            rec.normal = {-1, 0, 0};
        return true;
    }
    return false;
}

aabb rectangle_yz::get_aabb()
{
    return aabb(vec3(x - 0.0001, y0, z0), vec3(x + 0.0001, y0, z0));
}
