#include "RayTracer.h"

RayTracer::RayTracer()
{
	for (int i = 0; i < SX; i++)
		vbuf[i] = new RGB[SY];
	dimco = 1;
	l = -0.1;
	b = -0.075;
	bgcolor = RGB(0, 0, 0);
	enbflag = ENABLE_AMBIENT | ENABLE_DIFFUSE | ENABLE_SPECULAR | ENABLE_SHADOW | ENABLE_MIRROR;
	Ia = RGB(1.5, 1.5, 1.5);
	e = Eigen::Vector3d(0, 0, 0);
	u = Eigen::Vector3d(1, 0, 0);
	v = Eigen::Vector3d(0, 1, 0);
}

RayTracer::~RayTracer()
{
	for (int i = 0; i < SX; i++)
		delete[] vbuf[i];
	for (auto i = surfaces.begin(); i != surfaces.end(); i++)
		delete (*i);
}

void RayTracer::draw()
{
	#pragma omp parallel for
	for (int i = 0; i < SX; i++)
	{
		for (int j = 0; j < SY; j++)
		{
			Ray r = genRay(e, v, u, i, j);
			vbuf[i][j] = render(r);
		}
	}
}

RGB RayTracer::render(const Ray& r)
{
	Eigen::Vector3d pos, nor;
	Texture t, t2;
	RGB pixel = render_nomirror(r, pos, nor, t);
	if (enbflag & ENABLE_MIRROR && pos[0] != std::numeric_limits<double>::infinity() && (t.km.r != 0 || t.km.g != 0 || t.km.b != 0))
	{
		Eigen::Vector3d dir = r.direction - 2 * nor * nor.dot(r.direction);
		Ray refl(pos + epsilon * dir, dir);
		RGB refintensity = render_nomirror(refl, pos, nor, t2);
		pixel = pixel + t.km * refintensity;
	}
	return pixel;
}

RGB RayTracer::render_nomirror(const Ray& r, Eigen::Vector3d& pos, Eigen::Vector3d& nor, Texture& t)	//res: 存储击中点和法线
{
	Eigen::Vector3d pos_int, norm;
	Texture te;
	RGB pixel(0, 0, 0);
	if (!hit(r, true, pos_int, norm, te))
	{
		pos[0] = std::numeric_limits<double>::infinity();
		return bgcolor;
	}
	if (enbflag & ENABLE_AMBIENT)
	{
		//std::cout << "aaa" << std::endl;
		pixel = pixel + te.ka + Ia;
	}
	if ((enbflag & ENABLE_DIFFUSE) || (enbflag & ENABLE_SPECULAR) || (enbflag & ENABLE_SHADOW))
	{
		for (auto k = ptls.begin(); k != ptls.end(); k++)
		{
			if (enbflag & ENABLE_SHADOW)
			{
				Eigen::Vector3d tmpv;
				Texture tmpt;
				Eigen::Vector3d new_d = k->pos - pos_int;
				Eigen::Vector3d new_s = pos_int + epsilon * new_d;
				Ray sray(new_s, new_d);
				if (hit(sray, false, tmpv, tmpv, tmpt)) continue;
			}
			Eigen::Vector3d l = (k->pos - pos_int).normalized();
			if (enbflag & ENABLE_DIFFUSE)
			{
				RGB lum = k->getLum(pos_int);
				double m = l.dot(norm);
				if (m < 0) m = 0;
				pixel = pixel + te.kd * lum * m;
			}
			if (enbflag & ENABLE_SPECULAR)
			{
				Eigen::Vector3d v = (-pos_int).normalized();
				Eigen::Vector3d h = (v + l).normalized();
				double nhp = std::powl(norm.dot(h), te.p);
				if (nhp < 0) nhp = 0;
				pixel = pixel + nhp * te.ks;
			}
		}
	}
	pos = pos_int;
	nor = norm;
	t = te;
	return pixel;
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

void RayTracer::setCamera(const Eigen::Vector3d& e, const Eigen::Vector3d& u, const Eigen::Vector3d& v)
{
	this->e = e;
	this->u = u;
	this->v = v;
}

Ray RayTracer::genRay(Eigen::Vector3d e, Eigen::Vector3d v, Eigen::Vector3d u, int i, int j)
{
	u.normalize();
	v.normalize();
	Eigen::Vector3d w = u.cross(v);
	w.normalize();
	return Ray(e,
		-w * 0.1 +
		u * (l + 0.2 / SX * (i + 0.5)) +
		v * (b + (0.15 / SY * (j + 0.5))));
}

bool RayTracer::hit(const Ray& r, bool cal_int, Eigen::Vector3d& pos, Eigen::Vector3d& norm, Texture& te)
{
	double tmin = std::numeric_limits<double>::infinity();
	bool is_hit = false;
	for (auto k = surfaces.begin(); k != surfaces.end(); k++)
	{
		double tmp;
		Eigen::Vector3d pos_int_t, norm_t;
		if ((*k)->hit(r, cal_int, pos_int_t, norm_t, tmp))
		{
			is_hit = true;
			if (tmp < tmin)
			{
				tmin = tmp;
				pos = pos_int_t;
				norm = norm_t;
				te = (*k)->texture;
			}
		}
	}
	return is_hit;
}
