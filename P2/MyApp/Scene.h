//#pragma once
#ifndef _H_Scene_H_
#define _H_Scene_H_

#include <GL/freeglut.h>
#include "glm.hpp"
#include <vector>
#include "Camera.h"
#include "Entities.h"
using namespace std;

//-------------------------------------------------------------------------

class Scene: public CompoundEntity
{
public:
	Scene(Camera* cam) : camera(cam) { };
	~Scene();
	void init();
	void render();
	void aumentarRotacion();
	void update(GLuint timeElapsed);
	void moveBB8();
	//void saveImage();

protected:
	Camera * camera;
	Viewport* viewport;
	std::vector<Entity*> objetos;
};

//-------------------------------------------------------------------------

#endif //_H_Scene_H_
