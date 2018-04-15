#include "Camera.h"

#include <gtc/matrix_transform.hpp>  
#include <gtc/type_ptr.hpp>

using namespace glm;

void Viewport::setPos(GLsizei aw, GLsizei ah)
{
	x = aw;
	y = ah;
	set();
}
//-------------------------------------------------------------------------

void Viewport::setSize(GLsizei aw, GLsizei ah)
{
	w = aw;
	h = ah;
	set();
}
//-------------------------------------------------------------------------

void Viewport::set()
{
	glViewport(x, y, w, h);
}
//-------------------------------------------------------------------------

void Camera::setAZ()
{
	eye = dvec3(0, 0, 500);
	look = dvec3(0, 0, 0);
	up = dvec3(0, 1, 0);
	viewMat = lookAt(eye, look, up);
	setVM();
	actualizarFront();
	actualizarRight();
	actualizarPitch();
	actualizarYaw();
}
//-------------------------------------------------------------------------

void Camera::set3D()
{
	eye = dvec3(500, 500, 500);
	look = dvec3(0, 10, 0);
	up = dvec3(0, 1, 0);
	viewMat = lookAt(eye, look, up);
	setVM();
	actualizarFront();
	actualizarRight();
	actualizarPitch();
	actualizarYaw();
}
//-------------------------------------------------------------------------

void Camera::setVM()
{
	glMatrixMode(GL_MODELVIEW);
	glLoadMatrixd(value_ptr(viewMat));
}
//-------------------------------------------------------------------------

void Camera::pitch(GLdouble a)
{
	//viewMat = rotate(viewMat, glm::radians(-a), glm::dvec3(1.0, 0, 0));
	rotatePY(a, 0);
	actualizarFront();
	actualizarRight();
}
//-------------------------------------------------------------------------
void Camera::yaw(GLdouble a)
{
	//viewMat = rotate(viewMat, glm::radians(-a), glm::dvec3(0, 1.0, 0));
	rotatePY(0, a);
	actualizarFront();
	actualizarRight();
}
//-------------------------------------------------------------------------
void Camera::roll(GLdouble a)
{
	viewMat = rotate(viewMat, glm::radians(-a), glm::dvec3(0, 0, 1.0));
	actualizarFront();
	actualizarRight();
}
//-------------------------------------------------------------------------

void Camera::scale(GLdouble s)
{
	factScale -= s;
	if (s < 0) s = 0.01;
	setPM();
}
//-------------------------------------------------------------------------

void Camera::setSize(GLdouble aw, GLdouble ah)
{
	xRight = aw / 2.0;
	xLeft = -xRight;
	yTop = ah / 2.0;
	yBot = -yTop;
	setPM();
}

//-------------------------------------------------------------------------

void Camera::setPM()
{
	if(orto == true) //ortogonal
		projMat = ortho(xLeft*factScale, xRight*factScale, yBot*factScale, yTop*factScale, nearVal, farVal);
	else //perspectiva
		projMat = frustum(xLeft*factScale, xRight*factScale, yBot*factScale, yTop*factScale, nearVal, farVal);
	glMatrixMode(GL_PROJECTION);
	glLoadMatrixd(value_ptr(projMat));
	glMatrixMode(GL_MODELVIEW);
}
//-------------------------------------------------------------------------

void Camera::moveLR(GLdouble cs) { // Left / Right 
	eye = eye + (right * cs);
	viewMat = lookAt(eye, eye + front, up);
	actualizarRight();
}
void Camera::moveFB(GLdouble cs) { // Forward / Backward   
	eye = eye + (front * cs);
	viewMat = lookAt(eye, eye + front, up);
	actualizarFront();
}
void Camera::moveUD(GLdouble cs) { // Up / Down 
	eye = eye + (up * cs);
	viewMat = lookAt(eye, eye + front, up);
}
void Camera::rotatePY(GLdouble incrPitch, GLdouble incrYaw) {
	pitchAux += incrPitch;
	yawAux += incrYaw; // Actualizar los angulos
	if (pitchAux > 89.5) pitchAux = 89.5; // Limitar los angulos
										  // Actualizar la direccion de vista
	front.x = sin(radians(yawAux)) * cos(radians(pitchAux));
	front.y = sin(radians(pitchAux));
	front.z = -cos(radians(yawAux)) * cos(radians(pitchAux));
	front = glm::normalize(front);
	viewMat = lookAt(eye, eye + front, up);
}

void Camera::actualizarFront() {
	front = -normalize(eye - look);
}

void Camera::actualizarRight() {
	right = normalize(cross(up, normalize(eye - look)));
}


void Camera::setPrj() {
	if (orto == false) { //ortogonal
		orto = true;
		glMatrixMode(GL_PROJECTION);
		projMat = ortho(xLeft*factScale, xRight*factScale, yBot*factScale, yTop*factScale, yTop*factScale, farVal*factScale);
		glLoadMatrixd(value_ptr(projMat));
		glMatrixMode(GL_MODELVIEW);

	}
	else {
		orto = false; //perspectiva
		glMatrixMode(GL_PROJECTION);
		projMat = frustum(xLeft*factScale, xRight*factScale, yBot*factScale, yTop*factScale, yTop*factScale, farVal*factScale);
		glLoadMatrixd(value_ptr(projMat));
		glMatrixMode(GL_MODELVIEW);
	}
	
}

void Camera::actualizarPitch() {
	pitchAux = glm::degrees(asin(front.y));
}

void Camera::actualizarYaw() {
	yawAux = glm::degrees(asin(front.x / cos(radians(pitchAux))));
}