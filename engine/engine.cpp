#ifdef __APPLE__
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif

#include "tinyxml/tinyxml2.h"
#include <stdio.h>
#include <stdlib.h>
#include <vector>
#include "vertex.h"
#include "model.h"

using namespace tinyxml2;

std::vector<Model> models;

int parse3D(char * fname) {
  FILE * file = fopen(fname,"r");

  if (file == NULL)
    return 1;

  float x, y, z;
  char * line = (char *) malloc(sizeof(char)*1024);

  if (line == NULL)
    return 2;

  size_t size;
  Model m = newModel(fname);

  if (m == NULL)
    return 3;

  Vertex v;
  while((getline(&line, &size, file)) > 0) {
    int suc = sscanf(line,"%f %f %f",&x,&y,&z);
    if (suc != 3) {// if can't get 3 axes, can't parse and return failure;
      freeModel(m);
      return 4;
    }
    v = newVertex();
    setX(v,x);
    setY(v,y);
    setZ(v,z);
    addVertex(m,v);
  }
  models.push_back(m);
  free(line);

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

  while(model != NULL) {

    char * fileName = (char *) model->Attribute("file");

    int error = parse3D(fileName);
    if (error) // if error in parsing file 3D, don't parse anymore files
      return error;

    model = model->NextSiblingElement("model");
  }
  return 0;
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
  glBegin(GL_TRIANGLES);
  for(int i = 0; i < models.size(); i++) {
      Model m = models.at(i);
      int size = getSize(m);

      for(int j = 0; j < size; j++) {
        Vertex v = getVertex(m,j);
        glVertex3f(getX(v), getY(v), getZ(v));
      }
  }
  glEnd();

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

  int error = loadXML(argv[1]);
  if (!error)
    initialize(argc, argv);
  else
    return 1;
}