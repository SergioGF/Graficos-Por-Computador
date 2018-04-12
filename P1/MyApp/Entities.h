//#pragma once
#ifndef _H_Entities_H_
#define _H_Entities_H_

#include <GL/freeglut.h>
#include <glm.hpp>
#include "Mesh.h"
#include "Texture.h"

//-------------------------------------------------------------------------

class Entity
{
public:
	Entity() : modelMat(1.0) { };
	virtual ~Entity() { delete mesh; };

	virtual void render(glm::dmat4 const& modelViewMat);
	virtual void RotacionDiabolo();
	virtual void update(GLuint timeElapsed);
	//virtual void guardarImagen();

protected:
	Mesh * mesh = nullptr;
	glm::dmat4 modelMat;
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
};

class Cubo : public Entity
{
public:
	Cubo(GLdouble x);
	~Cubo() { };
	virtual void draw();
	virtual void render(glm::dmat4 const& modelViewMat);
protected:
	Mesh * mesh2 = nullptr;
	GLdouble altura;
};

class Suelo : public Entity
{
public:
	Suelo(GLdouble w, GLdouble h, GLdouble a);
	~Suelo() { };
	virtual void draw();
	virtual void render(glm::dmat4 const& modelViewMat);

protected:
	GLdouble altura;
};


class Espejo : public Entity
{
public:
	Espejo(GLdouble w, GLdouble h);
	~Espejo() { };
	virtual void draw();
	virtual void update(GLuint timeElapsed);
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
	virtual void render(glm::dmat4 const& modelViewMat);
};

class Planta : public Entity
{
public:
	Planta(GLdouble w, GLdouble h, GLdouble w_s, GLdouble h_s);
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

#endif //_H_Entities_H_