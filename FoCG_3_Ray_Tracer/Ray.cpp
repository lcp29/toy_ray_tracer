#include "Ray.h"

Ray::Ray(const Eigen::Vector3d& s, const Eigen::Vector3d& d):
	start(s),
	direction(d)
{}
