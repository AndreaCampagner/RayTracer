#include "Material.h"
const glm::dvec3 Material::getKd(double u, double v) const {
	if (textured) return texture->operator()(u, v);
	return kd;
}
