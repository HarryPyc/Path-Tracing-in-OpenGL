#include "Render.h"

void Render::init() {
	glewInit();
	create_quad_vao();
	quad_shader = InitShader(quad_vertex_shader.c_str(), quad_fragment_shader.c_str());
	compute_shader = InitShader(quad_compute_shader.c_str());
	result = new Texture2D("result", WINDOW_WIDTH, WINDOW_HEIGHT);
	cam = new Camera(glm::vec3(0, -20, 150), glm::vec3(0), glm::vec3(0, 1, 0));
	Samples = 0;
}
void Render::render() {
	Samples++;
	//ray tracing
	glUseProgram(compute_shader);
	result->activate(compute_shader, 0);
	glBindImageTexture(0, result->texture_id, 0, GL_TRUE, 0, GL_READ_WRITE, GL_RGBA32F);
	glUniform1i(glGetUniformLocation(compute_shader, "Samples"), Samples);
	cam->upload(compute_shader);
	glDispatchCompute(40, 30, 1);

	//render result image
	glUseProgram(quad_shader);
	result->activate(quad_shader, 0);
	glBindVertexArray(quad_vao);
	glDrawArrays(GL_TRIANGLE_STRIP, 0, 4);

}
Render& Render::getInstance() {
	static Render app;
	return app;
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