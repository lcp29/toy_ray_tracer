//
// Created by helmholtz on 2022/8/31.
//

#include "utils.h"

float random_float_0_1()
{
    return static_cast<float>(rand()) / static_cast<float>(RAND_MAX);
}

int random_int(int a, int b)
{
    return rand() % (b - a) + a;
}
