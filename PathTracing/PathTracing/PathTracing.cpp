#include <iostream>
#include <GL/glew.h>
#include <GL/freeglut.h>
#include "Render.h"
#include "GlobalConstant.h"
#include <imgui_impl_glut.h>

void displayGUI() {
	ImGui_ImplGlut_NewFrame();
	ImGui::Begin("Console");
	ImGui::Text("press m to release cursor");
	ImGui::End();
	ImGui::Render();
}
void display() {
	glClear(GL_COLOR_BUFFER_BIT);
	const int w = glutGet(GLUT_WINDOW_WIDTH);
	const int h = glutGet(GLUT_WINDOW_HEIGHT);
	glViewport(0, 0, w, h);
	Render::getInstance().render();

	//displayGUI();
	glutSwapBuffers();
}
void idle() {
	glutPostRedisplay();
}
//void keyboard(unsigned char key, int x, int y) {
//	ImGui_ImplGlut_KeyCallback(key);
//	switch(key)
//	{
//	case 19: {
//		std::string name = "screenshots/" + std::to_string(Render::getInstance().Samples) + "Samples.bmp";
//		Render::getInstance().result->print(name);
//		break;
//	}
//	default:
//		break;
//	}
//}
//void mouse_callback(int button, int state, int x, int y) {
//	ImGui_ImplGlut_MouseButtonCallback(button, state);
//}
//void motion_callback(int x, int y) {
//	ImGui_ImplGlut_MouseMotionCallback(x, y);
//}
//void passive_callback(int x, int y) {
//	ImGui_ImplGlut_PassiveMouseMotionCallback(x, y);
//}

void printGlInfo()
{
	std::cout << "Vendor: " << glGetString(GL_VENDOR) << std::endl;
	std::cout << "Renderer: " << glGetString(GL_RENDERER) << std::endl;
	std::cout << "Version: " << glGetString(GL_VERSION) << std::endl;
	std::cout << "GLSL Version: " << glGetString(GL_SHADING_LANGUAGE_VERSION) << std::endl;
	int X,Y,Z, total;
	glGetIntegeri_v(GL_MAX_COMPUTE_WORK_GROUP_SIZE, 0, &X);
	glGetIntegeri_v(GL_MAX_COMPUTE_WORK_GROUP_SIZE, 1, &Y);
	glGetIntegeri_v(GL_MAX_COMPUTE_WORK_GROUP_SIZE, 2, &Z);
	glGetIntegerv(GL_MAX_COMPUTE_WORK_GROUP_INVOCATIONS, &total);
	std::cout << "Max Compute Work Group Size: " << X << " " << Y << " " << Z << std::endl;
	std::cout << "Max Compute Work Group Invocations: " << total << std::endl;
}

int main(int argc, char** argv)
{
	//init glut
	glutInitContextVersion(4, 3);
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_RGBA | GLUT_DOUBLE);
	glutInitWindowPosition(0, 0);
	glutInitWindowSize(WINDOW_WIDTH, WINDOW_HEIGHT);
	int window = glutCreateWindow("Path Tracer, press m to use cursor");

	Render::getInstance().init();
	if (!ImGui_ImplGlut_Init())
		printf("ImGui Init Failed\n");
	
	printGlInfo();

	glutDisplayFunc(display);
	glutIdleFunc(idle);


	glutMainLoop();
	glutDestroyWindow(window);

    return 0;
}


