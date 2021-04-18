
#include "RGB.h"

RGB RGB::operator+(const RGB& b)
{
	return RGB(this->r + b.r, this->g + b.g, this->b + b.b);;
}

RGB RGB::operator-(const RGB& b)
{
	return RGB(this->r - b.r, this->g - b.g, this->b - b.b);
}

RGB RGB::operator*(const RGB& b)
{
	return RGB(this->r * b.r, this->g * b.g, this->b * b.b);
}

RGB RGB::operator*(const double& b)
{
	return b * *this;
}

RGB RGB::operator/(const double& b)
{
	return RGB(this->r / b, this->g / b, this->b / b);
}

RGB operator*(const double& a, const RGB& b)
{
	return RGB(a * b.r, a * b.g, a * b.b);
}