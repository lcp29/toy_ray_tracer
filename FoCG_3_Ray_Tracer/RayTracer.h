#pragma once

#include "Surface.h"
#include "Ray.h"
#include "RGB.h"
#include "Texture.h"
#include "PointLight.h"
#include "Sphere.h"
#include <vector>
#include <iostream>
#include <cmath>
#include <eigen3/Eigen/Eigen>
#include <limits>

#define ENABLE_DIFFUSE 1
#define ENABLE_SPECULAR 1<<1
#define ENABLE_AMBIENT 1<<2
#define ENABLE_SHADOW 1<<3
#define ENABLE_MIRROR 1<<4

#define SX 1280
#define SY 960

constexpr double epsilon = 1e-8;

class RayTracer
{
	// 视口固定，分辨率SXxSY，轴对应u->y, v->x, w->-z，d = 0.1, fovX = 90度
public:
	RayTracer();
	~RayTracer();
	void draw();
	RGB render(const Ray& ray);
	RGB render_nomirror(const Ray& r, Eigen::Vector3d& pos, Eigen::Vector3d& nor, Texture& t);
	void addSurface(const Sphere& s);
	void addPtls(const PointLight& p);
	unsigned enbflag;
	RGB getPixel(int x, int y);
	RGB Ia;
	void setCamera(const Eigen::Vector3d& e, const Eigen::Vector3d& u, const Eigen::Vector3d& v);
private:
	Eigen::Vector3d e, u, v;		//相机属性
	RGB* vbuf[SX];	               // 屏幕像素SXxSY
	std::vector<Surface*> surfaces; // 待渲染图元
	std::vector<PointLight> ptls;  // 点光源
	double dimco;				   // 亮度归一化系数
	double l, b;				   // left, bottom
	RGB bgcolor;
	Ray genRay(Eigen::Vector3d e, Eigen::Vector3d v, Eigen::Vector3d w, int i, int j);
	bool hit(const Ray& r, bool cal_int, Eigen::Vector3d& pos, Eigen::Vector3d& norm, Texture& te);
};

