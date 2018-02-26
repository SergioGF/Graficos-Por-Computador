//#pragma once
#ifndef _H_Entities_H_
#define _H_Entities_H_

#include <GL/freeglut.h>
#include <glm.hpp>
#include "Mesh.h"

//-------------------------------------------------------------------------

class Entity 
{
public:
  Entity() : modelMat(1.0) { };
  virtual ~Entity() { delete mesh; };

  virtual void render(glm::dmat4 const& modelViewMat);
  virtual void RotacionDiabolo();
  
protected:
  Mesh* mesh = nullptr;
  glm::dmat4 modelMat;
  GLdouble ang = 60.0;
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
	virtual void render(glm:: dmat4 const& modelViewMat);
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
};

#endif //_H_Entities_H_