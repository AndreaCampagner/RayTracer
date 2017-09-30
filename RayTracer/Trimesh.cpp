#include "Trimesh.h"
#include <iostream>

bool Trimesh::intersect(Ray & ray, Point & p)
{
	int shape = -1;
	ray.origin = ray.origin + 0.01*ray.direction;
	for (int i = 0; i < shapes.size(); i++) {
		Point tmp;
		bool t = shapes[i]->intersect(ray, tmp);
		if (tmp.getCoord() != ray.origin) {
			if (t) {
				if (shape == -1 ||
					glm::distance(ray.origin, tmp.getCoord()) < glm::distance(ray.origin, p.getCoord())) {
					p = tmp;
					shape = i;
				}

			}
		}
	}
	if (shape == -1)
		return false;

	return true;
}

glm::dvec4 Trimesh::normal(glm::dvec4 point)
{
	return glm::dvec4();
}

void Trimesh::apply(glm::dmat4 transform)
{
	for (Triangle* shape : shapes)
		shape->apply(transform);
}

Point Trimesh::point()
{
	int i = xs(gen);
	return shapes[i]->point();
}

bool Trimesh::isLight()
{
	for (Triangle* shape : shapes)
		if (shape->isLight())
			return true;
	return false;
}