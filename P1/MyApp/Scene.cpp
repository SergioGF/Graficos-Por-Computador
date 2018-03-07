#include "Scene.h"

//-------------------------------------------------------------------------

void Scene::init()
{ // OpenGL basic setting
  glClearColor(1.0, 1.0, 1.0, 1.0);  // background color (alpha=1 -> opaque)
  glEnable(GL_DEPTH_TEST);  
  glEnable(GL_TEXTURE_2D);
  camera->setAZ();
    
  // lights
  // textures  

  // objetos
  //objetos.push_back(new ContCubo(200.0));
  //objetos.push_back(new TrianguloRGB(100.0));
  //objetos.push_back(new TriPyramid(100.0,200.0));
  objetos.push_back(new Cubo(180.0));
  objetos.push_back(new Diabolo(80.0, 140.0));
  objetos.push_back(new Suelo(1000.0, 1000.0, 180.0));
  objetos.push_back(new EjesRGB(500.0));

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

int i = 0;
viewport = camera->getVP();
  viewport->setSize(800, 600);
  for each (Entity* it in objetos)
  {
	  if (i == 1) {
		  viewport->setPos(250, 20);
	  }
	  else if (i == 0) {
		  viewport->setPos(0, 0);
	  }
	 else if (i == 2) {
		 viewport->setPos(0, 0);
	  }
	  else if (i == 3) {
		  viewport->setPos(0, 0);
	  }
	  i++;
	  it->render(camera->getViewMat());
  }
  /*for each (Entity* it in objetos)
  {
	  it->render(camera->getViewMat());
  }*/
}

void Scene::aumentarRotacion() {
	for each (Entity* it in objetos)
	{
		it->RotacionDiabolo();
	}
}

void Scene::saveImage() {
	for each (Entity* it in objetos)
	{
		it->guardarImagen();
	}
}
//-------------------------------------------------------------------------

