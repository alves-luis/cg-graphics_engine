#include "headers/model.h"
#include "headers/vertex.h"
#include <vector>
#include <stdlib.h>
#include <string.h>

struct model {
    std::vector<Vertex> * vertexes;
    char * color;
    char * modelName;
};

Model newModel(char * name, char * color) {
  Model m = (Model) malloc(sizeof(struct model));
  m->vertexes = new std::vector<Vertex>();
  if (!m)
    return NULL;

  m->modelName = strdup(name);
  m->color = strdup(color);
  return m;
}

void addVertex(Model m, Vertex v) {
  if (m) {
    m->vertexes->push_back(v);
  }
}

Vertex getVertex(Model m, int i) {
  if (m) {
    Vertex v = m->vertexes->at(i);
    return v;
  }
  else
    return NULL;
}

char * getName(Model m) {
  if (m)
    return m->modelName;
  else
    return NULL;
}

char * getColor(Model m) {
  if (m)
    return m->color;
  else
    return NULL;
}

int getSize(Model m) {
  if (m)
    return (int) m->vertexes->size();
}

void freeModel(Model m) {
  if (m) {
    free(m->modelName);
    m->vertexes->clear();
  }
}
