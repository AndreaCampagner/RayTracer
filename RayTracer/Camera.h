#pragma once
#include <glm\glm.hpp>
struct Camera {
	glm::dvec4 position, lookAt, up;
	double nearPlane, focalLength, apertureRadius;
	int width, height;

	Camera(glm::dvec4 p, glm::dvec4 l, glm::dvec4 u, double np, int w, int h, double fl, double ar) :
		position(p), lookAt(l), up(u), nearPlane(np), width(w), height(h), focalLength(fl), apertureRadius(ar)
	{};
};