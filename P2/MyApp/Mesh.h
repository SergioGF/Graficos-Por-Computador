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
	glm::dvec3* getNormals() { return normals; };
protected:
	GLuint numVertices = 0;
	GLuint type = GL_POINTS;
	glm::dvec3* vertices = nullptr;
	glm::dvec4* colors = nullptr;
	glm::dvec2* texCoords = nullptr;
	glm::dvec3* normals = nullptr;
};


class HipoMesh: public Mesh
{
public:
	HipoMesh(int nP, int nQ, GLfloat a, GLfloat b, GLfloat c);
	void creaBase(); // Guarda en base el polígono que aproxima la circunferencia del tubo
	void creaVerticesIniciales(); // Añade los primeros nP vértices
	void creaRodaja(int v); // Añade nP nuevos vértices, a partir de la componente v
	void cargaMatriz(GLdouble t); // Define la matriz m para t
	glm::dvec3 multiplicacionMatriz(glm::dmat4 m, glm::dvec4 bi);
	glm::dvec3 curva(GLdouble t);
	glm::dvec3 derivada(GLdouble t);
	glm::dvec3 segundaDerivada(GLdouble t);
protected:
	int nP; // Número de lados del polígono que aproxima la circunferencia que define el tubo
	int nQ; // Número de rodajas que forman la hipotrocoide
	GLfloat a, b, c; // Valores de los parámetros de la ecuación de la hipotrocoide
	glm::dmat4 m; // Matriz de paso de coordenadas locales a globales
	glm::dvec4* base; // Perfil del nP-ágono que aproxima la circunferencia que define el tubo
};

//-------------------------------------------------------------------------

#endif //_H_Scene_H_