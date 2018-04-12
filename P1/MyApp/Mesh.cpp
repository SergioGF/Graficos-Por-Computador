#include "Mesh.h"

using namespace glm;

//-------------------------------------------------------------------------

Mesh ::~Mesh(void)
{
	delete[] vertices;
	delete[] colors;
	delete[] texCoords;
}
//-------------------------------------------------------------------------

void Mesh::draw()
{
	if (vertices != nullptr) {
		glEnableClientState(GL_VERTEX_ARRAY);
		glVertexPointer(3, GL_DOUBLE, 0, vertices);  // number of coordinates per vertex, type of each coordinate 
		if (colors != nullptr) {
			glEnableClientState(GL_COLOR_ARRAY);
			glColorPointer(4, GL_DOUBLE, 0, colors);   // number of coordinates per color, type of each coordinate 
		}
		if (texCoords != nullptr) {
			glEnableClientState(GL_TEXTURE_COORD_ARRAY);
			glTexCoordPointer(2, GL_DOUBLE, 0, texCoords);
		}

		glDrawArrays(type, 0, numVertices);   // kind of primitives, first, count

		glDisableClientState(GL_TEXTURE_COORD_ARRAY);
		glDisableClientState(GL_COLOR_ARRAY);
	}
}
//-------------------------------------------------------------------------

Mesh * Mesh::generateAxesRGB(GLdouble l)
{
	Mesh* m = new Mesh();
	m->type = GL_LINES;
	m->numVertices = 6;

	m->vertices = new dvec3[m->numVertices];
	m->vertices[0] = dvec3(0.0, 0.0, 0.0);
	m->vertices[1] = dvec3(l, 0.0, 0);
	m->vertices[2] = dvec3(0, 0.0, 0.0);
	m->vertices[3] = dvec3(0.0, l, 0.0);
	m->vertices[4] = dvec3(0.0, 0.0, 0.0);
	m->vertices[5] = dvec3(0.0, 0.0, l);

	m->colors = new dvec4[m->numVertices];
	m->colors[0] = dvec4(1.0, 0.0, 0.0, 1.0);
	m->colors[1] = dvec4(1.0, 0.0, 0.0, 1.0);
	m->colors[2] = dvec4(0.0, 1.0, 0.0, 1.0);
	m->colors[3] = dvec4(0.0, 1.0, 0.0, 1.0);
	m->colors[4] = dvec4(0.0, 0.0, 1.0, 1.0);
	m->colors[5] = dvec4(0.0, 0.0, 1.0, 1.0);

	return m;
}
//-------------------------------------------------------------------------

Mesh * Mesh::generateTriangle(GLdouble r)
{
	Mesh* m = new Mesh();
	m->type = GL_TRIANGLES;
	m->numVertices = 3;

	m->vertices = new dvec3[m->numVertices];
	m->vertices[0] = dvec3(r*cos(radians(90.0)), r*sin(radians(90.0)), 0);
	m->vertices[1] = dvec3(r*cos(radians(210.0)), r*sin(radians(210.0)), 0);
	m->vertices[2] = dvec3(r*cos(radians(330.0)), r*sin(radians(330.0)), 0);

	m->colors = new dvec4[m->numVertices];
	m->colors[0] = dvec4(1.0, 0.0, 0.0, 1.0);
	m->colors[1] = dvec4(1.0, 0.0, 0.0, 1.0);
	m->colors[2] = dvec4(1.0, 0.0, 0.0, 1.0);


	return m;
}

Mesh * Mesh::generateTriangleRGB(GLdouble r)
{
	Mesh* m = new Mesh();
	m->type = GL_TRIANGLES;
	m->numVertices = 3;

	m->vertices = new dvec3[m->numVertices];
	m->vertices[0] = dvec3(r*cos(radians(90.0)), r*sin(radians(90.0)), 0);
	m->vertices[1] = dvec3(r*cos(radians(210.0)), r*sin(radians(210.0)), 0);
	m->vertices[2] = dvec3(r*cos(radians(330.0)), r*sin(radians(330.0)), 0);

	m->colors = new dvec4[m->numVertices];
	m->colors[0] = dvec4(1.0, 0.0, 0.0, 1.0);
	m->colors[1] = dvec4(0.0, 1.0, 0.0, 1.0);
	m->colors[2] = dvec4(0.0, 0.0, 1.0, 1.0);


	return m;
}

Mesh * Mesh::generateTriPyramid(GLdouble r, GLdouble h)
{
	Mesh* m = new Mesh();
	m->type = GL_TRIANGLE_FAN;
	m->numVertices = 5;

	m->vertices = new dvec3[m->numVertices];
	m->vertices[0] = dvec3(0.0, 0.0, h);
	m->vertices[1] = dvec3(r*cos(radians(90.0)), r*sin(radians(90.0)), 0);
	m->vertices[2] = dvec3(r*cos(radians(210.0)), r*sin(radians(210.0)), 0);
	m->vertices[3] = dvec3(r*cos(radians(330.0)), r*sin(radians(330.0)), 0);
	m->vertices[4] = dvec3(r*cos(radians(90.0)), r*sin(radians(90.0)), 0);

	/*m->colors = new dvec4[m->numVertices];
	m->colors[0] = dvec4(1.0, 0.0, 0.0, 1.0);
	m->colors[1] = dvec4(0.0, 1.0, 0.0, 1.0);
	m->colors[2] = dvec4(0.0, 0.0, 1.0, 1.0);
	m->colors[3] = dvec4(0.0, 0.0, 1.0, 1.0);
	m->colors[4] = dvec4(0.0, 0.0, 1.0, 1.0);*/


	return m;
}

Mesh * Mesh::generateContCubo(GLdouble l)
{
	Mesh* m = new Mesh();
	m->type = GL_TRIANGLE_STRIP;
	m->numVertices = 10;

	m->vertices = new dvec3[m->numVertices];
	m->vertices[0] = dvec3(-l / 2, l / 2, l / 2);
	m->vertices[1] = dvec3(-l / 2, -l / 2, l / 2);
	m->vertices[2] = dvec3(l / 2, l / 2, l / 2);
	m->vertices[3] = dvec3(l / 2, -l / 2, l / 2);


	m->vertices[4] = dvec3(l / 2, l / 2, -l / 2);
	m->vertices[5] = dvec3(l / 2, -l / 2, -l / 2);
	m->vertices[6] = dvec3(-l / 2, l / 2, -l / 2);
	m->vertices[7] = dvec3(-l / 2, -l / 2, -l / 2);

	m->vertices[8] = dvec3(-l / 2, l / 2, l / 2);
	m->vertices[9] = dvec3(-l / 2, -l / 2, l / 2);

	m->colors = new dvec4[m->numVertices];
	m->colors[0] = dvec4(0.0, 0.0, 1.0, 1.0);
	m->colors[1] = dvec4(0.0, 0.0, 1.0, 1.0);
	m->colors[2] = dvec4(0.0, 0.0, 1.0, 1.0);
	m->colors[3] = dvec4(0.0, 0.0, 1.0, 1.0);
	m->colors[4] = dvec4(0.0, 0.0, 1.0, 1.0);
	m->colors[5] = dvec4(0.0, 0.0, 1.0, 1.0);
	m->colors[6] = dvec4(0.0, 0.0, 1.0, 1.0);
	m->colors[7] = dvec4(0.0, 0.0, 1.0, 1.0);
	m->colors[8] = dvec4(0.0, 0.0, 1.0, 1.0);
	m->colors[9] = dvec4(0.0, 0.0, 1.0, 1.0);

	return m;
}

Mesh * Mesh::generateRectangle(GLdouble w, GLdouble h)
{
	Mesh* m = new Mesh();
	m->type = GL_TRIANGLE_STRIP;
	m->numVertices = 4;

	m->vertices = new dvec3[m->numVertices];
	/*m->vertices[0] = dvec3(h*cos(radians(45.0)), w*sin(radians(45.0)), 0);
	m->vertices[1] = dvec3(h*cos(radians(135.0)), w*sin(radians(135.0)), 0);
	m->vertices[2] = dvec3(h*cos(radians(225.0)), w*sin(radians(225.0)), 0);
	m->vertices[3] = dvec3(h*cos(radians(315.0)), w*sin(radians(315.0)), 0);
	m->vertices[4] = dvec3(h*cos(radians(45.0)), w*sin(radians(45.0)), 0);*/

	m->vertices[0] = dvec3(-h / 2, w / 2, 0);
	m->vertices[1] = dvec3(-h / 2, -w / 2, 0);
	m->vertices[2] = dvec3(h / 2, w / 2, 0);
	m->vertices[3] = dvec3(h / 2, -w / 2, 0);

	m->colors = new dvec4[m->numVertices];
	m->colors[0] = dvec4(0.0, 0.0, 0.0, 0.0);
	m->colors[1] = dvec4(0.0, 0.0, 0.0, 0.0);
	m->colors[2] = dvec4(0.0, 0.0, 0.0, 0.0);
	m->colors[3] = dvec4(0.0, 0.0, 0.0, 0.0);

	return m;
}

Mesh* Mesh::generateRectangleTex(GLdouble w, GLdouble h)
{
	Mesh *m = generateRectangle(w, h);
	m->texCoords = new dvec2[m->numVertices];
	m->texCoords[0] = dvec2(0, 1);
	m->texCoords[1] = dvec2(0, 0);
	m->texCoords[2] = dvec2(1, 1);
	m->texCoords[3] = dvec2(1, 0);
	return m;
}

Mesh * Mesh::generateContCuboTex(GLdouble l)
{
	Mesh* m = generateContCubo(l);
	m->texCoords = new dvec2[m->numVertices];
	m->texCoords[0] = dvec2(0, 1);
	m->texCoords[1] = dvec2(0, 0);
	m->texCoords[2] = dvec2(1, 1);
	m->texCoords[3] = dvec2(1, 0);
	m->texCoords[4] = dvec2(2, 1);
	m->texCoords[5] = dvec2(2, 0);
	m->texCoords[6] = dvec2(3, 1);
	m->texCoords[7] = dvec2(3, 0);
	m->texCoords[8] = dvec2(4, 1);
	m->texCoords[9] = dvec2(4, 0);

	return m;
}

Mesh* Mesh::generateTriPyramidTex(GLdouble r, GLdouble h)
{
	Mesh *m = generateTriPyramid(r, h);
	m->texCoords = new dvec2[m->numVertices];
	m->texCoords[0] = dvec2(0, 1);
	m->texCoords[1] = dvec2(0, 0);
	m->texCoords[2] = dvec2(1, 1);
	m->texCoords[3] = dvec2(1, 0);
	m->texCoords[4] = dvec2(0, 1);
	return m;
}

Mesh* Mesh::generateSueloTex(GLdouble w, GLdouble h)
{
	Mesh *m = generateRectangle(w, h);
	m->texCoords = new dvec2[m->numVertices];
	m->texCoords[0] = dvec2(0, 4);
	m->texCoords[1] = dvec2(0, 0);
	m->texCoords[2] = dvec2(4, 4);
	m->texCoords[3] = dvec2(4, 0);
	return m;
}

Mesh* Mesh::generateEspejoTex(GLdouble w, GLdouble h)
{
	Mesh *m = generateRectangle(w, h);
	m->texCoords = new dvec2[m->numVertices];
	m->texCoords[0] = dvec2(0, 1);
	m->texCoords[1] = dvec2(0, 0);
	m->texCoords[2] = dvec2(1, 1);
	m->texCoords[3] = dvec2(1, 0);
	return m;
}

