#define _USE_MATH_DEFINES
#include "Framework.h"
#include "Materials.h"

void main() {
	int w = 1024, h = 768;
	
	std::vector<Triangle*> triangles;
	std::vector<Triangle*> trianglesLight;

	//Back
	glm::dvec4 v1(400, -400, -960, 1);
	glm::dvec4 v2(-400, 400, -960, 1);
	glm::dvec4 v3(-400, -400, -960, 1);
	triangles.push_back(new Triangle(v1, v2, v3, &mirror));

	v1 = glm::dvec4(400, -400, -960, 1);
	v2 = glm::dvec4(400, 400, -960, 1);
	v3 = glm::dvec4(-400, 400, -960, 1);
	triangles.push_back(new Triangle(v1, v2, v3, &mirror));

	//Left
	v1 = glm::dvec4(-400, -400, 960, 1);
	v2 = glm::dvec4(-400, -400, -960, 1);
	v3 = glm::dvec4(-400, 400, 960, 1);
	triangles.push_back(new Triangle(v1, v2, v3, &greenDiffuse));

	v1 = glm::dvec4(-400, -400, -960, 1);
	v2 = glm::dvec4(-400, 400, -960, 1);
	v3 = glm::dvec4(-400, 400, 960, 1);
	triangles.push_back(new Triangle(v1, v2, v3, &greenDiffuse));

	//Right
	v1 = glm::dvec4(400, -400, -960, 1);
	v2 = glm::dvec4(400, -400, 960, 1);
	v3 = glm::dvec4(400, 400, -960, 1);
	triangles.push_back(new Triangle(v1, v2, v3, &redDiffuse));

	v1 = glm::dvec4(400, -400, 960, 1);
	v2 = glm::dvec4(400, 400, 960, 1);
	v3 = glm::dvec4(400, 400, -960, 1);
	triangles.push_back(new Triangle(v1, v2, v3, &redDiffuse));

	//Bottom
	v1 = glm::dvec4(-400, -400, 960, 1);
	v2 = glm::dvec4(400, -400, 960, 1);
	v3 = glm::dvec4(-400, -400, -960, 1);
	triangles.push_back(new Triangle(v1, v2, v3, &greyDiffuse));

	v1 = glm::dvec4(400, -400, 960, 1);
	v2 = glm::dvec4(400, -400, -960, 1);
	v3 = glm::dvec4(-400, -400, -960, 1);
	triangles.push_back(new Triangle(v1, v2, v3, &greyDiffuse));

	//Top
	v1 = glm::dvec4(-400, 400, 960, 1);
	v2 = glm::dvec4(-400, 400, -960, 1);
	v3 = glm::dvec4(400, 400, 960, 1);
	triangles.push_back(new Triangle(v1, v2, v3, &greyDiffuse));

	v1 = glm::dvec4(400, 400, 960, 1);
	v2 = glm::dvec4(-400, 400, -960, 1);
	v3 = glm::dvec4(400, 400, -960, 1);
	triangles.push_back(new Triangle(v1, v2, v3, &greyDiffuse));

	Trimesh tm1(triangles);

	v1 = glm::dvec4(-50, 380, -50, 1);
	v2 = glm::dvec4(50, 380, 50, 1);
	v3 = glm::dvec4(-50, 380, 50, 1);
	trianglesLight.push_back(new Triangle(v1, v2, v3, &emissive));

	v1 = glm::dvec4(50, 380, 50, 1);
	v2 = glm::dvec4(-50, 380, -50, 1);
	v3 = glm::dvec4(50, 380, -50, 1);
	trianglesLight.push_back(new Triangle(v1, v2, v3, &emissive));

	Trimesh tlight(trianglesLight);

	Sphere s1(glm::dvec3(-205, -310, -500.0), 100.0, &blueGlossy);
	Sphere s2(glm::dvec3(0, -200, -500.0), 100.0, &blueHalfGlossy);
	Sphere s3(glm::dvec3(205, -298, -500.0), 100.0, &greenDiffuse);
	Sphere s4(glm::dvec3(0, -300, 0), 100.0, &tiledGlass);
	Sphere lightr(glm::dvec3(400, 0, 0), 40, &emissive);
	Sphere lightl(glm::dvec3(-400, 0, 0), 40, &emissive);
	std::vector<Shape*> shapes;
	shapes.push_back(&s1);
	shapes.push_back(&s2);
	shapes.push_back(&s3);
	shapes.push_back(&s4);
	shapes.push_back(&tm1);
	//shapes.push_back(&tlight);
	shapes.push_back(&lightl);
	shapes.push_back(&lightr);
	Camera cam(glm::dvec4(0, -250, 100, 1), glm::dvec4(0, 0, -601, 1), glm::dvec4(0.0, 1.0, 0.0, 0), -400, 1024, 768, 600, 0);
	Scene scene(cam, shapes);
	int shadowRays = 5;
	int glossyRays = 1;
	int aaRays = 5;
	int dof_rays = 1;
	int depth = 2;

	scene.render("image_5.ppm", w, h, depth, shadowRays, aaRays, glossyRays, dof_rays);
	
}