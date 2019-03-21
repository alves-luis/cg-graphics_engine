#ifdef __APPLE__
#include <GLUT/glut.h>
#else
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

#define PAINT_WHITE glColor3f(1,1,1);
#define PAINT_SUN glColor3f(0.9f,1,0);
#define PAINT_MERCURY glColor3f(0.4f,0.4f,0.4f);
#define PAINT_VENUS glColor3f(0.9f,0.8f,0.4f);
#define PAINT_EARTH glColor3f(0,0.6f,0);
#define PAINT_MARS glColor3f(0.8f,0.3f,0);
#define PAINT_JUPITER glColor3f(0.9f,0.6f,0.8f);
#define PAINT_SATURN glColor3f(0.9f,0.8f,0.3f);
#define PAINT_URANUS glColor3f(0.8f,0.8f,1.0f);
#define PAINT_NEPTUNE glColor3f(0.5f,0.5f,1.0f);
#define PAINT_PLUTO glColor3f(0.5f,0.3f,0.2f);

/** Stores the groups in a vector*/
std::vector<Group> groups;

float alfa = 0.0f, beta = 0.5f, radius = 10.0f;

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

	char * color = getColor(m);

	if (strcmp(color,"white") == 0)
	    PAINT_WHITE
    else if (strcmp(color,"sun") == 0)
        PAINT_SUN
	else if (strcmp(color,"mercury") == 0)
	    PAINT_MERCURY
    else if (strcmp(color,"venus") == 0)
        PAINT_VENUS
	else if (strcmp(color,"earth") == 0)
	    PAINT_EARTH
    else if (strcmp(color,"mars") == 0)
        PAINT_MARS
    else if (strcmp(color,"jupiter") == 0)
        PAINT_JUPITER
    else if (strcmp(color,"saturn") == 0)
        PAINT_SATURN
    else if (strcmp(color,"uranus") == 0)
        PAINT_URANUS
    else if (strcmp(color,"neptune") == 0)
        PAINT_NEPTUNE
    else if (strcmp(color,"pluto") == 0)
        PAINT_PLUTO
	else
	    glColor3f(1.0f,0,0);

    glBegin(GL_TRIANGLES);
	for(int j = 0; j < size; j++) {
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


    for(int i = 0; i < 3; i++) {
        char * op = getNthTransformation(g,i);
        if(!op) // if no op, stop
            break;
        if(strcmp("translation",op) == 0)
            glTranslatef(getX(translation), getY(translation), getZ(translation));
        else if(strcmp("rotation",op) == 0)
            glRotatef(getAngle(rotation), getX(rotation),getY(rotation),getZ(rotation));
        else if (strcmp("scale",op) == 0)
            glScalef(getX(scale), getY(scale), getZ(scale));
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

  float camX, camY, camZ;

  camX = radius * cos(beta) * sin(alfa);
  camY = radius * sin(beta);
  camZ = radius * cos(beta) * cos(alfa);

  gluLookAt(camX,camY,camZ,
            0.0,0.0,0.0,
            0.0f,1.0f,0.0f);

  glPolygonMode(GL_FRONT_AND_BACK,GL_LINE);

  // put drawing instructions here
  for(int i = 0; i < groups.size(); i++) {
      Group g = groups.at(i);
      drawGroup(g);
  }

  // End of frame
  glutSwapBuffers();
}

void processSpecialKeys(int key, int xx, int yy) {

    switch (key) {

        case GLUT_KEY_RIGHT:
            alfa -= 0.1; break;

        case GLUT_KEY_LEFT:
            alfa += 0.1; break;

        case GLUT_KEY_UP:
            beta += 0.1f;
            if (beta > 1.5f)
                beta = 1.5f;
            break;

        case GLUT_KEY_DOWN:
            beta -= 0.1f;
            if (beta < -1.5f)
                beta = -1.5f;
            break;

        case GLUT_KEY_PAGE_DOWN: radius -= 0.5f;
            if (radius < 1.0f)
                radius = 1.0f;
            break;

        case GLUT_KEY_PAGE_UP: radius += 0.5f; break;
    }
    glutPostRedisplay();

}

void printInfo() {
    printf("You can use PAGE_UP/PAGE_DOWN to increase/decrease distance to center\n");
    printf("Use ARROWS to shift model around\n");
}

void initialize(int argc, char** argv) {
    srand(23);
    //init GLUT and the window
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DEPTH|GLUT_DOUBLE|GLUT_RGBA);
    glutInitWindowPosition(100,100);
    glutInitWindowSize(800,800);
    glutCreateWindow("CG@DI-UM");

  // Required callback registry
    glutDisplayFunc(renderScene);
    glutReshapeFunc(changeSize);

    glutSpecialFunc(processSpecialKeys);

  //  OpenGL settings
    glEnable(GL_DEPTH_TEST);
    glEnable(GL_CULL_FACE);

  // enter GLUT's main cycle
    printInfo();
    glutMainLoop();
}

int main(int argc, char** argv) {

  if (argc < 2) {
    fprintf(stderr,"Invalid configuration file!\n");
    return 1;
  }
  int error = loadXML(argv[1],&groups);
  if (!error)
    initialize(argc, argv);
  else
    return 1;
}