#include "FPSController.h"
#include <GL/freeglut.h>
#include "Render.h"
FPSController::FPSController(Camera* camera)
{
    cam = camera;
	win_w = glutGet(GLUT_WINDOW_WIDTH);
	win_h = glutGet(GLUT_WINDOW_HEIGHT);
	mouseX = win_w / 2;
	mouseY = win_h / 2;
	init();

	glutMotionFunc(motion);
	glutKeyboardFunc(keyboard);
	glutKeyboardUpFunc(keyboard_up);
	glutSpecialFunc(special);
	glutSpecialUpFunc(special_up);
	glutPassiveMotionFunc(passive);
	glutMouseFunc(mouse);
}

FPSController::~FPSController()
{
}

void FPSController::init() {
	SetCursorPos(mouseX, mouseY);
	//glutSetCursor(GLUT_CURSOR_NONE);
}
void FPSController::update() {
	win_w = glutGet(GLUT_WINDOW_WIDTH);
	win_h = glutGet(GLUT_WINDOW_HEIGHT);
	if (useCursor)
		glutSetCursor(GLUT_CURSOR_NONE);
	else
		glutSetCursor(GLUT_CURSOR_LEFT_ARROW);
	lastPos = cam->pos, lastDir = cam->dir;
	Move();
}
void FPSController::Move()
{
	cam->pos += (hor*right() + ver*cam->dir + gravity*cam->up) * step;
	if (cam->pos != lastPos)
		Render::getInstance().needReset = true;
}
void FPSController::OnMouseMove(int x, int y)
{
	x = x * mouseSensitivity;
	y = y * mouseSensitivity;
	yaw += x;
	pitch += y;

	if (pitch > 89.0f)
		pitch = 89.0f;
	if (pitch < -89.0f)
		pitch = -89.0f;
	glm::mat4 R = glm::rotate(glm::radians(yaw), yAxis) * glm::rotate(glm::radians(pitch), xAxis);
	glm::vec4 t = R * glm::vec4(0.0f, 0.0f, -1.0f, 0.0f);
	cam->dir = normalize(glm::vec3(t));
	if (cam->dir != lastDir)
		Render::getInstance().needReset = true;
}

void keyboard(unsigned char key, int x, int y)
{
    ImGui_ImplGlut_KeyCallback(key);
	FPSController* ctrl = Render::getInstance().controller;
    switch (key)
    {
	case 'w':
		ctrl->ver = 1.0f;
		break;
	case 's':
		ctrl->ver = -1.0f;
		break;
	case 'a':
		ctrl->hor = -1.0f;
		break;
	case 'd':
		ctrl->hor = 1.0f;
		break;
	case 'e':
		ctrl->gravity = 1.0f;
		break;
	case 'q':
		ctrl->gravity = -1.0f;
		break;
	case 'm':
		ctrl->useCursor = !ctrl->useCursor;
		SetCursorPos(ctrl->mouseX, ctrl->mouseY);
		break;
	default:
		break;
    }
}

void keyboard_up(unsigned char key, int x, int y)
{
    ImGui_ImplGlut_KeyUpCallback(key);
	FPSController* ctrl = Render::getInstance().controller;
	switch (key)
	{
	case 'w':
		ctrl->ver = 0.0f;
		break;
	case 's':
		ctrl->ver = 0.0f;
		break;
	case 'a':
		ctrl->hor = 0.0f;
		break;
	case 'd':
		ctrl->hor = 0.0f;
		break;
	case 'e':
		ctrl->gravity = 0.0f;
		break;
	case 'q':
		ctrl->gravity = 0.0f;
		break;
	default:
		break;
	}
}

void special_up(int key, int x, int y)
{
    ImGui_ImplGlut_SpecialUpCallback(key);
}

void passive(int x, int y)
{
    ImGui_ImplGlut_PassiveMouseMotionCallback(x, y);
	FPSController* ctrl = Render::getInstance().controller;
	if (ctrl->useCursor) {
		glutWarpPointer(ctrl->win_w / 2, ctrl->win_h / 2);
		ctrl->mouseX = ctrl->win_w / 2;
		ctrl->mouseY = ctrl->win_h / 2;
		ctrl->OnMouseMove(ctrl->mouseX - x, ctrl->mouseY - y);
	}
}

void special(int key, int x, int y)
{
    ImGui_ImplGlut_SpecialCallback(key);
}

void motion(int x, int y)
{
    ImGui_ImplGlut_MouseMotionCallback(x, y);

}

void mouse(int button, int state, int x, int y)
{
    ImGui_ImplGlut_MouseButtonCallback(button, state);
}