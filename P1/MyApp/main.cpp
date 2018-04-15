//#include <Windows.h>
//#include <gl/GL.h>
//#include <gl/GLU.h>
//#include <GL/glut.h>

#include <GL/freeglut.h>
#include <glm.hpp>
#include "Camera.h"
#include "Scene.h"
#include "Texture.h"

#include <iostream>
using namespace std;

//---------- Global variables -------------------------------------------------------------

// Viewport position and size
Viewport viewPort(800, 600);

// Camera position, view volume and projection
Camera camera(&viewPort);

// Scene entities
Scene scene(&camera);

// Coordenadas del raton
glm::dvec2 mCoord;


//----------- Callbacks ----------------------------------------------------

void display();
void resize(int newWidth, int newHeight);
void key(unsigned char key, int x, int y);
void specialKey(int key, int x, int y);
void mouse(int button, int state, int x, int y);
void motion(int x, int y);


//-------------------------------------------------------------------------

int main(int argc, char *argv[])
{
	cout << "Starting console..." << '\n';

	// Initialization
	glutInit(&argc, argv);

	glutInitContextVersion(3, 3);
	glutInitContextProfile(GLUT_COMPATIBILITY_PROFILE);
	glutSetOption(GLUT_ACTION_ON_WINDOW_CLOSE, GLUT_ACTION_GLUTMAINLOOP_RETURNS);
	glutInitWindowSize(800, 600);   // window size
	//glutInitWindowPosition (140, 140);

	glutInitDisplayMode(GLUT_RGBA | GLUT_DOUBLE | GLUT_DEPTH);   // | GLUT_STENCIL

	int win = glutCreateWindow("Freeglut-project");  // window's identifier

	// Callback registration
	glutMouseFunc(mouse);
	glutMotionFunc(motion);
	glutReshapeFunc(resize);
	glutKeyboardFunc(key);
	glutSpecialFunc(specialKey);
	glutDisplayFunc(display);

	cout << glGetString(GL_VERSION) << '\n';
	cout << glGetString(GL_VENDOR) << '\n';

	scene.init();    // after creating the context

	glutMainLoop();
	//cin.sync();   cin.get();
	glutDestroyWindow(win);  // Destroy the context 

	return 0;
}
//-------------------------------------------------------------------------

void display()   // double buffer
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	scene.render();

	glutSwapBuffers();
}
//-------------------------------------------------------------------------

void resize(int newWidth, int newHeight)
{
	// Resize Viewport 
	viewPort.setSize(newWidth, newHeight);
	// Resize Scene Visible Area 
	camera.setSize(viewPort.getW(), viewPort.getH());    // scale unchanged
}
//-------------------------------------------------------------------------

void key(unsigned char key, int x, int y)
{
	bool need_redisplay = true;
	int x2;
	int y2;
	Texture texture;
	switch (key) {
	case 27:  // Escape key 
		glutLeaveMainLoop();  // Freeglut's sentence for stopping glut's main loop 
		break;
	case '+':
		camera.scale(+0.01);   // zoom in  
		break;
	case '-':
		camera.scale(-0.01);   // zoom out
		break;
	case 'l':
		camera.set3D();
		break;
	case 'o':
		camera.setAZ();
		break;
	case 'a':
		scene.aumentarRotacion(); //Rotación diábolo
		scene.render();
		break;
	case 'f': {
		Texture texture;
		int x2 = glutGet(GLUT_WINDOW_WIDTH);
		int y2 = glutGet(GLUT_WINDOW_HEIGHT);
		texture.loadColorBuffer(x2, y2);
		texture.save("texturaGIC.bmp");
	}
			  //scene.saveImage();
			  break;
	case 'W':
		camera.moveFB(80.0);
		break;
	case 'A':
		camera.moveLR(-3.0);
		break;
	case 'S':
		camera.moveFB(-80.0);
		break;
	case 'D':
		camera.moveLR(3.0);
		break;
	case 'R':
		camera.moveUD(3.0);
		break;
	case 'F':
		camera.moveUD(-3.0);
		break;
	case 'p':
		camera.setPrj();
		camera.actualizarFront();
		camera.actualizarRight();
		camera.actualizarPitch();
		camera.actualizarYaw();
		break;
	default:
		need_redisplay = false;
		break;
	}//switch

	if (need_redisplay)
		glutPostRedisplay();
}
//-------------------------------------------------------------------------

void specialKey(int key, int x, int y)
{
	bool need_redisplay = true;
	switch (key) {
	case GLUT_KEY_RIGHT:
		camera.pitch(1);   // rotate 1 on the X axis
		break;
	case GLUT_KEY_LEFT:
		camera.yaw(1);     // rotate 1 on the Y axis 
		break;
	case GLUT_KEY_UP:
		camera.roll(1);    // rotate 1 on the Z axis
		break;
	case GLUT_KEY_DOWN:
		camera.roll(-1);   // rotate -1 on the Z axis
		break;
	default:
		need_redisplay = false;
		break;
	}//switch
	if (need_redisplay)
		glutPostRedisplay();
}

void motion(int x, int y) {
	glm::dvec2 mOffset = mCoord; // var. global
	mCoord = glm::dvec2(x, glutGet(GLUT_WINDOW_HEIGHT) - y);
	mOffset = (mCoord - mOffset) * 0.05; // sensitivity = 0.05
	camera.rotatePY(mOffset.y, mOffset.x);
	glutPostRedisplay();
}

void mouse(int button, int state, int x, int y) {
	mCoord.x = x;
	mCoord.y = glutGet(GLUT_WINDOW_HEIGHT) - y;
}
//-------------------------------------------------------------------------
