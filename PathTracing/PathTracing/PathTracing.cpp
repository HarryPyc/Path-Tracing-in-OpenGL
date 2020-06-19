#include <iostream>
#include <GL/glew.h>
#include <GL/freeglut.h>
#include "Render.h"
#include "GlobalConstant.h"

void display() {
	glClear(GL_COLOR_BUFFER_BIT);
	const int w = glutGet(GLUT_WINDOW_WIDTH);
	const int h = glutGet(GLUT_WINDOW_HEIGHT);
	glViewport(0, 0, w, h);
	Render::getInstance().render();
	glutSwapBuffers();

}
void idle() {
	glutPostRedisplay();
}
void keyboard(unsigned char key, int x, int y) {
	switch(key)
	{
	case 19: {
		std::string name = "text/" + std::to_string(Render::getInstance().Samples) + "Samples.txt";
		Render::getInstance().result->print(name);
		break;
	}
	default:
		break;
	}
}
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
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_RGBA | GLUT_DOUBLE);
	glutInitWindowPosition(0, 0);
	glutInitWindowSize(WINDOW_WIDTH, WINDOW_HEIGHT);
	int window = glutCreateWindow("Path Tracer");

	Render::getInstance().init();
	
	printGlInfo();

	glutDisplayFunc(display);
	glutIdleFunc(idle);
	glutKeyboardFunc(keyboard);

	glutMainLoop();
	glutDestroyWindow(window);

    return 0;
}


