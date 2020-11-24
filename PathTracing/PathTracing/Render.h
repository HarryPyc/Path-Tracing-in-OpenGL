#pragma once
#include <GL/glew.h>
#include <string>
#include "InitShader.h"
#include "Texture2D.h"
#include "GlobalConstant.h"
#include "Camera.h"
#include "FPSController.h"

class Render {
public:
	void init();
	void render();

	bool needReset = false;
	FPSController* controller;
	Camera* cam;
	Texture2D *result;
	int Samples;
	static Render& getInstance();
private:
	GLuint quad_vao;
	GLuint quad_shader, compute_shader;
	void create_quad_vao();
};

