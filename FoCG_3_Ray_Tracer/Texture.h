#pragma once

#include "RGB.h"

class Texture
{
public:
	RGB kd, ks, ka, km;
	int p;
	double scat;
};

