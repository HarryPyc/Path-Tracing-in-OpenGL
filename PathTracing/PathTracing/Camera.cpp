#include "Camera.h"


glm::mat4 Camera::getPerspectiveMatrix()
{
	return glm::perspective(hfov, aspect, 0.1f, 100.f);
}

glm::mat4 Camera::getViewMatrix()
{
	return glm::lookAt(pos,getTarget(),up);
}


void Camera::upload(GLuint program)
{

    glUniform3fv(glGetUniformLocation(program, "camPos"), 1, &pos[0]);

    glm::mat4 PV = getPerspectiveMatrix() * getViewMatrix();
    glm::mat4 inversePV = glm::inverse((PV));
    glUniformMatrix4fv(glGetUniformLocation(program, "invPV"), 1, GL_FALSE, &inversePV[0][0]);
}

Camera::Camera(glm::vec3 _pos, glm::vec3 _target, glm::vec3 _up)
{
	pos = _pos;
	dir = glm::normalize(_target - pos);
	up = _up;
    hfov = glm::radians(60.f);
    int w = glutGet(GLUT_WINDOW_WIDTH);
    int h = glutGet(GLUT_WINDOW_HEIGHT);
    aspect = float(w) / float(h);
}

