#pragma once
#include "Material.h"

Texture tile("texture.ppm", 1024, 1024);

Material mirror(glm::dvec3(0, 0, 0),
	glm::dvec3(1, 1, 1),
	glm::dvec3(0, 0, 0),
	glm::dvec3(1, 1, 1),
	glm::dvec3(0, 0, 0), 51.2, 0, 0.1);

Material blue(glm::dvec3(0.0, 0.0, 0.0),
	glm::dvec3(0.3, 0.3, 0.3),
	glm::dvec3(0.1, 0.1, 0.5),
	glm::dvec3(0.3, 0.3, 0.3),
	glm::dvec3(0.0, 0.0, 0.0), 51.2, 0, 0);

Material blueHalfGlossy(glm::dvec3(0.0, 0.0, 0.0),
	glm::dvec3(0.3, 0.3, 0.3),
	glm::dvec3(0.1, 0.1, 0.5),
	glm::dvec3(0.3, 0.3, 0.3),
	glm::dvec3(0.0, 0.0, 0.0), 51.2, 0, 30);

Material blueGlossy(glm::dvec3(0.0, 0.0, 0.0),
	glm::dvec3(0.3, 0.3, 0.3),
	glm::dvec3(0.1, 0.1, 0.5),
	glm::dvec3(0.3, 0.3, 0.3),
	glm::dvec3(0.0, 0.0, 0.0), 51.2, 0, 60);

Material tiled(glm::dvec3(0, 0, 0),
	glm::dvec3(0, 0, 0),
	glm::dvec3(0, 0, 0.0),
	glm::dvec3(0, 0, 0),
	glm::dvec3(0, 0, 0), 51.2, 1.5, 0.0, &tile);

Material glass(glm::dvec3(0, 0, 0),
	glm::dvec3(1, 1, 1),
	glm::dvec3(0, 0, 0.0),
	glm::dvec3(1, 1, 1),
	glm::dvec3(1, 1, 1), 51.2, 1.52);

Material tiledGlass(glm::dvec3(0, 0, 0),
	glm::dvec3(1, 1, 1),
	glm::dvec3(0, 0, 0.0),
	glm::dvec3(1, 1, 1),
	glm::dvec3(1, 1, 1), 51.2, 1.52, 0.0, &tile);

Material water(glm::dvec3(0, 0, 0),
	glm::dvec3(1, 1, 1),
	glm::dvec3(0, 0.01, 0.01),
	glm::dvec3(1, 1, 1),
	glm::dvec3(1, 1, 1), 51.2, 1.3);

Material glassGlossy(glm::dvec3(0, 0, 0),
	glm::dvec3(1, 1, 1),
	glm::dvec3(1, 1, 1),
	glm::dvec3(0, 0, 0),
	glm::dvec3(1, 1, 1), 51.2, 1.52, 60);

Material emissive(glm::dvec3(0.99, 0.99, 0.9),
	glm::dvec3(0.0, 0.0, 0.0),
	glm::dvec3(0.0, 0.0, 0.0),
	glm::dvec3(0.0, 0.0, 0.0),
	glm::dvec3(0.0, 0.0, 0.0), 1, 1);

Material redDiffuse(glm::dvec3(0.0, 0.0, 0.0),
	glm::dvec3(0.3, 0.3, 0.3),
	glm::dvec3(0.5, 0.1, 0.1),
	glm::dvec3(0.7, 0.0, 0.0),
	glm::dvec3(0.0, 0.0, 0.0), 30.5, 0, 30);
Material greenDiffuse(glm::dvec3(0.0, 0.0, 0.0),
	glm::dvec3(0.3, 0.3, 0.3),
	glm::dvec3(0.1, 0.5, 0.1),
	glm::dvec3(0, 0.7, 0),
	glm::dvec3(0.0, 0.0, 0.0), 30.5, 0, 30);
Material greyDiffuse(glm::dvec3(0.0, 0.0, 0.0),
	glm::dvec3(0.3, 0.3, 0.3),
	glm::dvec3(0.5, 0.5, 0.5),
	glm::dvec3(0.7, 0.7, 0.7),
	glm::dvec3(0.0, 0.0, 0.0), 30.5, 0, 30);

