//#pragma once
#ifndef _H_Mesh_H_
#define _H_Mesh_H_

#include <GL/freeglut.h>
#include <glm.hpp>

//-------------------------------------------------------------------------

class Mesh
{
public:
	static Mesh* generateAxesRGB(GLdouble l);
	static Mesh* generateTriangle(GLdouble r);
	static Mesh* generateTriangleRGB(GLdouble r);
	static Mesh* generateTriPyramid(GLdouble r, GLdouble h);
	static Mesh* generateContCubo(GLdouble l);
	static Mesh* generateRectangle(GLdouble w, GLdouble h);
	static Mesh* generateRectangleTex(GLdouble w, GLdouble h);
	static Mesh* generateContCuboTex(GLdouble l);
	static Mesh* generateTriPyramidTex(GLdouble r, GLdouble h);
	static Mesh* generateSueloTex(GLdouble w, GLdouble h);
	static Mesh* generateEspejoTex(GLdouble w, GLdouble h);
	static Mesh* generaMallaPorRevolucion(int m, int n, glm::dvec3* perfil);


	Mesh(void) { };
	~Mesh(void);
	virtual void draw();
	virtual void normalize(int mm, int nn);
	glm::dvec3* getVertices() { return vertices; };
	glm::dvec4* getColours() { return colors; };

protected:
	GLuint numVertices = 0;
	GLuint type = GL_POINTS;
	glm::dvec3* vertices = nullptr;
	glm::dvec4* colors = nullptr;
	glm::dvec2* texCoords = nullptr;
	glm::dvec3* normals = nullptr;
};

//-------------------------------------------------------------------------

#endif //_H_Scene_H_