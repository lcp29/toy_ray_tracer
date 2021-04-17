/*
 * FoCG_3_Ray_Tracer.cpp
 * 
 * ³ÌÐòÈë¿Ú
 */

#include "RayTracer.h"
#include <iostream>
#include <string>
#include <SDL2/SDL.h>
#include <eigen3/Eigen/Eigen>
#include <cmath>
#include <png++/png.hpp>
#include <string>

#define SDL_DRAW 1

#ifdef PNG_OUTPUT
png::image<png::rgb_pixel> image(1280, 960);
#elif SDL_DRAW
#define E 2
#endif

int f2i(double f)
{
	int i = f / 20 * 255;
	if (i > 255) i = 255;
	return i;
}

unsigned flagt = 14;

typedef struct timpack
{
	RayTracer* rt;
	SDL_Renderer* renderer;
} timpack;

Uint32 rtdraw(Uint32 interval, void* tp)
{
	RayTracer* prt = static_cast<timpack*>(tp)->rt;
	SDL_Renderer* renderer = static_cast<timpack*>(tp)->renderer;
	//if (++flagt == 16) flagt = 0;
	//prt->enbflag = flagt;
	prt->draw();
#ifdef SDL_DRAW
	SDL_SetRenderDrawColor(renderer, 0, 0, 0, 0);
	SDL_RenderClear(renderer);
#endif
	for (int i = 0; i < SX; i++)
		for (int j = 0; j < SY; j++)
		{
			RGB pixel = prt->getPixel(i, SY - j - 1);
#ifdef SDL_DRAW
			SDL_SetRenderDrawColor(renderer, f2i(pixel.r), f2i(pixel.g), f2i(pixel.b), 1);
			SDL_RenderDrawPoint(renderer, i, j);
#elif PNG_OUTPUT
			image[j][i] = png::rgb_pixel(f2i(pixel.r), f2i(pixel.g), f2i(pixel.b));
#endif
		}
#ifdef SDL_DRAW
	SDL_RenderPresent(renderer);
	std::cout << flagt << std::endl;
#elif PNG_OUTPUT
	image.write("output.png");
#endif
	return 1000;
}

int main(int argc, char* argv[])
{
#ifdef PNG_OUTPUT
	std::string offsets;
	if (argc == 2)
		offsets = argv[1];
	else
		offsets = 2;
	double E = std::stod(offsets);
#endif
	std::ios::sync_with_stdio(false);
	RayTracer rt;
	Sphere bg(Eigen::Vector3d(0, -100000, 0), 99995);
	Sphere s(Eigen::Vector3d(0.816497 + E, -4, -10.3382), 1);
	Texture t;
	t.setKm(RGB(0, 0, 0));
	t.p = 2000;
	t.setKa(RGB(1, 0.5, 0.5));
	t.setKs(RGB(10, 5, 5));
	t.setKd(RGB(10, 5, 5));
	s.texture = t;
	rt.addSurface(s);
	s.cent_pos = Eigen::Vector3d(0.298858 + E, -4, -12.27006);
	t.p = 400;
	t.setKa(RGB(1, 1, 0.5));
	t.setKs(RGB(7, 7, 5));
	t.setKd(RGB(4, 10, 5));
	s.texture = t;
	rt.addSurface(s);
	s.cent_pos = Eigen::Vector3d(-1.115355 + E, -4, -10.855841);
	t.p = 1000;
	t.setKa(RGB(0.3, 0, 2));
	t.setKs(RGB(3, 2, 10));
	t.setKd(RGB(2, 2, 10));
	s.texture = t;
	rt.addSurface(s);
	s.cent_pos = Eigen::Vector3d(0 + E, -2.36, -11.1547);
	t.p = 10;
	t.setKa(RGB(0.3, 0, 1));
	t.setKs(RGB(6, 2, 8));
	t.setKd(RGB(6, 1, 8));
	s.texture = t;
	rt.addSurface(s);
	s.cent_pos = Eigen::Vector3d(-5. + E, -5, -10);
	s.radius = 2;
	t.p = 10000;
	t.setKa(RGB(0.3, 0.3, 0.3));
	t.setKs(RGB(10, 10, 10));
	t.setKd(RGB(3, 3, 3));
	s.texture = t;
	rt.addSurface(s);
	s.cent_pos = Eigen::Vector3d(-6.28558 + E, -3.4679, -10);
	s.radius = 0.9;
	t.p = 100;
	t.setKa(RGB(0.3, 0.3, 0.3));
	t.setKs(RGB(10, 10, 10));
	t.setKd(RGB(1, 1, 1));
	s.texture = t;
	rt.addSurface(s);
	s.cent_pos = Eigen::Vector3d(-3.71442 + E, -3.4679, -10);
	rt.addSurface(s);
	s.cent_pos = Eigen::Vector3d(-5. + E, -4.4, -8.2);
	s.radius = 0.5;
	rt.addSurface(s);

	//s.cent_pos = Eigen::Vector3d(-5, -3.58578, -8.58578);
	s.radius = 0.19;
	//rt.addSurface(s);
	s.cent_pos = Eigen::Vector3d(-5.70711 + E, -3.58578, -8.77526);
	rt.addSurface(s);
	s.cent_pos = Eigen::Vector3d(-4.29289 + E, -3.58578, -8.77526);
	rt.addSurface(s);
	s.cent_pos = Eigen::Vector3d(-5.35356 + E, -4.29289, -9.38762);
	s.radius = 1.03;
	t.p = 10;
	t.setKa(RGB(0.3, 0.3, 0.3));
	t.setKs(RGB(3, 3, 3));
	t.setKd(RGB(70, 70, 70));
	s.texture = t;
	rt.addSurface(s);
	s.cent_pos = Eigen::Vector3d(-4.64644 + E, -4.29289, -9.38762);
	rt.addSurface(s);
	t.p = 10;
	t.setKa(RGB(0.5, 0.5, 0.5));
	t.setKs(RGB(3, 3, 3));
	t.setKd(RGB(3, 3, 3));
	t.setKm(RGB(2, 2, 2));
	bg.texture = t;
	PointLight ptl(Eigen::Vector3d(2, 5, -6), RGB(0.9, 0.9, 0.9));
	PointLight ptl2(Eigen::Vector3d(-2, 2.5, -7), RGB(0.9, 0.9, 0.9));
	PointLight ptl3(Eigen::Vector3d(-0.149429 + E, -3.6, -10.5970), RGB(0.9, 0.9, 0.9));
	rt.addPtls(ptl);
	rt.addPtls(ptl2);
	rt.addPtls(ptl);
	rt.addPtls(ptl2);
	//rt.addPtls(ptl3);
	rt.addSurface(bg);
	/*Sphere s(Eigen::Vector3d(-1.2, -1, -8), 1);
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
	t.setKa(RGB(1, 1, 1));
	t.setKs(RGB(3, 3, 3));
	t.setKd(RGB(3, 3, 3));
	s3.texture = t;
	PointLight ptl(Eigen::Vector3d(2, 5, -6), RGB(1.5, 1.5, 1.5));
	PointLight ptl2(Eigen::Vector3d(-2, 2.5, -7), RGB(2, 2, 2));
	rt.addPtls(ptl);
	rt.addPtls(ptl2);
	rt.addSurface(s);
	rt.addSurface(s2);
	rt.addSurface(s3);*/
	timpack tp;
	tp.rt = &rt;
#ifdef SDL_DRAW
	SDL_Window* win = nullptr;
	SDL_Renderer* renderer = nullptr;
	SDL_Init(SDL_INIT_EVERYTHING);
	SDL_CreateWindowAndRenderer(SX, SY, 0, &win, &renderer);
	tp.renderer = renderer;
#elif PNG_OUTPUT
	tp.renderer = NULL;
#endif
	rtdraw(0, &tp);
	//SDL_TimerID timerid = SDL_AddTimer(1000, rtdraw, &tp);
	//std::cout << "id: " << timerid << std::endl;
#ifdef SDL_DRAW
	bool quit = false;
	SDL_Event e;
	while (!quit)
		if (SDL_PollEvent(&e) != 0)
			if (e.type == SDL_QUIT)
				quit = true;
	SDL_DestroyWindow(win);
	SDL_Quit();
#endif
	return 0;
}
