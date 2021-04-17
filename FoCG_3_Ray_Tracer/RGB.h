#pragma once

class RGB
{
public:
	double r, g, b;
	RGB() { r = g = b = 0; };
	RGB(double r, double g, double b) : r(r), g(g), b(b) {};
	RGB operator+(const RGB& b);
	RGB operator-(const RGB& b);
	RGB operator*(const RGB& b);
	RGB operator*(const double& b);
};

RGB operator*(const double& a, const RGB& b);
