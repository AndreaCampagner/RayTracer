#pragma once
#define _USE_MATH_DEFINES
#include "Shape.h"
#include <vector>
#include "Camera.h"
#include <string>
#include <glm/gtc/matrix_transform.hpp>
#include <random>
#include <glm/gtx/rotate_vector.hpp>
#include <fstream>

class Scene {
private:
	std::vector<Shape*> shapes;
	Camera camera;
	std::mt19937 gen;

public:
	Scene(Camera cam, std::vector<Shape*> shapes) : camera(cam), gen(std::random_device()()), shapes(shapes){};

	void cameraTransform();

	int closestIntersection(Ray r, Point& closest);
	void render(std::string file, int w, int h, int depth, int shadowRays, int aaRays, int glossyRays, int dofRays);

	glm::dvec3 inLight(Point p, Point q, int l);

	double distance(glm::dvec4 p1, glm::dvec4 p2);

	glm::u8vec3 trace(Ray ray, int depth, int maxDepth, int shadowRays, int glossyRays);
};