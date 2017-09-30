#include "Triangle.h"

bool Triangle::intersect(Ray& ray, Point& p)
{
	glm::dvec3 pvec = glm::cross(
		glm::dvec3(ray.direction),
		glm::dvec3(p3 - p1)
	);
	double det = glm::dot(glm::dvec3(p2 - p1), pvec);
	if (det == 0.0) return false;
	double invDet = 1.0 / det;

	glm::dvec3 tvec = ray.origin - p1;
	
	double u = glm::dot(tvec, pvec) * invDet;
	if (u < 0 || u > 1) return false;
	

	glm::dvec3 qvec = glm::cross(
		tvec,
		glm::dvec3(p2 - p1)
	);
	double v = glm::dot(glm::dvec3(ray.direction), qvec) * invDet;
	if (v < 0 || u + v > 1) return false;

	double t = invDet * glm::dot(
		glm::dvec3(p3 - p1),
		qvec
	);
	if (t < 0) return false;
	glm::dvec4 coord = ray.origin + t*ray.direction;

	double up = (1 - u - v)*u1 + u*u2 + v*u3;
	double vp = (1 - u - v)*v1 + u*v2 + v*v3;
	p.setCoord(coord);
	p.setU(up);
	p.setV(vp);
	p.setNormal(normal(coord));
	p.setM(material);
	return true;
}

glm::dvec4 Triangle::normal(glm::dvec4 point)
{
	return n;
}

void Triangle::apply(glm::dmat4 transform)
{
	p1 = transform*p1;
	p2 = transform*p2;
	p3 = transform*p3;
	glm::dmat4 norm = glm::transpose(glm::inverse(transform));
	n = norm*n;
}

Point Triangle::point()
{
	std::random_device rd;
	std::mt19937 gen(rd());
	std::uniform_real_distribution<> xs(0,1);
	double a = xs(gen);
	double max = 1 - a;
	double b = xs(gen)*max;
	double c = 1 - a - b;
	glm::dvec4 coord = a*p1 + b*p2 + c*p3;
	return Point(coord,n,material);
}

