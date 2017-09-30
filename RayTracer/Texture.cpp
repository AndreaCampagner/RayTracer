#include "Texture.h"
#include <iostream>

const glm::dvec3 Texture::operator()(double u, double v) const
{
	double w = (u * (double) width);
	double h = v * (double) height;
	int index = (int)h*width + w;
	return image[index]*glm::dvec3(1.0/255,1.0/255,1.0/255);
}
