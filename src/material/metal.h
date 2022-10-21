//
// Created by helmholtz on 2022/8/30.
//

#ifndef RAY_TRACING_REST_LIFE_METAL_H
#define RAY_TRACING_REST_LIFE_METAL_H

#include "material.h"

class metal : public material
{
public:
    metal(color att, float fuzziness): _attenuation(att), _fuzziness(fuzziness) {};
    bool scatter(const ray &i, ray &s, const hit_record &rec, color &attenuation) override;
    color emission(const ray &i, const hit_record &rec) override { return {0, 0, 0}; };
private:
    color _attenuation;
    float _fuzziness;
};


#endif //RAY_TRACING_REST_LIFE_METAL_H
