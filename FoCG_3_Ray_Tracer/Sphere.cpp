#include "Sphere.h"

Sphere::Sphere(const Eigen::Vector3d& c, double r) :
	cent_pos(c),
	radius(r)
{}

Sphere::Sphere(const Sphere& s)
{
	texture = s.texture;
	cent_pos = s.cent_pos;
	radius = s.radius;
}

Sphere::Sphere()
{}

bool Sphere::hit(const Ray& ray, bool cal_int, Eigen::Vector3d& pos, Eigen::Vector3d& norm, double& t)
{
	// 解二次方程法
	double a = ray.direction.dot(ray.direction);
	double b = 2 * ray.direction.dot(ray.start - cent_pos);
	double c = (ray.start - cent_pos).dot(ray.start - cent_pos) - radius * radius;
	double delta = b * b - 4 * a * c;
	if (delta < 0 || (c / a > 0 && b / a > 0))
		return false;
	if (cal_int == false)
		return true;
	double sd = sqrtl(delta);
	double t1 = -(b + sd) / (2 * a);
	double t2 = (sd - b) / (2 * a);
	// 取最小根
	double tmin;
	if (t1 < 0)
		tmin = t2;
	else if (t2 < 0)
		tmin = t1;
	else if (t1 < t2)
		tmin = t1;
	else
		tmin = t2;
	pos = ray.start + tmin * ray.direction;
	norm = (pos - cent_pos).normalized();
	t = tmin;
	return true;
}
