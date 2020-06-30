#pragma once
#include "LoadMesh.h"
#include "Transform.h"
#include "Material.h"
#include "Texture2D.h"
#include "SimpleShapes.h"
enum MeshMode {
	simple, complex,
};
struct CSMeshData{
	glm::vec3 color;
	int mode;
	glm::vec3 emission;
	float reflectivity;
	glm::mat4 M;
	int numVert, numIdx, PADDING0, PADDING1;
};
class Mesh
{
public:
	GLuint vao;
	Mesh(SimpleShapes* shape, glm::vec3 pos = glm::vec3(0),
		Material* mat = Material::White(), Texture2D* tex = NULL);
	Mesh(const std::string name, glm::vec3 pos = glm::vec3(0),
		Material* mat = Material::White(), Texture2D* tex = NULL);
	~Mesh();

	MeshData meshdata;
	SimpleShapes* shape;
	MeshMode mode;
	Transform* transform;
	Material* material;
	Texture2D* texture;
	void uploadTransformMatrix(GLuint program);
	void render(GLuint program);
	void draw();
	
	void initCSData(vector<CSMeshData>& CSDataList, vector<glm::vec4>& vectices, vector<glm::uvec4>& triangles, vector<glm::vec2>& tex_coords, int index);
};

