//
// Created by helmholtz on 2022/8/31.
//

#include "rectangle_xz.h"

bool rectangle_xz::hit(const ray &r, float tmin, float tmax, hit_record &rec) const
{
    auto t = (y - r.o().y()) / r.d().y();
    if (t < tmin || t > tmax)
        return false;
    auto p = r.at(t);
    if (p.x() >= x0 && p.x() <= x1 && p.z() >= z0 && p.z() <= z1)
    {
        rec.p = p;
        rec.mat = mat;
        rec.from_inside = false;
        rec.t = t;
        if (r.d().dot({0, 1, 0}) < 0)
            rec.normal = {0, 1, 0};
        else
            rec.normal = {0, -1, 0};
        return true;
    }
    return false;
}

aabb rectangle_xz::get_aabb()
{
    return aabb(vec3(x0, y - 0.0001, z0), vec3(x1, y + 0.0001, z0));
}
