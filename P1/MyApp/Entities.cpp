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
		mesh->draw();
}

void Entity::RotacionDiabolo() {
	//ang = ang + 10;
}

void Entity::update(GLuint timeElapsed) {

}

/*void Entity::guardarImagen() {

int x = glutGet(GLUT_WINDOW_WIDTH);
int y = glutGet(GLUT_WINDOW_HEIGHT);
textura.loadColorBuffer(x,y);
}*/
//-------------------------------------------------------------------------

void Entity::setMvM(dmat4 const& modelViewMat)
{
	glMatrixMode(GL_MODELVIEW);
	dmat4 aMat = modelViewMat * modelMat;
	glLoadMatrixd(value_ptr(aMat));
}
//-------------------------------------------------------------------------

EjesRGB::EjesRGB(GLdouble l) : Entity()
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
	mesh = Mesh::generateRectangle(r, h);
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

void Diabolo::update(GLuint timeElapsed)
{
	RotacionDiabolo();
}
void Diabolo::render(glm::dmat4 const& modelViewMat)
{
	glMatrixMode(GL_MODELVIEW);
	dmat4 aMat = modelViewMat * modelMat;
	aMat = translate(aMat, glm::dvec3(-200, 0.0, -altura));
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
	aMat = translate(aMat, glm::dvec3(-200, 0.0, altura));
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
	aMat = translate(aMat, glm::dvec3(0.0, 0.0, altura / 2));
	glLoadMatrixd(value_ptr(aMat));
	draw();

}

Espejo::Espejo(GLdouble w, GLdouble h) : Entity()
{
	mesh = Mesh::generateEspejoTex(w, h);
}
void Espejo::draw()
{
	textura.bind();
	mesh->draw();
	textura.unbind();
}

void Espejo::update(GLuint timeElapsed)
{
	textura.loadColorBuffer(glutGet(GLUT_WINDOW_WIDTH), glutGet(GLUT_WINDOW_HEIGHT));
}

Jardinera::Jardinera(GLdouble x, GLdouble w, GLdouble h) : Entity()
{
	mesh = Mesh::generateContCuboTex(x);
	textura.load("..\\Bmps\\window.bmp", 100);
	medida = x;
	w_suelo = w;
	h_suelo = h;
}

void Jardinera::draw()
{
	//glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
	glDepthMask(GL_FALSE);
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	textura.bind();
	mesh->draw();
	textura.unbind();
	glDisable(GL_BLEND);
	glDepthMask(GL_TRUE);
	//glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
}

void Jardinera::render(glm::dmat4 const& modelViewMat) {
	setMvM(modelViewMat);
	dmat4 aMat = modelViewMat * modelMat;
	GLdouble newx = (h_suelo / 2) - medida/2;
	GLdouble newz = -(w_suelo / 2) + medida / 2;
	//GLdouble newz = 0;
	aMat = translate(aMat, glm::dvec3(newx, 0.0, newz));
	glLoadMatrixd(value_ptr(aMat));
	draw();
}
Planta::Planta(GLdouble w, GLdouble h, GLdouble w_s, GLdouble h_s) : Entity()
{
	mesh = Mesh::generateRectangleTex(w, h);
	mesh2 = Mesh::generateRectangleTex(w, h);
	glm::ivec3 color;
	color.r = 0;
	color.g = 0;
	color.b = 0;
	textura.load("..\\Bmps\\grass.bmp", color, 0);
	w_suelo = w_s;
	h_suelo = h_s;
	h_p = h;
	w_p = w;
}
void Planta::draw()
{
	//glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
	glDepthMask(GL_FALSE);
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	textura.bind();
	mesh->draw();
	textura.unbind();
	//glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
}

void Planta::render(glm::dmat4 const& modelViewMat) {
	GLdouble newx = (w_suelo / 2) - w_p/2;
	GLdouble newz = -(h_suelo / 2) + h_p / 2;
	//GLdouble newz = 0;
	glDepthMask(GL_FALSE);
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	setMvM(modelViewMat);
	dmat4 aMat = modelViewMat * modelMat;
	aMat = translate(aMat, glm::dvec3(newx, 0.0, newz));
	mesh2->draw();
	glMatrixMode(GL_MODELVIEW);
	aMat = rotate(aMat, radians(45.0), glm::dvec3(0.0, 1.0, 0.0));
	//aMat = translate(aMat, glm::dvec3(newx, 0.0, newz));
	glLoadMatrixd(value_ptr(aMat));
	textura.bind();
	mesh2->draw();
	textura.unbind();

	glMatrixMode(GL_MODELVIEW);
	aMat = modelViewMat * modelMat;
	aMat = translate(aMat, glm::dvec3(newx, 0.0, newz));
	aMat = rotate(aMat, radians(90.0), glm::dvec3(0.0, 1.0, 0.0));
	//aMat = translate(aMat, glm::dvec3(newx, 0.0, newz));
	glLoadMatrixd(value_ptr(aMat));
	textura.bind();
	mesh2->draw();
	textura.unbind();

	glMatrixMode(GL_MODELVIEW);
	aMat = modelViewMat * modelMat;
	aMat = translate(aMat, glm::dvec3(newx, 0.0, newz));
	aMat = rotate(aMat, radians(135.0), glm::dvec3(0.0, 1.0, 0.0));
	//aMat = translate(aMat, glm::dvec3(newx, 0.0, newz));
	glLoadMatrixd(value_ptr(aMat));
	textura.bind();
	
	mesh2->draw();
	textura.unbind();

	glDisable(GL_BLEND);
	glDepthMask(GL_TRUE);
}