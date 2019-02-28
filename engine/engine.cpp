#include "tinyxml/tinyxml2.h"
#include <GL/glut.h>
#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <vector>

using namespace tinyxml2;

typedef struct vertex {
  float x;
  float y;
  float z;
} * Vertex;

std::vector<Vertex> vertexes;

int parse3D(char * fname) {
  FILE * file = fopen(fname,"r");

  if (file == NULL)
    return 1;

  float x, y, z;
  char * line = (char *) malloc(sizeof(char)*1024);
  int read;
  size_t size;
  while((read = getline(&line, &size, file)) > 0) {
    int suc = sscanf(line,"%f %f %f",&x,&y,&z);
    if (suc != 3)
      return 1;
    Vertex v = (Vertex) malloc(sizeof(struct vertex));
    v->x = x;
    v->y = y;
    v->z = z;
    vertexes.push_back(v);
  }

  return 0;
}

int loadXML(char * fname) {
  XMLDocument doc;

  XMLError err = doc.LoadFile(fname);
  if (err)
    return err;

  XMLElement* scene = doc.FirstChildElement("scene");
  if (!scene)
    return XML_ERROR_PARSING_ELEMENT;

  XMLElement* model = scene->FirstChildElement("model");
  int error;
  while(model != NULL) {
    char * fileName = (char *) model->Attribute("file");
    error = parse3D(fileName);
    model = model->NextSiblingElement("model");
  }
}

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


void renderScene(void) {

  // clear buffers
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

  // set the camera
  glLoadIdentity();
  gluLookAt(5.0,5.0,5.0,
            0.0,0.0,0.0,
            0.0f,1.0f,0.0f);


  // put drawing instructions here
  for(int i = 0; i < vertexes.size()-2; i+= 3) {
    glBegin(GL_TRIANGLES);
      Vertex v1 = vertexes.at(i);
      Vertex v2 = vertexes.at(i+1);
      Vertex v3 = vertexes.at(i+2);
      glVertex3f(v1->x,v1->y,v1->z);
      glVertex3f(v2->x,v2->y,v2->z);
      glVertex3f(v3->x,v3->y,v3->z);
    glEnd();
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
    std::cout << "Invalid configuration file!\n";
    return 1;
  }

  int error = loadXML(argv[1]);

  initialize(argc, argv);
}