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

void Mesh::initCSData(vector<CSMeshData>&CSDataList, vector<glm::vec4>&vertices, vector<unsigned int>& indices, int index) {
	CSMeshData CSdata;
	CSdata.color = material->color;
	CSdata.emission = material->emission;
	CSdata.mode = material->mode;
	CSdata.reflectivity = material->reflectivity;
	CSdata.M = transform->M;
	CSDataList.push_back(CSdata);
	if (mode == complex) {
		for (int i = 0; i < meshdata.vertices.size(); i++)
			vertices.push_back(glm::vec4(meshdata.vertices[i], index));
		indices.insert(indices.end(), meshdata.indices.begin(), meshdata.indices.end());
	}
	else
	{
		for (int i = 0; i < shape->vertices.size(); i++)
			vertices.push_back(glm::vec4(shape->vertices[i].pos, index));
		indices.insert(indices.end(), shape->indices.begin(), shape->indices.end());
	}
}
