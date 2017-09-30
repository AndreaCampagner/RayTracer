#pragma once
#include "Sphere.h"




Point Sphere::point() {
	double u = xs(gen);
	double v = xs(gen);
	double theta = 2 * M_PI * u;
	double phi = acos(2 * v - 1);
	glm::dvec4 point;
	point.x = this->center.x + (this->radius * sin(phi) * cos(theta));
	point.y = this->center.y + (this->radius * sin(phi) * sin(theta));
	point.z = this->center.z + (this->radius * cos(phi));
	point.w = 1;
	glm::dvec4 n = normal(point);
	u = 0.5 + atan2(n.z, n.x) / (2 * M_PI);
	v = 0.5 - asin(n.y) / M_PI;
	Point p (point, n, material, u, v);
	return p;
}

glm::dvec4 const& Sphere::getCenter() const
{
	return this->center;
}

double const& Sphere::getRadius() const
{
	return this->radius;
}

bool Sphere::intersect(Ray& ray, Point& p) {
	glm::dvec4 delta;
	delta.x = ray.origin.x - this->center.x;
	delta.y = ray.origin.y - this->center.y;
	delta.z = ray.origin.z - this->center.z;
	delta.w = 0;
	glm::dvec4 dir = ray.direction;
	double A = dir.x * dir.x + dir.y*dir.y + dir.z*dir.z;
	double B = 2 * (delta.x*dir.x + delta.y*dir.y + delta.z*dir.z);
	double C = (delta.x*delta.x + delta.y*delta.y + delta.z*delta.z) - this->radius*this->radius;
	double discr = B*B - 4 * A*C;
	if (discr < 0) return false;

	double s = sqrt(discr);
	double alpha1 = (-B - s) / (2 * A);
	double alpha2 = (-B + s) / (2 * A);
	double alpha = fmin(alpha1, alpha2);
	if (alpha < 0) return false;
	glm::dvec4 coord = ray.origin + alpha*ray.direction;
	Point tmp(coord, glm::dvec4(0, 0, 0, 0), nullptr);
	glm::dvec4 n = normal(coord);
	double u = 0.5 + atan2(n.z, n.x) / (2 * M_PI);
	double v = 0.5 - asin(n.y) / M_PI;
	p.setCoord(coord);
	p.setM(material);
	p.setU(u);
	p.setV(v);
	p.setNormal(n);

	return true;
}

glm::dvec4 Sphere::normal(glm::dvec4 p)
{
	glm::dvec4 n = glm::normalize(p - this->center);
	return n;
}

void Sphere::apply(glm::dmat4 transform)
{
	double sx = sqrt(transform[0][0]*transform[0][0] + transform[1][0]*transform[1][0] + transform[2][0]*transform[2][0]);
	this->radius *= sx;
	this->center = transform*this->center;
}
