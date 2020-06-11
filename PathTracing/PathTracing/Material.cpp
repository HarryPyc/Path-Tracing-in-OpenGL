#include "Material.h"

Material::Material(glm::vec3 _color, glm::vec3 _emission, int _mode, float _reflectivity)
	: mode(_mode), color(_color), emission(_emission), reflectivity(_reflectivity) {}


void Material::upload(GLuint program)
{
	glUniform1i(glGetUniformLocation(program, modeName), mode);
	glUniform1f(glGetUniformLocation(program, reflectivityName), reflectivity);
	glUniform3fv(glGetUniformLocation(program, colorName), 1, glm::value_ptr(color));
	glUniform3fv(glGetUniformLocation(program, emissionName), 1, glm::value_ptr(emission));
}
