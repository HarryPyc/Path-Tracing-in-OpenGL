#include "Camera.h"

glm::mat4 Camera::getPerspectiveMatrix(int w, int h)
{
	float aspect_ratio = float(w) / float(h);
	return glm::perspective(3.141592f / 4.f, aspect_ratio, 0.1f, 100.f);
}

glm::mat4 Camera::getViewMatrix()
{
	return glm::lookAt(pos,getTarget(),up);
}

void Camera::initRays() {
    const int w = glutGet(GLUT_WINDOW_WIDTH);
    const int h = glutGet(GLUT_WINDOW_HEIGHT);
    glm::mat4 P = getPerspectiveMatrix(w, h);
    glm::mat4 V = getViewMatrix();
    glm::mat4 inversePV = glm::inverse(glm::transpose(P * V));
    glm::vec4 temp;
    temp = glm::vec4(-1, -1, 0, 1) * inversePV;
    ray00 = glm::normalize(glm::vec3(temp / temp.w) - pos);
    temp = glm::vec4(-1,  1, 0, 1) * inversePV;
    ray01 = glm::normalize(glm::vec3(temp / temp.w) - pos);
    temp = glm::vec4( 1, -1, 0, 1) * inversePV;
    ray10 = glm::normalize(glm::vec3(temp / temp.w) - pos);
    temp = glm::vec4( 1,  1, 0, 1) * inversePV;
    ray11 = glm::normalize(glm::vec3(temp / temp.w) - pos);
}

void Camera::upload(GLuint program)
{
    //const int w = glutGet(GLUT_WINDOW_WIDTH);
    //const int h = glutGet(GLUT_WINDOW_HEIGHT);
    // 
    //glm::mat4 V = getViewMatrix();
    //glm::mat4 P = getPerspectiveMatrix(w, h);
    //glUniformMatrix4fv(glGetUniformLocation(program, "PV"), 1, false, glm::value_ptr(P * V));
    glUniform3fv(glGetUniformLocation(program, "camPos"), 1, &pos[0]);
    glUniform3fv(glGetUniformLocation(program, "ray00"), 1, &ray00[0]);
    glUniform3fv(glGetUniformLocation(program, "ray01"), 1, &ray01[0]);
    glUniform3fv(glGetUniformLocation(program, "ray10"), 1, &ray10[0]);
    glUniform3fv(glGetUniformLocation(program, "ray11"), 1, &ray11[0]);
}

Camera::Camera(glm::vec3 _pos, glm::vec3 _target, glm::vec3 _up)
{
	pos = _pos;
	dir = glm::normalize(_target - pos);
	up = _up;
    initRays();
}

