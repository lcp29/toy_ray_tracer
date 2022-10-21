//
// Created by helmholtz on 2022/8/31.
//

#include "aabb.h"

using std::swap;

bool aabb::hit(const ray &r, float tmin, float tmax) const
{
    for (int a = 0; a < 3; ++a)
    {
        auto inv_d = 1 / r.d()[a];
        auto ta = (c0[a] - r.o()[a]) * inv_d;
        auto tb = (c1[a] - r.o()[a]) * inv_d;
        if (ta > tb)
            swap(ta, tb);
        tmin = ta > tmin ? ta : tmin;
        tmax = tb < tmax ? tb : tmax;
        if (tmin > tmax)
            return false;
    }
    return true;
}

aabb aabb::merge(const aabb &a, const aabb &b)
{
    aabb merged_box;
    merged_box.c0[0] = fmin(a.c0[0], b.c0[0]);
    merged_box.c0[1] = fmin(a.c0[1], b.c0[1]);
    merged_box.c0[2] = fmin(a.c0[2], b.c0[2]);
    merged_box.c1[0] = fmax(a.c1[0], b.c1[0]);
    merged_box.c1[1] = fmax(a.c1[1], b.c1[1]);
    merged_box.c1[2] = fmax(a.c1[2], b.c1[2]);
    return merged_box;
}
