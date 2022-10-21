//
// Created by helmholtz on 2022/8/29.
//

#include "camera.h"

ray camera::gen_ray(float h, float v) const
{
    return ray(position, left_bottom + h * horizontal + v * vertical - position);
}
