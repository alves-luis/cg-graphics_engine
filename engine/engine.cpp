#ifdef __APPLE__
#include <GLUT/glut.h>
#else
#include <GL/glew.h>
#include <GL/glut.h>
#endif

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <vector>
#include <map>
#include <cstring>
#include "headers/vertex.h"
#include "headers/model.h"
#include "headers/parser.h"
#include "headers/group.h"
#define _USE_MATH_DEFINES
#include <math.h>

/** Stores the groups in a vector */
std::vector<Group> groups;

/** Stores the lights in a vector */
std::vector<Light> lights;

float camX;
float camY;
float camZ;
float viewX;
float viewY;
float viewZ;

void changeSize(int w, int h) {

  // Prevent a divide by zero, when window is too short
  // (you cant make a window with zero width).
  if(h == 0)
    h = 1;

  // compute window's aspect ratio
  float ratio = w * 1.0 / h;

  // Set the projection matrix as current
  glMatrixMode(GL_PROJECTION);
  // Load Identity Matrix
  glLoadIdentity();

  // Set the viewport to be the entire window
  glViewport(0, 0, w, h);

  // Set perspective
  gluPerspective(45.0f ,ratio, 1.0f ,1000.0f);

  // return to the model view matrix mode
  glMatrixMode(GL_MODELVIEW);
}

void drawModel(Model m) {

    drawVBO(m);
}

void drawGroup(Group g) {
    glPushMatrix();

    std::vector<Model> * models = getModels(g);
    std::vector<Group> * children = getGroups(g);

    Translation translation = getTranslation(g);
    Scale scale = getScale(g);
    Rotation rotation = getRotation(g);


    for(int i = 0; i < 3; i++) {
        char * op = getNthTransformation(g,i);
        if(!op) // if no op, stop
            break;
        if(strcmp("translation",op) == 0)
        	drawTranslation(translation);
        else if(strcmp("rotation",op) == 0)
        	drawRotation(rotation);
        else if (strcmp("scale",op) == 0)
            glScalef(getX(scale), getY(scale), getZ(scale));
    }


    if (models) {
        for(Model m : *models) {
            drawModel(m);
        }
    }

    if (children) {
        for(Group child : *children) {
            drawGroup(child);
        }
    }

    glPopMatrix();
}


void renderScene() {

  // clear buffers
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

  // set the camera
  glLoadIdentity();

  glPolygonMode(GL_FRONT_AND_BACK,GL_FILL);


  gluLookAt(viewX,viewY,viewZ,
            0,0,0.0,
            0.0f,1.0f,0.0f);


  glTranslatef(camX,camY,camZ);

  for(auto l : lights) {
      drawLight(l);
  }

  // put drawing instructions here
  for (auto g : groups) {
      drawGroup(g);
  }

  // End of frame
  glutSwapBuffers();
}

void processKeys(unsigned char c, int xx, int yy) {
    float k = 0.5f;
    float upX, upY, upZ;
    upX = upZ = 0.0f;
}

void processSpecialKeys(int key, int xx, int yy) {

    switch (key) {

        case GLUT_KEY_RIGHT:
            camX -= 0.1; break;

        case GLUT_KEY_LEFT:
            camX += 0.1; break;

        case GLUT_KEY_UP:
            camZ += 0.1; break;
        case GLUT_KEY_DOWN:
            camZ -= 0.1; break;
        case GLUT_KEY_PAGE_UP:
            camY -= 0.1; break;
        case GLUT_KEY_PAGE_DOWN:
            camY += 0.1; break;
        case GLUT_KEY_F1:
            viewX=0;
            viewY=0;
            viewZ=10;
            break;
        case GLUT_KEY_F2:
            viewX=1;
            viewY=10;
            viewZ=0;
            break;
        case GLUT_KEY_F3:
            viewX=1;
            viewY=-10;
            viewZ=0;
            break;
    }
    glutPostRedisplay();

}

void printInfo() {
    printf("You can use PAGE_UP/PAGE_DOWN to increase/decrease altitude\n");
    printf("Use ARROWS to shift model around XZ axis\n");
    printf("Use F1 to see sideways\n");
    printf("Use F2 to see from above\n");
    printf("Use F3 to see from bottom\n");
}

void initializeVBOS() {
	for(Group g: groups)
		initializeVBO(g);
}

void initialize(int argc, char** argv) {
    //init GLUT and the window
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DEPTH|GLUT_DOUBLE|GLUT_RGBA);
    glutInitWindowPosition(100,100);
    glutInitWindowSize(800,800);
    glutCreateWindow("CG@DI-UM");
	#ifndef __APPLE__
    glewInit();
	#endif
    glEnableClientState(GL_VERTEX_ARRAY);
    glEnableClientState(GL_NORMAL_ARRAY);
    glEnableClientState(GL_TEXTURE_COORD_ARRAY);
    if (lights.size() > 0)
    	glEnable(GL_LIGHTING);
    for(auto l : lights) {
        enableLight(l);
    }
    initializeVBOS();
    glEnable(GL_TEXTURE_2D);
    for(auto g : groups) {
        loadTexture(g);
    }
    viewX=0;
    viewY=0;
    viewZ=10;

  // Required callback registry
    glutDisplayFunc(renderScene);
    glutIdleFunc(renderScene);
    glutReshapeFunc(changeSize);

    glutSpecialFunc(processSpecialKeys);

  //  OpenGL settings
    glEnable(GL_DEPTH_TEST);
    //glEnable(GL_CULL_FACE);

  // enter GLUT's main cycle
    printInfo();
    glutMainLoop();
}

int main(int argc, char** argv) {

  if (argc < 2) {
    fprintf(stderr,"Invalid configuration file!\n");
    return 1;
  }
  int error = loadXML(argv[1],&groups,&lights);
  if (!error)
    initialize(argc, argv);
  else
    return 1;
}