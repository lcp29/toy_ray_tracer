#pragma once

#include "Surface.h"
#include <cmath>

class Sphere : public Surface
{
public:
	Eigen::Vector3d cent_pos;
	double radius;

	Sphere(const Eigen::Vector3d& c, double r);
	Sphere(const Sphere& s);
	Sphere();
	bool hit(const Ray& ray, bool cal_int, Eigen::Vector3d& pos, Eigen::Vector3d& norm, double& t);
};
