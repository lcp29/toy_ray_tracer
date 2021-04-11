#pragma once
#include "Surface.h"
#include "Ray.h"
#include "RGB.h"
#include "Texture.h"
#include "PointLight.h"
#include <vector>
#include <eigen3/Eigen/Eigen>
#include <limits>

class RayTracer
{
	// 视口固定，分辨率640x480，轴对应u->y, v->x, w->-z，d = 0.1, fovX = 90度
public:
	RayTracer();
	~RayTracer();
	void draw();
	void addSurface(const Surface& s);
	void addPtls(const PointLight& p);
private:
	RGB* vbuf[640];	               // 屏幕像素640*480
	std::vector<Surface> surfaces; // 待渲染图元
	std::vector<PointLight> ptls;  // 点光源
	double dimco;				   // 亮度归一化系数
	Eigen::Vector3d d;			   // 交点到视口平面距离
	double l, b;				   // left, bottom
	RGB bgcolor;
	Ray genRay(int i, int j);
	bool hit(const Ray& r, bool cal_int, Eigen::Vector3d& pos, Eigen::Vector3d& norm, Texture& te);
};

