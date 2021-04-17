#pragma once

#include <eigen3/Eigen/Eigen>

class Ray
{
public:
	Ray();
	Ray(const Eigen::Vector3d& s, const Eigen::Vector3d& d);
	Eigen::Vector3d start;
	Eigen::Vector3d direction;
};

