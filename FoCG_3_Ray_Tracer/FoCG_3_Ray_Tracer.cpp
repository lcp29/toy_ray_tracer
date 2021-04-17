/*
 * FoCG_3_Ray_Tracer.cpp
 * 
 * 程序入口
 */

#include "RayTracer.h"
#include <iostream>
#include <string>
#include <SDL2/SDL.h>
#include <eigen3/Eigen/Eigen>
#include <cmath>
#include <png++/png.hpp>
#include <string>
#include <fstream>
#include <map>

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

bool getmod(std::vector<Surface*>& surfaces, std::vector<PointLight>& ptls);

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
	std::vector<Surface*> sur;
	std::vector<PointLight> ptls;
	if (!getmod(sur, ptls))
	{
		std::cout << "Error reading file \'mod.txt\'.\n" << std::endl;
		return 0;
	}
	for (auto i = sur.begin(); i != sur.end(); i++)
		rt.addSurface(*i);
	for (auto i = ptls.begin(); i != ptls.end(); i++)
		rt.addPtls(*i);
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

bool getmod(std::vector<Surface*>& surfaces, std::vector<PointLight>& ptls)
{
	std::ifstream mod;
	mod.open("mod.txt", std::ios::in);
	if (mod.fail())
	{
		std::cout << "Error: Unable to open file \'mod.txt\'." << std::endl;
		return false;
	}
	std::map<std::string, Texture> textures;
	std::string line;
	const std::string spaces{ " \t\n\r" };
	while (!mod.eof())
	{
		std::getline(mod, line);
		auto firstpos = line.find_first_not_of(spaces);
		if (line[firstpos] == '#')
			continue;
		std::stringstream liness;
		liness << line;
		line.erase(); //复用
		while (!liness.eof())
		{
			liness >> line;
			if (line == "t")
			{
				Texture t;
				liness >> line
					>> t.km.r >> t.km.g >> t.km.b
					>> t.ka.r >> t.ka.g >> t.ka.b
					>> t.ks.r >> t.ks.g >> t.ks.b
					>> t.kd.r >> t.kd.g >> t.kd.b >> t.p;
				textures[line] = t;
			}
			else if (line == "s")
			{
				liness >> line;
				if (line == "s")
				{
					Sphere* s = new Sphere;
					liness >> s->cent_pos[0] >> s->cent_pos[1] >> s->cent_pos[2]
						>> s->radius >> line;
					s->texture = textures[line];
					surfaces.push_back((Surface*)s);
				}
			}
			else if (line == "l")
			{
				PointLight ptl;
				liness >> ptl.pos[0] >> ptl.pos[1] >> ptl.pos[2]
					>> ptl.luminance.r >> ptl.luminance.g >> ptl.luminance.b;
				ptls.push_back(ptl);
			}
		}
	}
	mod.close();
	return true;
}