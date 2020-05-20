#pragma once
#include <GL/glew.h>
#include <string>
class Texture2D
{
public:
	GLuint texture_id;
	std::string texture_name;
	int width, height;

	Texture2D(const std::string name, int w, int h, GLenum magFilter = GL_NEAREST, GLenum minFilter = GL_NEAREST,
		GLint internalFormat = GL_RGBA32F, GLint type = GL_FLOAT, GLint wrap = GL_REPEAT);

	void activate(GLuint program, GLuint textureLoc);
};

