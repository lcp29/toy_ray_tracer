//
// Created by helmholtz on 2022/8/31.
//

#ifndef RAY_TRACING_REST_LIFE_TRANSLATION_H
#define RAY_TRACING_REST_LIFE_TRANSLATION_H

#include "hittable.h"

class translation : public hittable
{
private:
    shared_ptr<hittable> obj;
    vec3 trans;
public:
    translation(const vec3 &trans, shared_ptr<hittable> obj): trans(trans), obj(obj) {};
    bool hit(const ray &r, float tmin, float tmax, hit_record &rec) const override;
    aabb get_aabb() override;
};


#endif //RAY_TRACING_REST_LIFE_TRANSLATION_H
