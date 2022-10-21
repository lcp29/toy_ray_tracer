//
// Created by helmholtz on 2022/8/31.
//

#include "cuboid.h"

using std::make_shared;

cuboid::cuboid(const vec3 &c0, const vec3 &c1, shared_ptr<material> mat) : mat(mat)
{
    _c0 = {fmin(c0.x(), c1.x()), fmin(c0.y(), c1.y()), fmin(c0.z(), c1.z())};
    _c1 = {fmax(c0.x(), c1.x()), fmax(c0.y(), c1.y()), fmax(c0.z(), c1.z())};
    surfaces.add(make_shared<rectangle_xy>(_c0.x(), _c0.y(), _c1.x(), _c1.y(), _c0.z(), mat));
    surfaces.add(make_shared<rectangle_xy>(_c0.x(), _c0.y(), _c1.x(), _c1.y(), _c1.z(), mat));
    surfaces.add(make_shared<rectangle_yz>(_c0.y(), _c0.z(), _c1.y(), _c1.z(), _c0.x(), mat));
    surfaces.add(make_shared<rectangle_yz>(_c0.y(), _c0.z(), _c1.y(), _c1.z(), _c1.x(), mat));
    surfaces.add(make_shared<rectangle_xz>(_c0.x(), _c0.z(), _c1.x(), _c1.z(), _c0.y(), mat));
    surfaces.add(make_shared<rectangle_xz>(_c0.x(), _c0.z(), _c1.x(), _c1.z(), _c1.y(), mat));
}

bool cuboid::hit(const ray &r, float tmin, float tmax, hit_record &rec) const
{
    bool h = surfaces.hit(r, tmin, tmax, rec);
    if (!h) return false;
    if (r.o().x() >= _c0.x() && r.o().x() <= _c1.x() &&
        r.o().y() >= _c0.y() && r.o().y() <= _c1.y() &&
        r.o().z() >= _c0.z() && r.o().z() <= _c1.z())
    {
        rec.from_inside = true;
        rec.normal = -rec.normal;
    }
    return true;
}

aabb cuboid::get_aabb()
{
    return {_c0, _c1};
}
