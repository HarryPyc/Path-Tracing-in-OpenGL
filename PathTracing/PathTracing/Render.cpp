#include "Render.h"

void Render::init() {
	glewInit();
	create_quad_vao();
	quad_shader = InitShader(quad_vertex_shader.c_str(), quad_fragment_shader.c_str());
	compute_shader = InitShader(quad_compute_shader.c_str());
	result = new Texture2D("result", WINDOW_WIDTH, WINDOW_HEIGHT);
	cam = new Camera(glm::vec3(200, 150, 1100), glm::vec3(200,150,600), glm::vec3(0, 1, 0));
	//uploadThermalData(compute_shader, 0);

	Samples = 0; nu = 0; isRight = true;

	Mesh* cube = new Mesh("asset/model/cube.obj", glm::vec3(200,50,500), Material::Orange());
	cube->transform->Scale(glm::vec3(50)); cube->material->mode = 1;
	cube->transform->Rotate(30, glm::vec3(0, 1, 0));
	meshes.push_back(cube);
	Mesh* obj2 = new Mesh("asset/model/bunny.obj", glm::vec3(90, 0, 600), Material::Blue());
	obj2->transform->Scale(glm::vec3(800)); obj2->material->mode = 1;
	//obj2->transform->Rotate(60, glm::vec3(0, 1, 0));
	//meshes.push_back(obj2);

	initSSBO();
	vertexProcess();
}
void Render::render() {
	Samples++;
	//ray tracing
	glUseProgram(compute_shader);
	result->activate(compute_shader, 0);
	glBindImageTexture(0, result->texture_id, 0, GL_TRUE, 0, GL_READ_WRITE, GL_RGBA32F);
	cam->upload(compute_shader);
	glUniform1i(glGetUniformLocation(compute_shader, "Samples"), Samples);
	glDispatchCompute(40, 30, 1);

	//render result image
	glUseProgram(quad_shader);
	result->activate(quad_shader, 0);
	glBindVertexArray(quad_vao);
	glDrawArrays(GL_TRIANGLE_STRIP, 0, 4);

	//automatically print results
	/*if (Samples == 8192 && nu <11) {
		std::string name = "text/"+ std::to_string(nu)+"nu"+ std::to_string(Samples) + "spp"+(isRight?"Right":"Left")+".txt";
		Render::getInstance().result->print(name);
		result->clear(glm::vec4(0)); Samples = 0;
		if (isRight) {
			cam->pos.x = 100;
		}
		else if(nu < 10){
			nu++;
			cam->pos.x = 200;
			uploadThermalData(compute_shader, nu);
		}
		isRight = !isRight;
	}*/
}
Render& Render::getInstance() {
	static Render app;
	return app;
}
void Render::initSSBO()
{
	for (int i = 0; i < meshes.size(); i++) {
		meshes[i]->initCSData(CSdataList, Vertices, Indices, i);
	}
	GLuint ubo, Vssbo, Issbo;
	glGenBuffers(1, &ubo);
	glBindBuffer(GL_UNIFORM_BUFFER, ubo);
	glBufferData(GL_UNIFORM_BUFFER, sizeof(CSMeshData) * CSdataList.size(), &CSdataList[0], GL_DYNAMIC_COPY);
	glBindBufferBase(GL_UNIFORM_BUFFER, 1, ubo);
	glBindBuffer(GL_UNIFORM_BUFFER, 0);
	glGenBuffers(1, &Vssbo);
	glBindBuffer(GL_SHADER_STORAGE_BUFFER, Vssbo);
	glBufferData(GL_SHADER_STORAGE_BUFFER, sizeof(glm::vec4) * Vertices.size(), &Vertices[0], GL_DYNAMIC_COPY);
	glBindBufferBase(GL_SHADER_STORAGE_BUFFER, 2, Vssbo);
	glGenBuffers(1, &Issbo);
	glBindBuffer(GL_SHADER_STORAGE_BUFFER, Issbo);
	glBufferData(GL_SHADER_STORAGE_BUFFER, sizeof(unsigned int)*Indices.size(), &Indices[0], GL_DYNAMIC_COPY);
	glBindBufferBase(GL_SHADER_STORAGE_BUFFER, 3, Issbo);
	glBindBuffer(GL_SHADER_STORAGE_BUFFER, 0);
}
void Render::vertexProcess()
{
	GLuint vpProgram = InitShader(vertex_process_shader.c_str());
	glUseProgram(vpProgram);
	glDispatchCompute(10, 1, 1);
	glMemoryBarrier(GL_SHADER_STORAGE_BARRIER_BIT);
	glUseProgram(0);
}
void Render::create_quad_vao() {
	glGenVertexArrays(1, &quad_vao);
	glBindVertexArray(quad_vao);

	double vertices[] = {
		-1,  1, 0, 0, 0,
		-1, -1, 0, 0, 1,
		 1,  1, 0, 1, 0,
		 1, -1, 0, 1, 1
	};
	GLuint vbo = -1;
	glGenBuffers(1, &vbo);
	glBindBuffer(GL_ARRAY_BUFFER, vbo);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), &vertices[0], GL_STATIC_DRAW);

	const int pos_loc = 0, tex_coord_loc = 1;
	glEnableVertexAttribArray(pos_loc);
	glVertexAttribPointer(pos_loc, 3, GL_DOUBLE, GL_FALSE, 5 * sizeof(double), (void*)(0));
	glEnableVertexAttribArray(tex_coord_loc);
	glVertexAttribPointer(tex_coord_loc, 2, GL_DOUBLE, GL_FALSE, 5 * sizeof(double), (void*)(3*sizeof(double)));
	
}