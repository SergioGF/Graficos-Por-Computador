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
	modelMat = translate(modelMat, dvec3(250, 0, -150));
	modelMat = rotate(modelMat, radians(30.0), dvec3(0, 1, 0));
	altura = h;
	mesh = Mesh::generateTriPyramidTex(r, h);
	textura.load("..\\Bmps\\floris.bmp");
	//    texture.load("..\\Bmps\\floris.bmp");
}
//-------------------------------------------------------------------------

void Diabolo::draw()
{
	textura.bind();
	mesh->draw();
	textura.unbind();
}

void Diabolo::render(const glm::dmat4 &modelViewMat) {
	glMatrixMode(GL_MODELVIEW);
	dmat4 aMat = modelViewMat * modelMat;
	aMat = translate(aMat, dvec3(0, 0, -altura));

	glLoadMatrixd(value_ptr(aMat));
	//    glColor3d(0.0, 0.0, 0.0);
	draw();

	aMat = rotate(aMat, radians(180.0), dvec3(0.0, 0.0, 1.0));
	glLoadMatrixd(value_ptr(aMat));
	//    glColor3d(1.0, 0.0, 0.0);
	draw();

	aMat = modelViewMat * modelMat;
	aMat = rotate(aMat, radians(180.0), dvec3(0.0, 1.0, 0.0));
	aMat = translate(aMat, dvec3(0, 0, -altura));
	glLoadMatrixd(value_ptr(aMat));
	//    glColor3d(0.0, 0.0, 1.0);
	draw();

	aMat = rotate(aMat, radians(180.0), dvec3(0.0, 0.0, 1.0));
	glLoadMatrixd(value_ptr(aMat));
	//    glColor3d(0.0, 1.0, 0.0);
	draw();
}

void Diabolo::RotacionDiabolo() {
	glMatrixMode(GL_MODELVIEW);
	modelMat = rotate(modelMat, radians(2.0), dvec3(0.0, 0.0, 1.0));
	glLoadMatrixd(value_ptr(modelMat));
}

void Diabolo::update(GLuint timeElapsed) {
	RotacionDiabolo();
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

Cubo::Cubo(GLdouble h) : Entity()
{
	altura = h;
	modelMat = translate(modelMat, dvec3(-altura / 2, 0, 0));
	textura.load("..\\Bmps\\container.bmp");
	textura2.load("..\\Bmps\\chuches.bmp");
	//    texture.load("..\\Bmps\\container.bmp");
	mesh = Mesh::generateContCuboTex(h);
	mesh2 = Mesh::generateRectangleTex(h, h);
}

void Cubo::drawMesh()
{
	textura.bind();
	mesh->draw();
	textura.unbind();
}

void Cubo::drawMeshAux()
{
	textura.bind();
	mesh2->draw();
	textura.unbind();
}

void Cubo::drawMeshAux2()
{
	textura2.bind();
	mesh->draw();
	textura2.unbind();
}

void Cubo::render(const glm::dmat4 &modelViewMat) {
	glMatrixMode(GL_MODELVIEW);
	dmat4 aMat = modelViewMat * modelMat;
	glLoadMatrixd(value_ptr(aMat));
	//para poner textura por dentro y por fuera
	glEnable(GL_CULL_FACE);
	glPolygonMode(GL_FRONT, GL_FILL);
	drawMesh();
	glDisable(GL_CULL_FACE);
	glPolygonMode(GL_BACK, GL_FILL);
	drawMeshAux2();

	//glPolygonMode(GL_FRONT, GL_LINE);
	//glPolygonMode(GL_BACK, GL_POINT);

	aMat = modelViewMat * modelMat;
	aMat = translate(aMat, dvec3(0, altura*0.85, 0));
	aMat = translate(aMat, dvec3(0, 0, -(altura*0.15)));
	aMat = rotate(aMat, radians(45.0), dvec3(1.0, 0.0, 0.0));

	glLoadMatrixd(value_ptr(aMat));
	drawMeshAux();
	glPolygonMode(GL_FRONT, GL_FILL);

}

Suelo::Suelo(GLdouble w, GLdouble h) : Entity()
{
	modelMat = translate(modelMat, dvec3(0, -100, 0));
	modelMat = rotate(modelMat, radians(90.0), dvec3(1, 0, 0));
	mesh = Mesh::generateSueloTex(w, h);
	textura.load("..\\Bmps\\baldosaC.bmp");
}
void Suelo::draw()
{
	//glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
	textura.bind();
	mesh->draw();
	textura.unbind();
	//glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
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
	modelMat = translate(modelMat, dvec3(410.0, (-x / 2) + 100, -410.0));
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



Planta::Planta(GLdouble l) : Entity()
{
	modelMat = translate(modelMat, dvec3(410.0, (-l / 2) + 100.0, -410.0));
	textura.load("..\\Bmps\\grass.bmp", ivec3(0, 0, 0), 0);
	mesh = Mesh::generateRectangleTex(l, l);
}
//-------------------------------------------------------------------------

void Planta::draw()
{
	glDepthMask(GL_FALSE);
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	textura.bind();
	mesh->draw();
	textura.unbind();
	glDisable(GL_BLEND);
	glDepthMask(GL_TRUE);
}


void Planta::render(const glm::dmat4 &modelViewMat) {
	glMatrixMode(GL_MODELVIEW);
	dmat4 aMat = modelViewMat * modelMat;
	glLoadMatrixd(value_ptr(aMat));
	draw();
	aMat = rotate(aMat, radians(45.0), dvec3(0.0, 1.0, 0.0));
	glLoadMatrixd(value_ptr(aMat));
	draw();
	aMat = rotate(aMat, radians(45.0), dvec3(0.0, 1.0, 0.0));
	glLoadMatrixd(value_ptr(aMat));
	draw();
	aMat = rotate(aMat, radians(45.0), dvec3(0.0, 1.0, 0.0));
	glLoadMatrixd(value_ptr(aMat));
	draw();
}

MPR::MPR(int n) {
	this->m = 3; //número de puntos del perfil
	this->n = n;
	dvec3* perfil = new dvec3[3];
	perfil[0] = dvec3(0.0, 0.0, 0.0);
	perfil[1] = dvec3(25.0,0.0,0.0);
	perfil[2] = dvec3(0.0,75.0,0.0);

	this->mesh = Mesh::generaMallaPorRevolucion(m, n, perfil);
}

void MPR::draw() {
	dvec3* vertices = mesh->getVertices();
	//dvec4* colors = mesh->getColours();
	dvec3* normals = mesh->getNormals();
	glColor3d(0.0,0.0,1.0);
	if (vertices != nullptr) {
		glEnableClientState(GL_VERTEX_ARRAY);
		glEnableClientState(GL_NORMAL_ARRAY);
		glVertexPointer(3, GL_DOUBLE, 0, vertices);
		glNormalPointer(GL_DOUBLE, 0, normals);
		/*if (colors != nullptr) {
			glEnableClientState(GL_COLOR_ARRAY);
			glColorPointer(4, GL_DOUBLE, 0, colors);
		}*/
	}
	// Definición de las caras
	glPolygonMode(GL_FRONT, GL_FILL);
	for (int i = 0; i<n; i++) { // Unir el perfil i-ésimo con el (i+1)%n-ésimo
		for (int j = 0; j<m - 1; j++) { // Esquina inferior-izquierda de una cara
			int indice = i * m + j;
			unsigned int stripIndices[] =
			{ indice, (indice + m) % (n*m),
				(indice + m + 1) % (n*m), indice + 1 };
			glDrawElements(GL_POLYGON, 4, GL_UNSIGNED_INT, stripIndices);
			// o GL_POLYGON, si se quiere las caras con relleno
		}
	}
	// Después del dibujo de los elementos por índices,
	// se deshabilitan los vertex arrays, como es habitual
	glDisableClientState(GL_VERTEX_ARRAY);
	glDisableClientState(GL_NORMAL_ARRAY);
}

Hipo::Hipo(int nP, int nQ, GLfloat a, GLfloat b, GLfloat c) {
	this->nP = nP;
	this->nQ = nQ;
	this->a = a;
	this->b = b;
	this->c = c;
	this->mesh = new HipoMesh(nP, nQ, a, b, c);
	mesh->normalize(nP,nQ);
}

void Hipo::draw() {
	dvec3* vertices = mesh->getVertices();
	//dvec4* colors = mesh->getColours();
	dvec3* normals = mesh->getNormals();
	int numeroCaras = nQ * nP;

	glColor3d(0.0,0.0,1.0);
	if (vertices != nullptr) {
		glEnableClientState(GL_VERTEX_ARRAY);
		glEnableClientState(GL_NORMAL_ARRAY);
		glVertexPointer(3, GL_DOUBLE, 0, vertices);
		glNormalPointer(GL_DOUBLE, 0, normals);
		/*if (colors != nullptr) {
		glEnableClientState(GL_COLOR_ARRAY);
		glColorPointer(4, GL_DOUBLE, 0, colors);
		}*/
	}
	// Definición de las caras
	glPolygonMode(GL_FRONT, GL_LINE);
	int indiceCara = 0;
	for (int i = 0; i < nQ; i++) { // Unir el perfil i-ésimo con el (i+1)%n-ésimo
		int cara = i;
		for (int j = 0; j < nP; j++) { // Esquina inferior-izquierda de una cara
			//4,0,5,9
			int indice = i * nP + j;
			int indice1 = (indice + nP) % (nQ*nP);
			int indice2 = 0;
			int indice3 = 0;
			if (j == nP - 1) {
				/*
				vn[2] = new VerticeNormal((indice + 1) % numeroVertices, indiceCara);
				vn[3] = new VerticeNormal(indice - nP + 1, indiceCara)
				*/
				indice2 = (indice + 1) % (nQ*nP);
				indice3 = indice -nP + 1;

			}
			else {
				/*
				vn[2] = new VerticeNormal((indice + 1 + nP) % numeroVertices, indiceCara);
				vn[3] = new VerticeNormal(indice + 1, indiceCara);
				*/
				indice2 = (indice + nP + 1) % (nQ*nP);
				indice3 = indice + 1;
			}

				unsigned int stripIndices[] = { indice, indice1, indice2, indice3 };
				glDrawElements(GL_LINE_LOOP,4, GL_UNSIGNED_INT, stripIndices);
		}
	}
	// Después del dibujo de los elementos por índices,
	// se deshabilitan los vertex arrays, como es habitual
	glDisableClientState(GL_VERTEX_ARRAY);
	glDisableClientState(GL_NORMAL_ARRAY);
}

Sphere::Sphere(GLdouble l) {
	r = l;
	sphere = gluNewQuadric();
	//gluQuadricTexture(sphere, GLU_TRUE);
}

void Sphere::draw() {
	glColor3d(a,b,c);
	// En la Práctica 2, el color se debe incorporar con tres
	// atributos en Entity de tipo GLfloat o con un nuevo atributo de
	// clase Color que tiene 3 atributos de tipo GLfloat
	gluQuadricDrawStyle(sphere, GLU_FILL);
	//texture.bind(GL_MODULATE);
	gluSphere(sphere, r, 50, 50);
	//texture.unbind();
}

void CompoundEntity::render(glm::dmat4 const& modelViewMat) {
	glMatrixMode(GL_MODELVIEW);
	int i = 0;
	dmat4 aMat = modelViewMat * this->modelMat;
	aMat = rotate(aMat, glm::radians(45.0), glm::dvec3(0, 1, 0));
	for each (Entity* it in entities)
	{
		dmat4 aMatAux = aMat;
		if (i == 0) {
			aMatAux = translate(aMatAux, glm::dvec3(0, 20, 0));
		}
		else if (i == 1) {

		}
		else if (i == 2) {
			aMatAux = translate(aMatAux, glm::dvec3(-3, 25, 6));
		}
		else if (i == 3) {
			aMatAux = translate(aMatAux, glm::dvec3(3, 24, 8));
		}
			it->render(aMatAux);
			i++;
	}
};

SemiEsfera::SemiEsfera(int l) {
	this->m = 53; //número de puntos del perfil
	this->n = 30;

	dvec3* perfil = new dvec3[23];
	perfil[0] = dvec3(0.0, 0.0, 0.0);
	perfil[1] = dvec3(l, 0.0, 0.0);

	double varAng = 90 / 20;
	double angulo = 0.0;
	for (int i = 2; i < 22;i++) {
		angulo = angulo + varAng;
		perfil[i] = dvec3(l*cos(glm::radians(angulo)),l*sin(glm::radians(angulo)),0.0);
	}
	perfil[22] = dvec3(0.0, l, 0.0);
	this->mesh = Mesh::generaMallaPorRevolucion(m, n, perfil);
}

void SemiEsfera::draw() {
	dvec3* vertices = mesh->getVertices();
	//dvec4* colors = mesh->getColours();
	dvec3* normals = mesh->getNormals();
	glColor3d(a, b, c);
	if (vertices != nullptr) {
		glEnableClientState(GL_VERTEX_ARRAY);
		glEnableClientState(GL_NORMAL_ARRAY);
		glVertexPointer(3, GL_DOUBLE, 0, vertices);
		glNormalPointer(GL_DOUBLE, 0, normals);
		/*if (colors != nullptr) {
		glEnableClientState(GL_COLOR_ARRAY);
		glColorPointer(4, GL_DOUBLE, 0, colors);
		}*/
	}
	// Definición de las caras
	glPolygonMode(GL_FRONT, GL_FILL);
	for (int i = 0; i<n; i++) { // Unir el perfil i-ésimo con el (i+1)%n-ésimo
		for (int j = 0; j<m - 1; j++) { // Esquina inferior-izquierda de una cara
			int indice = i * m + j;
			unsigned int stripIndices[] =
			{ indice, (indice + m) % (n*m),
				(indice + m + 1) % (n*m), indice + 1 };
			glDrawElements(GL_POLYGON, 4, GL_UNSIGNED_INT, stripIndices);
			// o GL_POLYGON, si se quiere las caras con relleno
		}
	}
	// Después del dibujo de los elementos por índices,
	// se deshabilitan los vertex arrays, como es habitual
	glDisableClientState(GL_VERTEX_ARRAY);
	glDisableClientState(GL_NORMAL_ARRAY);
}



