#include "Shape.h"
bool Shape::isLight()
{
	return (material->ke != glm::dvec3(0.0, 0.0, 0.0));
}
