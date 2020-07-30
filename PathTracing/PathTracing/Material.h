#pragma once
#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <GL/glew.h>
namespace {
	const char* colorName = "material.color";
	const char* emissionName = "material.emission";
	const char* modeName = "material.mode";
	const char* reflectivityName = "material.reflectivity";
}
class Material
{
public:
	int mode;
	float reflectivity;
	glm::vec3 color, emission;
	

	Material(
		glm::vec3 _color = glm::vec3(0.9f), 
		glm::vec3 _emission = glm::vec3(0),
		int _mode = 1,
		float _reflectivity = 1.0f);

	void upload(GLuint program);

	static Material* Red() {
		return new Material(glm::vec3(1, 0, 0));
	}

	static Material* Blue() {
		return new Material(glm::vec3(0.1, 0.1, 0.75));
	}

	static Material* Green() {
		return new Material(glm::vec3(0, 1, 0));
	}

	static Material* White() {
		return new Material(glm::vec3(0.75));
	}
	
	static Material* Orange() {
		return new Material(glm::vec3(0.99, 0.5, 0.1));
	}

	static Material* Pink() {
		return new Material(glm::vec3(0.99, 0.75, 0.8));
	}
};

