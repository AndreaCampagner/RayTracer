#include "Point.h"

Point& Point::operator=(Point & p)
{
	this->coord = p.coord;
	this->normal = p.normal;
	this->m = p.m;
	this->u = p.u;
	this->v = p.v;
	return Point();
}

glm::dvec4 const& Point::getCoord() const
{
	return this->coord;
}

glm::dvec4 const& Point::getNormal() const
{
	return this->normal;
}

Material* const& Point::getM() const
{
	return this->m;
}

double const& Point::getU() const{
	return this->u;
}

double const& Point::getV() const {
	return this->v;
}

void Point::setCoord(glm::dvec4 coord)
{
	this->coord = coord;
}

void Point::setNormal(glm::dvec4 normal)
{
	this->normal = normal;
}

void Point::setM(Material * m)
{
	this->m = m;
}

void Point::setU(double u)
{
	this->u = u;
}

void Point::setV(double v)
{
	this->v = v;
}

void Point::apply(glm::dmat4 transform) {
	this->coord = transform*this->coord;
	glm::dmat4 normalTrans = glm::transpose(glm::inverse(transform));
	this->normal = normalTrans*this->normal;
}
