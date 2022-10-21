//
// Created by helmholtz on 2022/9/3.
//

#ifndef RAY_TRACING_REST_LIFE_ROTATION_Y_H
#define RAY_TRACING_REST_LIFE_ROTATION_Y_H

#include "hittable.h"

class rotation_y : public hittable
{
private:
    float angle;
    float cos_angle, sin_angle;
    float axis_x, axis_z;
public:
    rotation_y(float angle, float ax, float az): angle(angle), axis_x(ax), axis_z(az)
    {
        cos_angle = cos(angle);
        sin_angle = sin(angle);
    };
    bool hit(const ray &r, float tmin, float tmax, hit_record &rec) const override;
    aabb get_aabb() override;
};


#endif //RAY_TRACING_REST_LIFE_ROTATION_Y_H
