#include "Mesh.h"
#include <math.h>
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


glm::dmat4 Mesh::getM(){ 
	
	return m; };
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

Mesh* Mesh::generaMallaPorRevolucion(int m, int n, glm::dvec3* perfil) {
	Mesh* mesh = new Mesh();
	mesh->numVertices = n * m;
	mesh->vertices = new dvec3[mesh->numVertices];

	for (int i = 0; i < n; i++) { // Generar el perfil i-ésimo
		double theta = i * 2 * 3.1415926535 / n;
		double c = cos(theta);
		double s = sin(theta);
		// R_y es la matriz de rotación sobre el eje Y
		for (int j = 0; j < m; j++) {
			int indice = i * m + j;
			// Transformar el punto j-ésimo del perfil original
			double x = c * perfil[j][0] + s * perfil[j][2];
			double z = -s * perfil[j][0] + c * perfil[j][2];
			dvec3 p = dvec3(x, perfil[j].y, z);
			mesh->vertices[indice] = p;
		}
	}
	mesh->normalize(m,n);
	return mesh;
}

void Mesh::normalize(int mm, int nn) {
	normals = new dvec3[mm*nn];
	// Se ponen al vector nulo todas las componentes de normals

	for (int i = 0; i < this->numVertices;i++)
		normals[i] = dvec3(0, 0, 0);

	for (int i = 0; i < nn; i++)
		for (int j = 0; j < mm - 1; j++) {
			int indice = i * mm + j;
			// Por cada cara a la que pertenece el vértice índice,
			// se determinan 3 índices i0, i1, i2 de 3 vértices consecutivos de esa cara
			dvec3 aux0 = vertices[indice];//vértice de i0; 
			dvec3 aux1 = vertices[(indice+mm)%(mm*nn)]; 
			dvec3 aux2 = vertices[(indice+mm+1) %(mm*nn)];
			dvec3 norm = glm::cross(aux2 - aux1, aux0 - aux1);
			normals[indice] += norm; 
			normals[(indice+mm)% (nn*mm)] += norm;
			normals[(indice+mm+1) % (nn*mm)] += norm; 
			normals[indice+1] += norm;
		}
	for (int i = 0; i < nn; i++) {
		for (int j = 0; j < mm; j++) {
			int indice = i * mm + j;
			normals[indice] = glm::normalize(normals[indice]);
		}
	}
}

glm::dmat4 Mesh::getMBB8(GLdouble t) {
	return m;
}
void HipoMesh::normalize(int mm, int nn) {
	normals = new dvec3[numVertices];
	for (int i = 0; i < numVertices; i++) {
		this->normals[i] = dvec3(0, 0, 0);
	}
	GLuint n = nQ;
	GLuint m = nP;
	for (GLuint i = 0; i < n; i++) {
		for (GLuint j = 0; j < m - 1; j++) {
			GLuint indice = i * m + j;
			dvec3 aux0 = vertices[indice];
			dvec3 aux1 = vertices[(indice + m) % (n*m)];
			dvec3 aux2 = vertices[(indice + m + 1) % (n*m)];
			dvec3 norm = glm::cross(aux2 - aux1, aux0 - aux1);

			normals[indice] += norm;
			normals[(indice + m) % (n*m)] += norm;
			normals[(indice + m + 1) % (n*m)] += norm;
			normals[indice + 1] += norm;
		}
	}

	for (int i = 0; i < numVertices; i++)
		this->normals[i] = glm::normalize(normals[i]);
}
HipoMesh::HipoMesh(int nP,int nQ, GLfloat a, GLfloat b, GLfloat c) {
	int cont = 0;
	this->nP = nP;
	this->nQ = nQ;
	this->a = a;
	this->b = b;
	this->c = c;
	this->numVertices = nP + nP * nQ;
	this->vertices = new dvec3[numVertices];
	for (int i = 0; i < numVertices; i++) {
		this->vertices[i] = dvec3(0, 0, 0);
	}
	GLdouble radio = 0.5;
	creaBase();
	GLdouble t = 0.0;
	cargaMatriz(t);
	creaVerticesIniciales();
	double PI = 3.1415926535897932384;
	GLdouble saltoEntreRodajas = 8*PI/nQ;
	cont++;
	for (int i = 1; i < nQ; i++) {
		t += saltoEntreRodajas;
		cargaMatriz(t);
		creaRodaja(i);
	}
}

void HipoMesh::creaBase() {
	GLdouble radio = 0.5;
	base = new dvec4[nP];
	for (int i = 0; i < nP; i++) {
		GLdouble theta = i * 3.14 * 2.0f / (GLdouble)nP;
		double c = cos(theta);
		double s = sin(theta);
		dvec4 aux0 = dvec4(c*radio, s*radio, 0.0, 1.0);
		//dvec3 aux0 = dvec3(c*radio, s*radio, (double)0.0);
		base[i] = aux0;
	}
}

void HipoMesh::creaVerticesIniciales() {
	//cargaMatriz(0);
	creaRodaja(0);
}

void HipoMesh::creaRodaja(int v) {
	for (int i = 0; i < nP; i++) {
		vertices[i + v * nP] = multiplicacionMatriz(m, base[i]);
	}
}

glm::dvec3 HipoMesh::multiplicacionMatriz(dmat4 m, dvec4 bi) {
	dvec3 resultado;
	double suma = 0.0;
	for (int i = 0; i < 3; i++) {
		for (int j = 0; j < 4; j++) {
			suma += m[i][j] * bi[j];
		}
		resultado[i] = suma;
		suma = 0.0;
	}
	return resultado;
}

void HipoMesh::cargaMatriz(GLdouble t) {
	dvec3 v_curva = curva(t);
	dvec3 v_derivada = derivada(t);
	dvec3 v_segunda = segundaDerivada(t);
	dvec3 t_vector = glm::normalize(v_derivada);
	dvec3 b_vector = glm::normalize(glm::cross(v_derivada,v_segunda));
	dvec3 n_vector = glm::cross(b_vector, t_vector);
	 for (int i = 0; i < 4; i++) {
		 for (int j = 0; j < 4; j++) {
			 if(i<3){
				 if (j == 0) {
					 m[i][j] = n_vector[i];
				 }
				 else if (j == 1) {
					 m[i][j] = b_vector[i];
				 }
				 else if (j == 2) {
					 m[i][j] = t_vector[i];

				 }
				 else {
					 m[i][j] = v_curva[i];
				 }
			}
			else{
				 if (j == 3)
					 m[i][j] = 1.0;
				 else
					 m[i][j] = 0.0;
			 }
		 }
	 }
}

glm::dvec4 HipoMesh::curva(GLdouble t) {

	return glm::dvec4((a - b)*cos(t) + c*cos(t*((a - b) / b)),
		0,
		(a - b)*sin(t) - c * sin(t*((a - b) / b)),0);
}

glm::dvec3 HipoMesh::derivada(GLdouble t) {
	return glm::dvec3(-(a - b)*sin(t) - c * ((a - b) / b)*sin(t*((a - b) / b)),
		0,
		(a - b)*cos(t) - c * ((a - b) / b)*cos(t*((a - b) / b)));
}

glm::dvec3 HipoMesh:: segundaDerivada(GLdouble t) {

	return dvec3(-(a - b)*cos(t) - c * ((a - b) / b)*((a - b) / b)*cos(t*((a - b) / b)),
		0,
		-(a - b)*sin(t) + c * ((a - b) / b)*((a - b) / b)*sin(t*((a - b) / b)));
}

glm::dmat4 HipoMesh::getMBB8(GLdouble t) {
	dvec4 v_curva = curva(t);
	dvec3 v_derivada = derivada(t);
	dvec3 v_segunda = segundaDerivada(t);
	dvec3 t_vector = glm::normalize(v_derivada);
	dvec3 b_vector = glm::normalize(glm::cross(v_derivada, v_segunda));
	dvec3 n_vector = glm::cross(b_vector, t_vector);
	for (int i = 0; i < 4; i++) {
		for (int j = 0; j < 4; j++) {
			if (i<3) {
				if (j == 0) {
					m[i][j] = n_vector[i];
				}
				else if (j == 1) {
					m[i][j] = b_vector[i];
				}
				else if (j == 2) {
					m[i][j] = t_vector[i];

				}
				else {
					m[i][j] = 0.0;
				}
			}
			else {
				if (j == 3)
					m[i][j] = 1.0;
				else {
					GLdouble aux3 = v_curva[i];
					m[i][j] = v_curva[i];
				}
					
			}
		}
	}

	return m;
}