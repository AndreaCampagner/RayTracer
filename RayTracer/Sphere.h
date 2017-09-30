#pragma once
#define _USE_MATH_DEFINES
#include "Shape.h"
#include <random>

class Sphere : public Shape{
private:
	glm::dvec4 center;
	double radius;
	std::random_device rd;
	std::mt19937 gen;
	std::uniform_real_distribution<> xs;

	
public:
	glm::dvec4 const& getCenter() const;
	double const& getRadius() const;

	Sphere(glm::dvec3 c, double r, Material* m) : Shape(m), radius(r), center(glm::dvec4(c,1))
	{}

	Sphere(Material* m): radius(1), center(glm::dvec4(0,0,0,1)), Shape(m), xs(0, 1), gen(rd()) {}

	bool intersect(Ray& ray, Point& p) override;
	glm::dvec4 normal(glm::dvec4 p) override;
	void apply(glm::dmat4 transform) override;
	Point point() override;
};