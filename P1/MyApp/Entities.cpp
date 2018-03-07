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

void Entity::guardarImagen() {

	int x = glutGet(GLUT_WINDOW_WIDTH);
	int y = glutGet(GLUT_WINDOW_HEIGHT);
	textura.loadColorBuffer(x,y);
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
	mesh = Mesh::generateTriPyramidTex(r, h);
	textura.load("..\\Bmps\\floris.bmp");
	radio = r;
	altura = h;
}

void Diabolo::draw()
{
	//glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
	mesh->draw();
	//glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
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
	textura.bind();
	draw();
	textura.unbind();

	glMatrixMode(GL_MODELVIEW);
	//aMat = rotate(aMat, radians(60.0),glm::dvec3(0.0,0.0,1.0));
	aMat = rotate(aMat, radians(180.0), glm::dvec3(0.0, 0.0, 1.0));
	glLoadMatrixd(value_ptr(aMat));
	glColor3d(0.0, 1.0, 0.0);
	textura.bind();
	draw();
	textura.unbind();

	glMatrixMode(GL_MODELVIEW);
	aMat = modelViewMat * modelMat;
	aMat = translate(aMat, glm::dvec3(0, 0.0, altura));
	aMat = rotate(aMat, radians(180.0), glm::dvec3(0.0, 1.0, 0.0));
	aMat = rotate(aMat, radians(ang), glm::dvec3(0.0, 0.0, 0.1));
	//aMat = rotate(aMat, radians(ang+120.0), glm::dvec3(0.0, 1.0, 0.0));
	glLoadMatrixd(value_ptr(aMat));
	glColor3d(0.0, 0.0, 1.0);
	textura.bind();
	mesh->draw();
	textura.unbind();

	glMatrixMode(GL_MODELVIEW);
	aMat = rotate(aMat, radians(180.0), glm::dvec3(0.0, 0.0, 1.0));
	//aMat = rotate(aMat, radians(ang+120.0), glm::dvec3(0.0, 0.0, 1.0));
	glLoadMatrixd(value_ptr(aMat));
	glColor3d(0.0, 0.0, 0.0);
	textura.bind();
	mesh->draw();
	textura.unbind();
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
	mesh = Mesh::generateContCuboTex(x);
	mesh2 = Mesh::generateRectangleTex(x, x);
	textura.load("..\\Bmps\\container.bmp");
	textura2.load("..\\Bmps\\chuches.bmp");
	altura = x;
}

void Cubo::draw()
{
	//glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
	glCullFace(GL_BACK);
	glEnable(GL_CULL_FACE);
	textura.bind();
	mesh->draw();
	glDisable(GL_CULL_FACE);
	glCullFace(GL_FRONT);
	glEnable(GL_CULL_FACE);
	textura2.bind();
	glDisable(GL_CULL_FACE);
	mesh->draw();
	textura.unbind();
	textura2.unbind();
	//glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
}

void Cubo::render(glm::dmat4 const& modelViewMat) {

	setMvM(modelViewMat);
	draw();
	//glPolygonMode(GL_FRONT, GL_FILL);
	//glPolygonMode(GL_BACK, GL_POINT);
	glMatrixMode(GL_MODELVIEW);
	dmat4 aMat = modelViewMat * modelMat;
	int pend = (altura * 15) / 100;
	aMat = translate(aMat, glm::dvec3(0, altura-pend, -pend));
	aMat = rotate(aMat, radians(45.0), glm::dvec3(1.0, 0.0, 0.0));
	glLoadMatrixd(value_ptr(aMat));
	textura.bind();
	mesh2->draw();
	textura.unbind();
}

Suelo::Suelo(GLdouble w, GLdouble h, GLdouble a) : Entity()
{
	mesh = Mesh::generateSueloTex(w, h);
	textura.load("..\\Bmps\\baldosaC.bmp");
	altura = a;
}
void Suelo::draw()
{
	//glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
	textura.bind();
	mesh->draw();
	textura.unbind();
	//glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
}

void Suelo::render(glm::dmat4 const& modelViewMat) {
	setMvM(modelViewMat);
	glMatrixMode(GL_MODELVIEW);
	dmat4 aMat = modelViewMat * modelMat;
	aMat = rotate(aMat, radians(90.0), glm::dvec3(1.0, 0.0, 0.0));
	aMat = translate(aMat, glm::dvec3(0.0, 0.0, altura/2));
	glLoadMatrixd(value_ptr(aMat));
	draw();

}