#include "Entities.h"
#include "Camera.h"

#include <gtc/matrix_transform.hpp>  
#include <gtc/type_ptr.hpp>

using namespace glm;

//-------------------------------------------------------------------------

void Entity::render(dmat4 const& modelViewMat) 
{ 
	setMvM(modelViewMat); 
	draw(); 
}
//-------------------------------------------------------------------------

void Entity::draw() 
{ 
  if (mesh != nullptr) 
    mesh -> draw(); 
}

void Entity::RotacionDiabolo() {
	//ang = ang + 10;
}
//-------------------------------------------------------------------------

void Entity::setMvM(dmat4 const& modelViewMat)
{
	glMatrixMode(GL_MODELVIEW);
	dmat4 aMat = modelViewMat * modelMat;
	glLoadMatrixd(value_ptr(aMat));
}
//-------------------------------------------------------------------------

EjesRGB::EjesRGB(GLdouble l): Entity() 
{
  mesh = Mesh::generateAxesRGB(l);
}
//-------------------------------------------------------------------------

void EjesRGB::draw()
{
  glLineWidth(2);
  mesh->draw();
  glLineWidth(1);
}
//-------------------------------------------------------------------------
Triangulo::Triangulo(GLdouble r) : Entity()
{
	mesh = Mesh::generateTriangle(r);
}
void Triangulo::draw()
{
	glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
	mesh->draw();
	glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
}

TrianguloRGB::TrianguloRGB(GLdouble r) : Entity()
{
	mesh = Mesh::generateTriangleRGB(r);
}
void TrianguloRGB::draw()
{
	glPolygonMode(GL_FRONT_AND_BACK, GL_BLUE);
	mesh->draw();
	glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
}


TriPyramid::TriPyramid(GLdouble r, GLdouble h) : Entity()
{
	mesh = Mesh::generateRectangle(r,h);
}

void TriPyramid::draw()
{
	glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
	mesh->draw();
	glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
}

ContCubo::ContCubo(GLdouble l) : Entity()
{
	mesh = Mesh::generateContCubo(l);
}

void ContCubo::draw()
{
	glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
	mesh->draw();
	glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
}

Diabolo::Diabolo(GLdouble r, GLdouble h) : Entity()
{
	mesh = Mesh::generateTriPyramid(r, h);
	radio = r;
	altura = h;
}

void Diabolo::draw()
{
	glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
	mesh->draw();
	glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
}

void Diabolo::RotacionDiabolo() {
	ang = ang + 10;
}
void Diabolo::render(glm::dmat4 const& modelViewMat)
{
	glMatrixMode(GL_MODELVIEW);
	dmat4 aMat = modelViewMat * modelMat;
	aMat = translate(aMat, glm::dvec3(0, 0.0, -altura));
	aMat = rotate(aMat, radians(ang), glm::dvec3(0.0, 0.0, 1.0));
	glLoadMatrixd(value_ptr(aMat));
	glColor3d(1.0, 0.0, 0.0);
	draw();

	glMatrixMode(GL_MODELVIEW);
	//aMat = rotate(aMat, radians(60.0),glm::dvec3(0.0,0.0,1.0));
	aMat = rotate(aMat, radians(180.0), glm::dvec3(0.0, 0.0, 1.0));
	glLoadMatrixd(value_ptr(aMat));
	glColor3d(0.0, 1.0, 0.0);
	draw();

	glMatrixMode(GL_MODELVIEW);
	aMat = modelViewMat * modelMat;
	aMat = translate(aMat, glm::dvec3(0, 0.0, altura));
	aMat = rotate(aMat, radians(180.0), glm::dvec3(0.0, 1.0, 0.0));
	aMat = rotate(aMat, radians(ang), glm::dvec3(0.0, 0.0, 0.1));
	//aMat = rotate(aMat, radians(ang+120.0), glm::dvec3(0.0, 1.0, 0.0));
	glLoadMatrixd(value_ptr(aMat));
	glColor3d(0.0, 0.0, 1.0);
	mesh->draw();

	glMatrixMode(GL_MODELVIEW);
	aMat = rotate(aMat, radians(180.0), glm::dvec3(0.0, 0.0, 1.0));
	//aMat = rotate(aMat, radians(ang+120.0), glm::dvec3(0.0, 0.0, 1.0));
	glLoadMatrixd(value_ptr(aMat));
	glColor3d(0.0, 0.0, 0.0);
	mesh->draw();

}

Rectangle::Rectangle(GLdouble w, GLdouble h) : Entity()
{
	mesh = Mesh::generateRectangle(w, h);
}
void Rectangle::draw()
{
	glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
	mesh->draw();
	glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
}

Cubo::Cubo(GLdouble x) : Entity()
{
	mesh = Mesh::generateContCubo(x);
	mesh2 = Mesh::generateRectangle(x, x);
	altura = x;
}

void Cubo::draw()
{
	glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
	mesh->draw();
	glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
}

void Cubo::render(glm::dmat4 const& modelViewMat) {

	setMvM(modelViewMat);
	draw();
	glPolygonMode(GL_FRONT, GL_LINE);
	glPolygonMode(GL_BACK, GL_POINT);
	glMatrixMode(GL_MODELVIEW);
	dmat4 aMat = modelViewMat * modelMat;
	int pend = (altura * 15) / 100;
	aMat = translate(aMat, glm::dvec3(0, altura-pend, -pend));
	aMat = rotate(aMat, radians(45.0), glm::dvec3(1.0, 0.0, 0.0));
	glLoadMatrixd(value_ptr(aMat));
	mesh2->draw();
}