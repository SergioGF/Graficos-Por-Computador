//#pragma once
#ifndef _H_Entities_H_
#define _H_Entities_H_

#include <GL/freeglut.h>
#include <glm.hpp>
#include "Mesh.h"
#include "Texture.h"
#include <vector>
#include <iostream>
using namespace std;
//-------------------------------------------------------------------------

class Entity
{
public:
	Entity() : modelMat(1.0) { };
	virtual ~Entity() { delete mesh; };

	virtual void render(glm::dmat4 const& modelViewMat);
	virtual void RotacionDiabolo();
	virtual void update(GLuint timeElapsed);
	virtual void moveBB8();
	//virtual void guardarImagen();
	glm::dmat4 modelMat;

protected:
	Mesh * mesh = nullptr;
	GLdouble ang = 60.0;
	Texture textura;
	Texture textura2;
	virtual void draw();
	virtual void setMvM(glm::dmat4 const& modelViewMat);
};

//-------------------------------------------------------------------------

class EjesRGB : public Entity
{
public:
	EjesRGB(GLdouble l);
	~EjesRGB() { };
	virtual void draw();
};

//-------------------------------------------------------------------------

class Triangulo : public Entity
{
public:
	Triangulo(GLdouble r);
	~Triangulo() { };
	virtual void draw();
};

class TrianguloRGB : public Entity
{
public:
	TrianguloRGB(GLdouble r);
	~TrianguloRGB() { };
	virtual void draw();
};

class TriPyramid : public Entity
{
public:
	TriPyramid(GLdouble r, GLdouble h);
	~TriPyramid() { };
	virtual void draw();
};

class ContCubo : public Entity
{
public:
	ContCubo(GLdouble l);
	~ContCubo() { };
	virtual void draw();
};

class Diabolo : public Entity
{
public:
	Diabolo(GLdouble r, GLdouble h);
	~Diabolo() { };
	virtual void draw();
	void RotacionDiabolo();
	virtual void render(glm::dmat4 const& modelViewMat);
	virtual void update(GLuint timeElapsed);
protected:
	GLdouble radio;
	GLdouble altura;
};

class Rectangle : public Entity
{
public:
	Rectangle(GLdouble w, GLdouble h);
	~Rectangle() { };
	virtual void draw();
protected:
};

class Cubo : public Entity
{
public:
	Cubo(GLdouble x);
	~Cubo() { };
	virtual void drawMesh();
	virtual void drawMeshAux();
	virtual void drawMeshAux2();
	virtual void render(glm::dmat4 const& modelViewMat);
protected:
	Mesh * mesh2 = nullptr;
	GLdouble altura;
};

class Suelo : public Entity
{
public:
	Suelo(GLdouble w, GLdouble h);
	~Suelo() { };
	virtual void draw();

protected:
};


class Espejo : public Entity
{
public:
	Espejo(GLdouble w, GLdouble h);
	~Espejo() { };
	virtual void draw();
	virtual void update(GLuint timeElapsed);

protected:
};

class Jardinera : public Entity
{
public:
	Jardinera(GLdouble x, GLdouble w, GLdouble h);
	~Jardinera() { };
	virtual void draw();
protected:
	GLdouble w_suelo;
	GLdouble h_suelo;
	GLdouble medida;
};

class Planta : public Entity
{
public:
	Planta(GLdouble h);
	~Planta() { };
	virtual void draw();
protected:
	Mesh * mesh2 = nullptr;
	GLdouble w_suelo;
	GLdouble h_suelo;
	GLdouble w_p;
	GLdouble h_p;
	GLdouble medida;
	virtual void render(glm::dmat4 const& modelViewMat);
};

class MPR : public Entity
{
public:
	MPR(int n);
	~MPR() { };
	virtual void draw();
protected:
	int m;
	int n;
};

class Hipo : public Entity
{
public:
	Hipo(int nP, int nQ, GLfloat a, GLfloat b, GLfloat c);
	~Hipo() { };
	glm::dmat4 getMat(GLdouble t);
	virtual void draw();
protected:
	int nP;
	int nQ;
	GLfloat a;
	GLfloat b;
	GLfloat c;
};

class CompoundEntity : public Entity
{
public:
	CompoundEntity() {};
	std::vector<Entity*> entities;
	virtual void render(glm::dmat4 const& modelViewMat);
	void moveBB8();
	GLdouble getTbb8();
	GLdouble tBB8 = 0.0;
	bool mov = false;
	void setMov() { mov = true; };
protected:
};

class QuadricEntity : public Entity
{
public:
	QuadricEntity() {};
	GLfloat a;
	GLfloat b;
	GLfloat c;
	GLdouble r;
protected:
};

class Sphere : public QuadricEntity
{
public:
	Sphere(GLdouble l);
	~Sphere() {gluDeleteQuadric(sphere);};
	virtual void draw();
protected:
	GLUquadricObj * sphere;
};

class Cylinder : public QuadricEntity
{
public:
	Cylinder() {};
protected:

};

class SemiEsfera : public Entity
{
public:
	SemiEsfera(int n);
	~SemiEsfera() { };
	virtual void draw();
	GLfloat a;
	GLfloat b;
	GLfloat c;
protected:
	int m;
	int n;
};
#endif //_H_Entities_H_