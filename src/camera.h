//
// Created by helmholtz on 2022/8/29.
//

#ifndef RAY_TRACING_REST_LIFE_CAMERA_H
#define RAY_TRACING_REST_LIFE_CAMERA_H

#include <cmath>
#include "vec3.h"
#include "ray.h"

class camera
{
private:
    vec3 position;
    vec3 u, v, w;
    float _tmin, _tmax;
    vec3 left_bottom;
    vec3 horizontal;
    vec3 vertical;
public:
    camera() : position({0, 0, 0}), u({1, 0, 0}), v({0, 1, 0}),
               w({0, 0, 1}), _tmin(0.1), _tmax(1000),
               left_bottom({-0.1, -0.066666667, -0.1}),
               horizontal({0.2, 0, 0}),
               vertical({0, 0.13333333, 0})
    {};

    camera(vec3 lookfrom, vec3 lookat, vec3 top, float tmin, float tmax, float hfov, float yxratio) :
            position(lookfrom), _tmin(tmin), _tmax(tmax), v(top.normalize()), w((lookfrom - lookat).normalize())
    {
        u = v.cross(w);
        auto hsize = tmin * tan(hfov / 2);
        auto vsize = hsize * yxratio;
        left_bottom = position - tmin * w - hsize * u - vsize * v;
        horizontal = 2 * u * hsize;
        vertical = 2 * v * vsize;
    };

    ray gen_ray(float h, float v) const;

    float tmin() const { return _tmin; };

    float tmax() const { return _tmax; };
};


#endif //RAY_TRACING_REST_LIFE_CAMERA_H
