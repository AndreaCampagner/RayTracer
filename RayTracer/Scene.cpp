#pragma once
#include "Scene.h"
#include <iostream>

void Scene::cameraTransform() {

	glm::dmat4 t = glm::lookAt(
		glm::dvec3(camera.position),
		glm::dvec3(camera.lookAt),
		glm::dvec3(camera.up));

	camera.position = t*camera.position;
	for (auto s : shapes)
		s->apply(t);
}

int Scene::closestIntersection(Ray r, Point& closest) {
	int shape = -1;
	r.origin = r.origin + 0.01*r.direction;
	for (int i = 0; i < shapes.size(); i++) {
		Point p;
		bool t = shapes[i]->intersect(r, p);
		if (p.getCoord() != r.origin) {
			if (t) {
				if (shape == -1 ||
					distance(r.origin, p.getCoord()) < distance(r.origin, closest.getCoord())) {
					closest = p;
					shape = i;
				}

			}
		}
	}
	return shape;
}

void Scene::render(std::string file, int w, int h, int depth, int shadowRays, int aaRays, int glossyRays, int dofRays) {
	std::random_device rd;
	std::mt19937 gen(rd());
	glm::u8vec3* viewplane = new glm::u8vec3[w*h];
	cameraTransform();
#pragma omp parallel for schedule(dynamic)
	for (int y = 0; y < h; y++) {
		for (int x = 0; x < w; x++) {
			glm::dvec3 color(0, 0, 0);
			//Antialiasing with uniform sampling inside pixel
			for (int r = 0; r < aaRays; r++) {
				std::uniform_real_distribution<> xs(x, x + 1);
				std::uniform_real_distribution<> ys(y, y + 1);
				double x_r = xs(gen);
				double y_r = ys(gen);
				double x_c = (2 * x_r / w - 1) * camera.width / 2 * (w / h);
				double y_c = (2 * y_r / h - 1) * camera.height / 2;
				glm::dvec4 center = glm::dvec4(x_c, -y_c, camera.nearPlane, 1);

				//Compute focal point
				glm::dvec4 focal_point = camera.position +
					abs(camera.focalLength)*glm::normalize(center - camera.position);
				glm::dvec3 color_dof(0, 0, 0);

				//Depth of Field
				for (int d = 0; d < dofRays; d++) {
					std::uniform_real_distribution<> dofs(0, 1);
					double a = dofs(gen);
					double b = dofs(gen);
					if (b < a) std::swap(a, b);

					//compute point inside aperture
					double x = (b*camera.apertureRadius*cos(2 * M_PI*a / b));
					double y = b*camera.apertureRadius*sin(2 * M_PI*a / b);
					glm::dvec4 aperture_point = glm::dvec4(x, y, camera.position.z, 1);
					Ray ray = Ray(aperture_point, glm::normalize(focal_point - aperture_point));
					glm::u8vec3 color_tmp = trace(ray, 0, depth, shadowRays, glossyRays);
					color_dof += color_tmp;
				}
				color_dof /= dofRays;
				color += color_dof;
				//}
			}
			color /= (aaRays);
			viewplane[y*w + x] = (glm::u8vec3) color;
		}
	}

	//save image
	std::ofstream f;
	f.open(file);
	f << "P3\n" << w << " " << h << "\n255\n";
	for (int i = 0; i < w*h; i++)
		f << (int)viewplane[i][0] << " " << (int)viewplane[i][1] << " " << (int)viewplane[i][2] << " ";
	f.close();
}

glm::dvec3 Scene::inLight(Point p, Point q, int l) {
	Ray r(p.getCoord(), q.getCoord() - p.getCoord());
	r.origin = r.origin + 0.01*r.direction;
	double distLight = distance(p.getCoord(), q.getCoord());
	glm::dvec3 attenuation(1, 1, 1);
	for (int i = 0; i < shapes.size(); i++) {
		if (i != l) {
			Point objInt;
			bool inter = shapes[i]->intersect(r, objInt);
			if (inter && distance(p.getCoord(), objInt.getCoord()) < distLight) {
				attenuation *= objInt.getM()->refr;
			}
		}
	}
	return attenuation;
}

double Scene::distance(glm::dvec4 p1, glm::dvec4 p2) {
	double dist = glm::sqrt((p2[1] - p1[1])*(p2[1] - p1[1]) +
		(p2[2] - p1[2])*(p2[2] - p1[2]) +
		(p2[3] - p1[3])*(p2[3] - p1[3]));
	return dist;
}

glm::u8vec3 Scene::trace(Ray ray, int depth, int maxDepth, int shadowRays, int glossyRays)
{
	Point p;
	int shape = closestIntersection(ray, p);
	if (shape < 0) return glm::u8vec3(0, 0, 0);


	glm::u16vec3 color = glm::u16vec3(0, 0, 0);
	glm::dvec3 Ie = glm::dvec3(255, 255, 255);
	color += (glm::u16vec3) (Ie * p.getM()->ke);

	//local lighting
	for (int l = 0; l < shapes.size(); l++) {
		if ((*shapes[l]).isLight()) {
			glm::dvec3 tmp_color(0, 0, 0);
			for (int r = 0; r < shadowRays; r++) {
				Point q = (*shapes[l]).point();
				glm::dvec4 ln = glm::normalize(q.getCoord() - p.getCoord());
				glm::dvec3 attenuation = inLight(p, q, l);
				glm::dvec4 v = glm::normalize(ray.origin - p.getCoord());
				glm::dvec4 n = p.getNormal();

				glm::dvec4 R = 2 * glm::dot(ln, n)*n - ln;
				R = glm::normalize(R);
				double cosAlpha = pow(fmax(0, glm::dot(R, v)), p.getM()->sh);
				double cosTheta = fmax(0, glm::dot(n, ln));

				glm::dvec3 lightIe = glm::dvec3(255, 255, 255);
				lightIe *= (q.getM()->ke*attenuation);
				tmp_color += (glm::u16vec3) ((lightIe * p.getM()->ks)*cosAlpha);
				tmp_color +=
					(glm::u16vec3) ((lightIe * p.getM()->getKd(p.getU(), p.getV()))*cosTheta);
			}
			tmp_color /= shadowRays;
			color += (glm::u16vec3) tmp_color;
		}
	}

	//global lighting
	if (depth < maxDepth) {
		//parameters for refraction
		double cosi = glm::dot(ray.direction, p.getNormal());
		if (cosi <= -1)
			cosi = -1;
		else if (cosi >= 1)
			cosi = 1;
		double etai = 1, etat = p.getM()->eta;
		glm::dvec4 n(p.getNormal());
		if (cosi < 0) { cosi = -cosi; }
		else { std::swap(etai, etat); n = -p.getNormal(); }
		double eta = etai / etat;
		double k = 1 - eta * eta * (1 - cosi * cosi);

		//Schlick
		double R0 = pow((etai - etat) / (etai + etat), 2);
		double RTheta = R0 + (1 - R0)*pow((1 - cosi), 5);

		glm::dvec4 refrDir = k < 0 ? glm::dvec4(0, 0, 0, 0) : (ray.direction * eta) + n*(eta * cosi - sqrt(k));
		glm::dvec4 reflDir = ray.direction - 2.0*p.getNormal()*glm::dot(ray.direction, p.getNormal());
		glm::normalize(reflDir);
		glm::dvec3 tmpCol(0, 0, 0);

		//Reflection
		std::uniform_real_distribution<double> zs(cos(p.getM()->thetaGlossy*M_PI/180), 1);
		std::uniform_real_distribution<double> phis(0, 2 * M_PI);
		for (int nRays = 0; nRays < glossyRays; nRays++) {
			Ray reflRay(p.getCoord(), reflDir);
			if (p.getM()->glossy) {
				//Sample over sphere for glossiness
				double z = zs(gen);
				double phi = phis(gen);
				glm::dvec4 glossyDir(sqrt(1 - z*z)*cos(phi), sqrt(1 - z*z)*sin(phi), z, 0);

				//Rotate north pole
				glm::dvec3 rotationDir = glm::cross(glm::dvec3(0, 0, 1), glm::dvec3(reflDir));
				glossyDir = glm::dvec4(
					glm::rotate(glm::dvec3(glossyDir),
						acos(glm::dot(reflDir, glm::dvec4(0, 0, 1, 0))),
						rotationDir), 0);
				glossyDir = glm::normalize(glossyDir);
				
				reflRay = Ray(p.getCoord(), glossyDir);
			}
			tmpCol += trace(reflRay, depth + 1, maxDepth, shadowRays, glossyRays);
		}
		tmpCol /= glossyRays;
		glm::dvec3 dcolor = RTheta*(((glm::dvec3) tmpCol) * p.getM()->refl);

		//Refraction
		if (RTheta < 1) {

			if (refrDir != glm::dvec4(0, 0, 0, 0)) {
				refrDir = glm::normalize(refrDir);
				Ray refrRay(p.getCoord(), refrDir);
				glm::u8vec3 tmpCol = trace(refrRay, depth + 1, maxDepth, shadowRays, glossyRays);
				dcolor += (1 - RTheta)*(((glm::dvec3) tmpCol) * p.getM()->refr);
			}
		}
		color += (glm::u16vec3) dcolor;
	}

	//Fix color
	glm::u8vec3 out = glm::u8vec3(0, 0, 0);
	for (int i = 0; i < 3; i++) {
		color[i] = (color[i] < 0) ? 0 : color[i];
		color[i] = (color[i] > 255) ? 255 : color[i];
		out[i] = (glm::u8) color[i];
	}
	return out;
}