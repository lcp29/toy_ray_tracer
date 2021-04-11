#pragma once

#include "Ray.h"
#include "Texture.h"
#include <eigen3/Eigen/Eigen>

class Surface
{
public:
	Texture texture;
	virtual bool hit(const Ray &ray, bool cal_int, Eigen::Vector3d &pos, Eigen::Vector3d &norm, double& t) = 0;
};
