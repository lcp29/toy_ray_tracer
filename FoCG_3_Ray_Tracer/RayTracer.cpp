#include "RayTracer.h"

RayTracer::RayTracer()
{
	for (int i = 0; i < 640; i++)
		vbuf[i] = new RGB[480];
	dimco = 1;
	d = Eigen::Vector3d(0, 0, -0.1);
	l = -0.1;
	b = -0.075;
	bgcolor = RGB(0, 0, 0);
	enbflag = ENABLE_AMBIENT | ENABLE_DIFFUSE | ENABLE_SPECULAR;
	Ia = RGB(1.5, 1.5, 1.5);
}

RayTracer::~RayTracer()
{
	for (int i = 0; i < 640; i++)
		delete[] vbuf[i];
	for (auto i = surfaces.begin(); i != surfaces.end(); i++)
		delete (*i);
}

void RayTracer::draw()
{
	for (int i = 0; i < 640; i++)
	{
		for (int j = 0; j < 480; j++)
		{
			vbuf[i][j] = bgcolor;
			Ray r = genRay(i, j);
			Eigen::Vector3d pos_int, norm;
			Texture te;
			if(!hit(r, true, pos_int, norm, te))
				continue;
			if (enbflag & ENABLE_AMBIENT)
			{
				//std::cout << "aaa" << std::endl;
				vbuf[i][j].r += te.ka.r * Ia.r;
				vbuf[i][j].g += te.ka.g * Ia.g;
				vbuf[i][j].b += te.ka.b * Ia.b;
			}
			if ((enbflag & ENABLE_DIFFUSE) || (enbflag & ENABLE_SPECULAR))
			{
				for (auto k = ptls.begin(); k != ptls.end(); k++)
				{
					Eigen::Vector3d l = (k->pos - pos_int).normalized();
					if (enbflag & ENABLE_DIFFUSE)
					{
						RGB lum = k->getLum(pos_int);
						double m = l.dot(norm);
						if (m < 0) m = 0;
						vbuf[i][j].r += te.kd.r * lum.r * m;
						vbuf[i][j].g += te.kd.g * lum.g * m;
						vbuf[i][j].b += te.kd.b * lum.b * m;
					}
					if (enbflag & ENABLE_SPECULAR)
					{
						Eigen::Vector3d v = (-pos_int).normalized();
						Eigen::Vector3d h = (v + l).normalized();
						double nhp = std::powl(norm.dot(h), te.p);
						if (nhp < 0) nhp = 0;
						vbuf[i][j].r += nhp * te.ks.r;
						vbuf[i][j].g += nhp * te.ks.g;
						vbuf[i][j].b += nhp * te.ks.b;
					}
				}
			}	
		}
	}
}

void RayTracer::addSurface(const Sphere& s)
{
	Surface* ps = new Sphere(s);
	surfaces.push_back(ps);
}

void RayTracer::addPtls(const PointLight& p)
{
	ptls.push_back(p);
}

RGB RayTracer::getPixel(int x, int y)
{
	return vbuf[x][y];
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
		is_hit = (*k)->hit(r, cal_int, pos_int_t, norm_t, tmp) || is_hit;
		if (tmp < tmin)
		{
			tmin = tmp;
			pos = pos_int_t;
			norm = norm_t;
			te = (*k)->texture;
		}
	}
	return is_hit;
}
