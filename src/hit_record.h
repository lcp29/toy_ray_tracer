//
// Created by helmholtz on 2022/8/29.
//

#ifndef RAY_TRACING_REST_LIFE_HIT_RECORD_H
#define RAY_TRACING_REST_LIFE_HIT_RECORD_H

#include "vec3.h"
#include "material/material.h"
#include <memory>

using std::shared_ptr;

class material;

class hit_record
{
public:
    vec3 p;
    vec3 normal;
    shared_ptr<material> mat;
    bool from_inside;
    float t;
};


#endif //RAY_TRACING_REST_LIFE_HIT_RECORD_H
