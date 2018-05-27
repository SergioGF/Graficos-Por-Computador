#include "Scene.h"
#include <gtc/matrix_transform.hpp>  
#include <gtc/type_ptr.hpp>
//-------------------------------------------------------------------------

void Scene::init()
{ // OpenGL basic setting
	/*glClearColor(1.0, 1.0, 1.0, 1.0);  // background color (alpha=1 -> opaque)
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_TEXTURE_2D);
	camera->setAZ();*/
	
	glClearColor(0.6f, 0.7f, 0.8f, 1.0); // Fondo azul (o el que prefieras)
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_COLOR_MATERIAL);
	glEnable(GL_LIGHTING);
	glEnable(GL_LIGHT0); // Light0
	GLfloat d[] = { 1.0f, 1.0f, 1.0f, 1.0f };
	glLightfv(GL_LIGHT0, GL_DIFFUSE, d);
	GLfloat a[] = { 0.3f, 0.3f, 0.3f, 1.0f };
	glLightfv(GL_LIGHT0, GL_AMBIENT, a);
	GLfloat s[] = { 1.0f, 1.0f, 1.0f, 1.0f };
	glLightfv(GL_LIGHT0, GL_SPECULAR, s);
	GLfloat p[] = { 50.0f, 50.0f, 50.0f, 1.0f };
	glLightfv(GL_LIGHT0, GL_POSITION, p);
	camera->set3D();

	// lights
	// textures  

	// objetos
	//objetos.push_back(new ContCubo(200.0));
	//objetos.push_back(new TrianguloRGB(100.0));
	//objetos.push_back(new TriPyramid(100.0,200.0));
	//objetos.push_back(new Cubo(180.0));
	//objetos.push_back(new Diabolo(80.0, 140.0));
	//objetos.push_back(new Suelo(1000.0, 1000.0));
	//objetos.push_back(new EjesRGB(500.0));
	//objetos.push_back(new Espejo(100.0,100.0));
	//objetos.push_back(new Jardinera(180.0, 1000.0, 1000.0));
	//objetos.push_back(new Planta(180, 260, 1000.0, 1000.0));
	//objetos.push_back(new Planta(180));
	Hipo* h = new Hipo(10, 300, 7, 4, 2);
	//h->modelMat = glm::scale(h->modelMat,glm::dvec3(50.0,50.0,50.0));
	objetos.push_back(h);
	//objetos.push_back(new Sphere(100.0));
	
	this->objetos.push_back(new EjesRGB(500.0));
	//this->objetos.push_back(new Sphere(100.0));

	CompoundEntity* BB8 = new CompoundEntity();
	BB8->modelMat = glm::rotate(BB8->modelMat, glm::radians(45.0), glm::dvec3(0, 1, 0));
	BB8->modelMat = glm::scale(BB8->modelMat, glm::dvec3(0.01, 0.01, 0.01));

	CompoundEntity* cabeza = new CompoundEntity();
	BB8->entities.push_back(cabeza);

	SemiEsfera* sp1 = new SemiEsfera(10); // Cabeza
	sp1->a = 1.0;
	sp1->b = 1.0;
	sp1->c = 1.0;
	sp1->modelMat = glm::translate(sp1->modelMat, glm::dvec3(0, 20, 0)); 	// Se sube la cabeza
	cabeza->entities.push_back(sp1);

	CompoundEntity* cuerpo = new CompoundEntity();
	BB8->entities.push_back(cuerpo);

	Sphere* sp2 = new Sphere(20); // Cuerpo
	sp2->a = 0.9;
	sp2->b = 1.0;
	sp2->c = 0;
	cuerpo->entities.push_back(sp2);

	Sphere* sp3 = new Sphere(4);
	sp3->a = 0.0;
	sp3->b = 0.0;
	sp3->c = 0.0;
	sp3->modelMat = glm::translate(sp3->modelMat, glm::dvec3(0, 15, 15));
	cuerpo->entities.push_back(sp3);

	Sphere* spo1 = new Sphere(1.5); // Ojo izquierdo
	spo1->a = 0.0;
	spo1->b = 0.0;
	spo1->c = 0.0;				
	// Se sitúa el ojo en la cabeza
	spo1->modelMat = glm::translate(spo1->modelMat, glm::dvec3(-3, 26, 6));
	cabeza->entities.push_back(spo1);

	Sphere* spo2 = new Sphere(1); // Ojo derecho
	spo2->a = 0.0;
	spo2->b = 0.0;
	spo2->c = 0.0;
	// Se sitúa el ojo en la cabeza
	spo2->modelMat = glm::translate(spo2->modelMat, glm::dvec3(3, 26, 7));
	cabeza->entities.push_back(spo2);

	this->objetos.push_back(BB8);
}
//-------------------------------------------------------------------------

Scene::~Scene()
{ // free memory and resources 

	for each (Entity* it in objetos)
	{
		delete it;
	}
}
//-------------------------------------------------------------------------

void Scene::render()
{
	glMatrixMode(GL_MODELVIEW);

	viewport = camera->getVP();
	viewport->setSize(800, 600);
	int i = 0;
	for each (Entity* it in objetos)
	{

		i++;
		it->render(camera->getViewMat());
	}
}

void Scene::aumentarRotacion() {
	for each (Entity* it in objetos)
	{
		it->RotacionDiabolo();
	}
}

void Scene::update(GLuint timeElapsed) {
	for each (Entity* it in objetos)
	{
		it->update(timeElapsed);
	}
}

void Scene::moveBB8() {
	/*
	(NBT | 0)
	(c(t)| 1)
	Intercambiar c(t) por 0
	*/
	CompoundEntity *ob = (CompoundEntity*)objetos.at(2);
	GLdouble t = ob->getTbb8();
	
	Hipo *hi = (Hipo*)objetos.at(0);
	glm::dmat4 hipoamat = hi->getMat(t);

	ob->modelMat = hipoamat;
	ob->modelMat = glm::rotate(ob->modelMat, glm::radians(180.0), glm::dvec3(0, 0, 1));
	ob->modelMat = glm::scale(ob->modelMat, glm::dvec3(0.01, 0.01, 0.01));

	CompoundEntity *cpo = (CompoundEntity*)ob->entities.at(1);
	cpo->modelMat = glm::rotate(cpo->modelMat, glm::radians(5.0), glm::dvec3(1, 0, 0));
   
	if (ob->mov == false) {
		ob->setMov();
		CompoundEntity *cpo2 = (CompoundEntity*)ob->entities.at(0);
		cpo2->modelMat = glm::rotate(cpo2->modelMat, glm::radians(-35.0), glm::dvec3(1, 0, 0));
	}
}

/*void Scene::saveImage() {
for each (Entity* it in objetos)
{
it->guardarImagen();
}
}*/
//-------------------------------------------------------------------------
