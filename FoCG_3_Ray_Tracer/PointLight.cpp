#include "PointLight.h"

PointLight::PointLight()
{}

PointLight::PointLight(const Eigen::Vector3d& p, const RGB& l):
	pos(p),
	luminance(l)
{}

RGB PointLight::getLum(const Eigen::Vector3d& target)
{
	return luminance;
}
