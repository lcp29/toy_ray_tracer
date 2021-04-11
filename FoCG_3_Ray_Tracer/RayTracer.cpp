#include "RayTracer.h"

RayTracer::RayTracer()
{
	for (int i = 0; i < 640; i++)
		vbuf[i] = new RGB[480];
	dimco = 1;
	d = Eigen::Vector3d(0, 0, -0.1);
	l = -0.2;
	b = -0.075;
	bgcolor = RGB(0, 0, 0);
}

RayTracer::~RayTracer()
{
	for (int i = 0; i < 640; i++)
		delete[] vbuf[i];
}

void RayTracer::draw()
{
	for (int i = 0; i < 640; i++)
	{
		for (int j = 0; i < 480; j++)
		{
			vbuf[i][j] = bgcolor;
			Ray r = genRay(i, j);
			Eigen::Vector3d pos_int, norm;
			Texture te;
			if(!hit(r, true, pos_int, norm, te))
				continue;
			
		}
	}
}

void RayTracer::addSurface(const Surface& s)
{
	surfaces.push_back(s);
}

void RayTracer::addPtls(const PointLight& p)
{
	ptls.push_back(p);
}

Ray RayTracer::genRay(int i, int j)
{
	return Ray(Eigen::Vector3d(0, 0, 0),
		d +
		Eigen::Vector3d(l + 0.0003125 * (i + 0.5),
			b + (0.0003125 * (j + 0.5)),
			0));
}

bool RayTracer::hit(const Ray& r, bool cal_int, Eigen::Vector3d& pos, Eigen::Vector3d& norm, Texture& te)
{
	double tmin = std::numeric_limits<double>::infinity();
	bool is_hit = false;
	for (auto k = surfaces.begin(); k != surfaces.end(); k++)
	{
		double tmp;
		Eigen::Vector3d pos_int_t, norm_t;
		is_hit = is_hit || k->hit(r, cal_int, pos_int_t, norm_t, tmp);
		if (tmp < tmin)
		{
			tmin = tmp;
			pos = pos_int_t;
			norm = norm_t;
			te = k->texture;
		}
	}
	return is_hit;
}
