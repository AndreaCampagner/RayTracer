#pragma once
#include <glm\glm.hpp>
#include "Texture.h"

struct Material {
	const glm::dvec3 ke, refl, ks, kd, refr;
	bool glossy;
	const double sh, eta, thetaGlossy;
	bool textured;
	Texture* texture;
	
public:

	Material(
		glm::dvec3 ke = glm::dvec3(0,0,0),
		glm::dvec3 refl = glm::dvec3(0, 0, 0),
		glm::dvec3 kd = glm::dvec3(0, 0, 0),
		glm::dvec3 ks = glm::dvec3(0, 0, 0),
		glm::dvec3 refr = glm::dvec3(0, 0, 0),
		double sh = 0,
		double eta = 1,
		double thetaGlossy = 0,
		Texture* texture = nullptr
	) : ke(ke), refl(refl), ks(ks), kd(kd), refr(refr), sh(sh), eta(eta),
		texture(texture), textured(false), thetaGlossy(thetaGlossy), glossy(false)
	{
		if (texture)
			textured = true;
		if (thetaGlossy > 1e-8)
			glossy = true;
	};

	const glm::dvec3 getKd(double u, double v) const;
};