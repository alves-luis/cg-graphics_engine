#ifdef __APPLE__
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif

#include <stdio.h>
#include <stdlib.h>
#include <vector>
#include <map>
#include "headers/vertex.h"
#include "headers/model.h"
#include "headers/parser.h"
#include "headers/group.h"

/** Stores the groups in a vector*/
std::vector<Group> groups;

std::map<char *,Model> models;


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
	int size = getSize(m);

    glBegin(GL_TRIANGLES);
	for(int j = 0; j < size; j++) {

		if (j % 2) glColor3f(1,1,0);
		else glColor3f(0,0,1);

		Vertex v = getVertex(m,j);
		glVertex3f(getX(v), getY(v), getZ(v));
	}
	glEnd();
}

void drawGroup(Group g) {
    glPushMatrix();

    std::vector<Model> * models = getModels(g);
    std::vector<Group> * children = getGroups(g);
    Translation translation = getTranslation(g);
    Scale scale = getScale(g);
    Rotation rotation = getRotation(g);
    int orderTranslation = getOrder(translation);
    int orderScale = getOrder(scale);
    int orderRotation = getOrder(rotation);

    if (orderTranslation < orderScale) {
        glTranslatef(getX(translation), getY(translation), getZ(translation));
        glScalef(getX(scale), getY(scale), getZ(scale));
    }
    else {
        glScalef(getX(scale), getY(scale), getZ(scale));
        glTranslatef(getX(translation), getY(translation), getZ(translation));
    }


    if (models) {
        for(Model m : *models) {
            drawModel(m);
        }
    }

    if (children) {
        for(Group g : *children) {
            drawGroup(g);
        }
    }

    glPopMatrix();
}


void renderScene(void) {

  // clear buffers
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

  // set the camera
  glLoadIdentity();
  gluLookAt(5.0,5.0,5.0,
            0.0,0.0,0.0,
            0.0f,1.0f,0.0f);


  // put drawing instructions here
  for(int i = 0; i < groups.size(); i++) {
      Group g = groups.at(i);
      drawGroup(g);
  }

  // End of frame
  glutSwapBuffers();
}


void initialize(int argc, char** argv) {
    //init GLUT and the window
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DEPTH|GLUT_DOUBLE|GLUT_RGBA);
    glutInitWindowPosition(100,100);
    glutInitWindowSize(800,800);
    glutCreateWindow("CG@DI-UM");

  // Required callback registry
    glutDisplayFunc(renderScene);
    glutReshapeFunc(changeSize);

  //  OpenGL settings
    glEnable(GL_DEPTH_TEST);
    glEnable(GL_CULL_FACE);

  // enter GLUT's main cycle
    glutMainLoop();
}

int main(int argc, char** argv) {

  if (argc < 2) {
    printf("Invalid configuration file!\n");
    return 1;
  }
  int error = loadXML(argv[1],&groups);
  if (!error)
    initialize(argc, argv);
  else
    return 1;
}