/*
 * FoCG_3_Ray_Tracer.cpp
 * 
 * �������
 */

#include "RayTracer.h"
#include <iostream>
#include <string>
#include <SDL2/sdl.h>
#include <eigen3/Eigen/Eigen>
#include <cmath>

int f2i(double f)
{
	int i = f / 20 * 255;
	if (i > 255) i = 255;
	return i;
}

int main(int argc, char* argv[])
{
	std::ios::sync_with_stdio(false);
	Sphere s(Eigen::Vector3d(-1.2, -1, -8), 1);
	Sphere s2(Eigen::Vector3d(1, -1, -8.5), 1);
	Sphere s3(Eigen::Vector3d(0, -100000, 0), 99993);
	Texture t;
	t.p = 700;
	t.setKa(RGB(1, 0.5, 0.5));
	t.setKs(RGB(10, 5, 5));
	t.setKd(RGB(10, 5, 5));
	s.texture = t;
	t.p = 200;
	t.setKa(RGB(0.5, 1, 0.5));
	t.setKs(RGB(5, 10, 5));
	t.setKd(RGB(5, 10, 5));
	s2.texture = t;
	t.p = 10;
	t.setKa(RGB(4, 4, 4));
	t.setKs(RGB(3, 3, 3));
	t.setKd(RGB(3, 3, 3));
	s3.texture = t;
	RayTracer rt;
	PointLight ptl(Eigen::Vector3d(2, 5, -6), RGB(1.5, 1.5, 1.5));
	PointLight ptl2(Eigen::Vector3d(-2, 2.5, -7), RGB(2, 2, 2));
	rt.addPtls(ptl);
	rt.addPtls(ptl2);
	rt.addSurface(s);
	rt.addSurface(s2);
	rt.addSurface(s3);
	rt.draw();
	SDL_Window* win = nullptr;
	SDL_Renderer* renderer = nullptr;
	SDL_CreateWindowAndRenderer(640, 480, 0, &win, &renderer);
	SDL_SetRenderDrawColor(renderer, 0, 0, 0, 0);
	SDL_RenderClear(renderer);
	for(int i = 0;i < 640;i++)
		for (int j = 0; j < 480; j++)
		{
			RGB pixel = rt.getPixel(i, 480 - j);
			SDL_SetRenderDrawColor(renderer, f2i(pixel.r), f2i(pixel.g), f2i(pixel.b), 1);
			SDL_RenderDrawPoint(renderer, i, j);
		}
	SDL_RenderPresent(renderer);
	bool quit = false;
	SDL_Event e;
	while (!quit)
		if (SDL_PollEvent(&e) != 0)
			if (e.type == SDL_QUIT)
				quit = true;
	SDL_DestroyWindow(win);
	SDL_Quit();
	SDL_Quit();
	return 0;
}
