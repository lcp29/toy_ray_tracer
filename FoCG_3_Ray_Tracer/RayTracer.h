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
#define ENABLE_MIRROR 1<<3

class RayTracer
{
	// 视口固定，分辨率640x480，轴对应u->y, v->x, w->-z，d = 0.1, fovX = 90度
public:
	RayTracer();
	~RayTracer();
	void draw();
	void addSurface(const Sphere& s);
	void addPtls(const PointLight& p);
	unsigned enbflag;
	RGB getPixel(int x, int y);
	RGB Ia;
private:
	RGB* vbuf[640];	               // 屏幕像素640*480
	std::vector<Surface*> surfaces; // 待渲染图元
	std::vector<PointLight> ptls;  // 点光源
	double dimco;				   // 亮度归一化系数
	Eigen::Vector3d d;			   // 交点到视口平面距离
	double l, b;				   // left, bottom
	RGB bgcolor;
	Ray genRay(int i, int j);
	bool hit(const Ray& r, bool cal_int, Eigen::Vector3d& pos, Eigen::Vector3d& norm, Texture& te);
};

