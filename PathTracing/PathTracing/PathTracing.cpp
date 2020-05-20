#include <iostream>
#include <GL/glew.h>
#include <GL/freeglut.h>
#include "Render.h"
#include "GlobalConstant.h"

void display() {
	glClear(GL_COLOR_BUFFER_BIT);
	glViewport(0, 0, WINDOW_WIDTH, WINDOW_HEIGHT);
	Render::getInstance().render();
	glutSwapBuffers();
}

void printGlInfo()
{
	std::cout << "Vendor: " << glGetString(GL_VENDOR) << std::endl;
	std::cout << "Renderer: " << glGetString(GL_RENDERER) << std::endl;
	std::cout << "Version: " << glGetString(GL_VERSION) << std::endl;
	std::cout << "GLSL Version: " << glGetString(GL_SHADING_LANGUAGE_VERSION) << std::endl;
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

	glutMainLoop();
	glutDestroyWindow(window);

    return 0;
}


