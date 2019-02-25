#include "tinyxml/tinyxml2.h"
#include <iostream>
#include <GLUT/glut.h>

using namespace tinyxml2;
using namespace std;

typedef struct models {

};

int parse3D(const char * fname) {
  return 1;
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
    const char * fileName = model->Attribute("file");
    cout << fileName << "\n";
    int error = parse3D(fileName);
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
    cout << "Invalid configuration file!\n";
    return 1;
  }

  int error = loadXML(argv[1]);
  cout << error;

  initialize(argc, argv);
}