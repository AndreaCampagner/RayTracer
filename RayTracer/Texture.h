#pragma once
#include <glm\glm.hpp>
#include <string>
#include <fstream>

struct Texture {
private:
	glm::dvec3* image;
	int width, height;

public:
	Texture() : image(nullptr), width(0), height(0) {};
	Texture(glm::dvec3* a, int width, int height) : image(a), width(width), height(height) {};
	Texture(std::string file, int width, int height) : width(width), height(height), image(new glm::dvec3[width*height]) {
		std::ifstream ifs;
		try
		{
			ifs.open(file);
		}
		catch (std::exception& e) {}
		std::string line;
		std::getline(ifs, line);
		std::getline(ifs, line);
		std::getline(ifs, line);
		for (int i = 0; i < height; i++) 
		for (int j = 0; j < width; j++){
			glm::dvec3 v(0, 0, 0);
			ifs >> v[0];
			ifs >> v[1];
			ifs >> v[2];
			image[j*width + i] = v;
		}
	};
	const glm::dvec3 operator()(double u, double v) const;
};