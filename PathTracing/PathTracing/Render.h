#pragma once
#include <GL/glew.h>
#include <string>
#include "InitShader.h"
#include "Texture2D.h"
#include "GlobalConstant.h"
#include "Camera.h"
#include "ThermalData.h"
#include "Mesh.h"

class Render {
public:
	void init();
	void render();
	
	Camera* cam;
	Texture2D *result;
	int Samples;
	static Render& getInstance();

private:
	GLuint quad_vao;
	GLuint quad_shader, compute_shader;
	int nu;
	bool isRight;

	vector<Mesh*> meshes;
	vector<CSMeshData> CSdataList;
	vector<glm::vec4> Vertices;
	vector<unsigned int> Indices;
	
	void initSSBO();
	void vertexProcess();
	void create_quad_vao();

};

