#pragma once
#include <GL/glew.h>
#include <string>
#include "InitShader.h"
#include "Texture2D.h"
#include "GlobalConstant.h"
#include "Camera.h"
#include "ThermalData.h"
#include "Mesh.h"
#include "KdTree.h"

class Render {
public:
	void init();
	void render();
	
	Camera* cam;
	Texture2D *result;
	int Samples;
	static Render& getInstance();

private:
	GLuint quad_vao, ubo, Vssbo, Issbo,TreeUBO;
	GLuint quad_shader, compute_shader;
	int nu;
	bool isRight;

	vector<Mesh*> meshes;
	vector<CSMeshData> CSdataList;
	KdTree* tree;
	
	void initSSBO();
	void vertexProcess();
	void uploadTree();
	void create_quad_vao();

};

