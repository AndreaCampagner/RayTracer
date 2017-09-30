#pragma once
#include "Shape.h"
#include <vector>
#include "Triangle.h"

class Trimesh : public Shape {
private:
	std::vector<Triangle*> shapes;
	std::random_device rd;
	std::mt19937 gen;
	std::uniform_int_distribution<> xs;

public:
	Trimesh(std::vector<glm::dvec3> points, Material* m) : Shape(m), shapes(), gen(rd()), xs(0,shapes.size()/3-1){
		for (int i = 0; i < points.size() / 3; i++) {
			Triangle* tmp = new Triangle(points[i * 3], points[i * 3 + 1], points[i * 3 + 2], m);
			shapes.push_back(tmp);
		}
	};

	Trimesh(std::vector<glm::dvec3> points, std::vector<double> us, std::vector<double> vs, Material* m) : Shape(m), shapes(), gen(rd()), xs(0, shapes.size() / 3-1) {
		for (int i = 0; i < points.size() / 3; i++) {
			Triangle* tmp = new Triangle(points[i * 3], points[i * 3 + 1], points[i * 3 + 2], m, us[i*3], vs[i*3], us[i*3+1], vs[i*3+1], us[i*3+2], vs[i*3+2]);
			shapes.push_back(tmp);
		}
	};

	Trimesh(std::vector<Triangle*> shapes) : Shape(nullptr), shapes(shapes), gen(rd()), xs(0, shapes.size()-1) {};

	bool intersect(Ray& ray, Point& p) override;
	glm::dvec4 normal(glm::dvec4 p) override;
	void apply(glm::dmat4 transform) override;
	Point point() override;
	bool isLight() override;
};