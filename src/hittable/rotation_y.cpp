//
// Created by helmholtz on 2022/9/3.
//

#include "rotation_y.h"

bool rotation_y::hit(const ray &r, float tmin, float tmax, hit_record &rec) const
{
    float rox = r.o().x() - axis_x;
    float roz = r.o().z() - axis_z;
    rox = axis_x + rox * cos_angle + roz * sin_angle;
    roz = axis_z + roz * cos_angle - rox * sin_angle;
    
    return false;
}

aabb rotation_y::get_aabb()
{
    return aabb();
}
