#pragma once
#include <glm/glm.hpp>

struct Ray {
	glm::dvec4 origin;
	glm::dvec4 direction;

	Ray(glm::dvec3 o): Ray(o, glm::dvec3(0,0,0)){}
	Ray(glm::dvec3 o, glm::dvec3 d) : origin(glm::dvec4(o, 1)),
									direction(glm::dvec4(d, 0)) 
	{  }
	Ray(glm::dvec4 o, glm::dvec4 d) : origin(o), direction(d){}
};
