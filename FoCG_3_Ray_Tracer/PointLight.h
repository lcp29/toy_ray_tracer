#pragma once

#include "RGB.h"
#include <eigen3/Eigen/Eigen>

class PointLight
{
public:
	PointLight();
	PointLight(const Eigen::Vector3d& v, const RGB& l);
	Eigen::Vector3d pos;
	RGB getLum(const Eigen::Vector3d& target);
	RGB luminance;
};
