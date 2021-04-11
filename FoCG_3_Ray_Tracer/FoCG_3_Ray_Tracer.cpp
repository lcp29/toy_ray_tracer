/*
 * FoCG_3_Ray_Tracer.cpp
 * 
 * ³ÌÐòÈë¿Ú
 */

#include "Ray.h"
#include "Sphere.h"
#include <iostream>
#include <string>
#include <SDL2/sdl.h>
#include <eigen3/Eigen/Eigen>
#include <cmath>

int main(int argc, char* argv[])
{
	Sphere s(Eigen::Vector3d(0, 0, 0), 5);
	Ray r(Eigen::Vector3d(0, 0, 0), Eigen::Vector3d(1, 0, 0));
	Eigen::Vector3d v(0, 0, 0);
	s.hit(r, true, v, v);
	return 0;
}
