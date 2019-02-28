#include "tinyxml/tinyxml2.h"
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

int main(int argc, char** argv) {

  if (argc < 2) {
    std::cout << "Invalid configuration file!\n";
    return 1;
  }

  int error = loadXML(argv[1]);
}