#include "headers/model.h"
#include "headers/vertex.h"
#include <vector>
#include <stdlib.h>
#include <string.h>

struct model {
    std::vector<Vertex> * vertexes;
    char * modelName;
};

Model newModel(char * name) {
  Model m = (Model) malloc(sizeof(struct model));
  m->vertexes = new std::vector<Vertex>();
  if (!m)
    return NULL;

  m->modelName = strdup(name);
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
