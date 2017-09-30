#pragma once
#include <glm\glm.hpp>
#include "Material.h"
#include "Ray.h"
#include "Point.h"
#include <cmath>

class Shape {
protected:
	Material* material;
	Shape(Material* m) : material(m) {};
	virtual glm::dvec4 normal(glm::dvec4 p) = 0;
public:
	virtual bool intersect(Ray& ray, Point& p) = 0;
	virtual void apply(glm::dmat4) = 0;
	virtual Point point() = 0;
	virtual bool isLight();
};
