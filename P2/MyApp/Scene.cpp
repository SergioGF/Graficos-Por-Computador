#include "Scene.h"

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
	objetos.push_back(new EjesRGB(500.0));
	//objetos.push_back(new Espejo(100.0,100.0));
	//objetos.push_back(new Jardinera(180.0, 1000.0, 1000.0));
	//objetos.push_back(new Planta(180, 260, 1000.0, 1000.0));
	//objetos.push_back(new Planta(180));
	//objetos.push_back(new MPR(20));
	//objetos.push_back(new Hipo(10,300,7,4,2));
	objetos.push_back(new Sphere(100.0));
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

	for each (Entity* it in objetos)
	{
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

/*void Scene::saveImage() {
for each (Entity* it in objetos)
{
it->guardarImagen();
}
}*/
//-------------------------------------------------------------------------
