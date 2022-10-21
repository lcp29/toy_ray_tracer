//
// Created by helmholtz on 2022/8/31.
//

#include "rectangle_xy.h"

bool rectangle_xy::hit(const ray &r, float tmin, float tmax, hit_record &rec) const
{
    auto t = (z - r.o().z()) / r.d().z();
    if (t < tmin || t > tmax)
        return false;
    auto p = r.at(t);
    if (p.x() >= x0 && p.x() <= x1 && p.y() >= y0 && p.y() <= y1)
    {
        rec.p = p;
        rec.mat = mat;
        rec.from_inside = false;
        rec.t = t;
        if (r.d().dot({0, 0, 1}) < 0)
            rec.normal = {0, 0, 1};
        else
            rec.normal = {0, 0, -1};
        return true;
    }
    return false;
}

aabb rectangle_xy::get_aabb()
{
    return aabb(vec3(x0, y0, z - 0.0001), vec3(x1, y1, z + 0.0001));
}
