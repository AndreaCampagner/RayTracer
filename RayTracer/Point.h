#pragma once
#include <glm\glm.hpp>
#include "Material.h"

struct Point {
private:
	glm::dvec4 coord;
	glm::dvec4 normal;
	double u, v;
	Material* m;

public:
	Point() : coord(glm::dvec4(0.0, 0.0, 0.0, 1.0)),
		normal(glm::dvec4(0.0, 0.0, 0.0, 0.0)), m(nullptr), u(0), v(0)
	{};

	Point(glm::dvec4 coord, glm::dvec4 normal, Material* m) : coord(coord),
		normal(normal), m(m), u(0), v(0)
	{};

	Point(glm::dvec4 coord, glm::dvec4 normal, Material* m, double u, double v):
		coord(coord), normal(normal), m(m), u(u), v(v)
	{};

	Point& operator=(Point& p);
	glm::dvec4 const& getCoord() const;
	glm::dvec4 const& getNormal() const;
	Material* const& getM() const;
	double const& getU() const;
	double const& getV() const;
	void setCoord(glm::dvec4 coord);
	void setNormal(glm::dvec4 normal);
	void setM(Material* m);
	void setU(double u);
	void setV(double v);
	void apply(glm::dmat4 transform);
};
