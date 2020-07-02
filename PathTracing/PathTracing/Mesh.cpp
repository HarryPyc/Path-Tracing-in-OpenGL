#include "Mesh.h"

Mesh::~Mesh() {
	delete shape, transform, material, texture;
}

Mesh::Mesh(SimpleShapes* _shape, glm::vec3 pos, Material* mat, Texture2D* tex)
	: shape(_shape), material(mat), vao(_shape->vao), mode(simple), texture(tex)
{
	transform = new Transform(pos);
}
Mesh::Mesh(const std::string name, glm::vec3 pos, Material* mat, Texture2D* tex)
	: mode(complex), material(mat), texture(tex)
{
	meshdata = LoadMesh(name);
	vao = meshdata.mVao;
	transform = new Transform(pos, glm::vec3(meshdata.mScaleFactor));
}

void Mesh::uploadTransformMatrix(GLuint program)
{
	int M_loc = glGetUniformLocation(program, "M");
	if (M_loc != -1)
	{
		glUniformMatrix4fv(M_loc, 1, false, glm::value_ptr(transform->M));
	}
}

void Mesh::render(GLuint program)
{
	uploadTransformMatrix(program);
	material->upload(program);
	if(texture != NULL)
		texture->activate(program, 0);
	draw();
}

void Mesh::draw() {
	glBindVertexArray(vao);
	if (mode == complex) {

		meshdata.DrawMesh();
	}
	else if (mode == simple) {
		glDrawElements(GL_TRIANGLE_STRIP, shape->N, GL_UNSIGNED_INT, 0);
	}
}

void Mesh::initCSData(vector<CSMeshData>&CSDataList, vector<glm::vec4>&vertices, vector<glm::uvec4>& triangles, vector<glm::vec2>& tex_coords, int index) {
	CSMeshData CSdata;
	CSdata.color = material->color;
	CSdata.emission = material->emission;
	CSdata.mode = material->mode;
	CSdata.reflectivity = material->reflectivity;
	CSdata.M = transform->M;
	if (mode == complex) {
		for (int i = 0; i < meshdata.vertices.size(); i++)
			vertices.push_back(glm::vec4(meshdata.vertices[i], index));
		for (int i = 0; i < meshdata.indices.size()-2; i += 3) {
			glm::uvec4 tri = glm::uvec4(meshdata.indices[i], meshdata.indices[i + 1], meshdata.indices[i + 2], index);
			triangles.push_back(tri);
		}
		tex_coords.insert(tex_coords.end(), meshdata.tex_coords.begin(), meshdata.tex_coords.end());
		CSdata.numVert = meshdata.vertices.size();
		CSdata.numIdx = meshdata.indices.size();
	}
	else
	{
		for (int i = 0; i < shape->vertices.size(); i++)
			vertices.push_back(glm::vec4(shape->vertices[i].pos, index));
		for (int i = 0; i < shape->indices.size() - 2; i += 3) {
			glm::uvec4 tri = glm::uvec4(shape->indices[i], shape->indices[i + 1], shape->indices[i + 2], index);
			triangles.push_back(tri);
		}
		CSdata.numVert = shape->vertices.size();
		CSdata.numIdx = shape->indices.size();
	}
	CSDataList.push_back(CSdata);
}
