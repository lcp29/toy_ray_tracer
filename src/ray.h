//
// Created by helmholtz on 2022/8/29.
//

#ifndef RAY_TRACING_REST_LIFE_RAY_H
#define RAY_TRACING_REST_LIFE_RAY_H

#include "vec3.h"

class ray
{
private:
    vec3 origin;
    vec3 direction;
public:
    ray() {};

    ray(vec3 o, vec3 d) : origin(o), direction(d)
    {};

    inline const vec3& o() const
    { return origin; };

    inline const vec3& d() const
    { return direction; };

    inline vec3 at(float t) const
    { return origin + t * direction; };

    void seto(const vec3 &o)
    { origin = o; };

    void setd(const vec3 &d)
    { direction = d; };
};


#endif //RAY_TRACING_REST_LIFE_RAY_H
