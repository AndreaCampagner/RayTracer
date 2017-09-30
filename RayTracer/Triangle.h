#pragma once
#include "Shape.h"
#include <random>

class Triangle : public Shape {
private:
	glm::dvec4 p1, p2, p3;
	glm::dvec4 n;
	double u1, v1, u2, v2, u3, v3;

public:
	Triangle(glm::dvec3 p1, glm::dvec3 p2, glm::dvec3 p3, Material *m) :
		Shape(m),
		p1(glm::dvec4(p1, 1)),
		p2(glm::dvec4(p2, 1)),
		p3(glm::dvec4(p3, 1)),
		n(glm::dvec4(glm::normalize(glm::cross((p2 - p1), (p3 - p1))),0))
	{};

	Triangle(glm::dvec3 p1, glm::dvec3 p2, glm::dvec3 p3, Material *m, double u1, double v1,
		double u2, double v2, double u3, double v3) :
		Shape(m),
		p1(glm::dvec4(p1, 1)),
		p2(glm::dvec4(p2, 1)),
		p3(glm::dvec4(p3, 1)),
		n(glm::dvec4(glm::normalize(glm::cross((p2 - p1), (p3 - p1))),0)),
		u1(u1), u2(u2), u3(u3), v1(v1), v2(v2), v3(v3)
	{};

	bool intersect(Ray& ray, Point& p) override;
	glm::dvec4 normal(glm::dvec4 point) override;
	void apply(glm::dmat4 transform) override;
	Point point() override;
};