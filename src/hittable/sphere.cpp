//
// Created by helmholtz on 2022/8/29.
//

#include "sphere.h"

bool sphere::hit(const ray &r, float tmin, float tmax, hit_record &rec) const
{
    auto a = r.d().length_squared();
    auto b = 2 * (r.o() - position).dot(r.d());
    auto c = (r.o() - position).length_squared() - radius * radius;
    auto d = b*b - 4*a*c;
    if (d < 0)
        return false;
    auto center = -b / (2*a);
    auto t = sqrt(d) / (2*a);
    auto t1 = center - t;
    if (t1 >= tmin && t1 <= tmax)
    {
        rec.p = r.at(t1);
        rec.normal = (rec.p - position).normalize();
        rec.mat = mat;
        rec.t = t1;
        rec.from_inside = (rec.normal.dot(r.d()) > 0);
        return true;
    }
    auto t2 = center + t;
    if (t2 >= tmin && t2 <= tmax)
    {
        rec.p = r.at(t2);
        rec.normal = (rec.p - position).normalize();
        rec.mat = mat;
        rec.t = t2;
        rec.from_inside = (rec.normal.dot(r.d()) > 0);
        return true;
    }
    return false;
}

aabb sphere::get_aabb()
{
    return aabb(position - vec3(radius, radius,radius), position + vec3(radius, radius, radius));
}
