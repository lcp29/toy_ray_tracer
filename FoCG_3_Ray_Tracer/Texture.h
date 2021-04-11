#pragma once

#include "RGB.h"

class Texture
{
public:
	RGB kd, ks, ka, km;
	int p;
	void setKa(const RGB& k) { ka = k; };
	void setKd(const RGB& k) { kd = k; };
	void setKs(const RGB& k) { ks = k; };
	void setKm(const RGB& k) { km = k; };
};

