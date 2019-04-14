#include "headers/model.h"
#include "headers/vertex.h"
#include <vector>
#include <stdlib.h>
#include <string.h>
#ifdef __APPLE__
#include <GLUT/glut.h>
#else
#include <GL/glew.h>
#include <GL/glut.h>
#include <cstdio>

#endif

struct model {
    std::vector<float> * vertexes;
    std::vector<unsigned int> * indexes;
    unsigned int buffers[2];
    char * color;
    char * modelName;
};

Model newModel(char * name, char * color) {
  Model m = (Model) malloc(sizeof(struct model));
  if (!m)
    return NULL;
  m->vertexes = new std::vector<float>();
  m->indexes = new std::vector<unsigned int>();
  m->modelName = strdup(name);
  m->color = strdup(color);
  return m;
}

void addVertex(Model m, float v) {
  if (m) {
    m->vertexes->push_back(v);
  }
}

void addIndex(Model m, unsigned int i) {
  if (m) {
    m->indexes->push_back(i);
  }
}

float getVertex(Model m, int i) {
  if (m) {
    float v = m->vertexes->at(i);
    return v;
  }
  else
    return NULL;
}

int getIndex(Model m, int i) {
  if (m)
    return m->indexes->at(i);
  else
    return -1;
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

int getNumIndexes(Model m) {
  if (m)
    return (int) m->indexes->size();
}

void freeModel(Model m) {
  if (m) {
    free(m->modelName);
    m->vertexes->clear();
    m->indexes->clear();
  }
}

void initializeVBO(Model m) {
  if (m) {
    glGenBuffers(2,m->buffers);
    glBindBuffer(GL_ARRAY_BUFFER,m->buffers[0]);
    glBufferData(GL_ARRAY_BUFFER,m->vertexes->size() * sizeof(float),&m->vertexes[0],GL_STATIC_DRAW);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER,m->buffers[1]);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER,m->indexes->size() * sizeof(unsigned int), &m->indexes[0],GL_STATIC_DRAW);
  }
}

void drawVBO(Model m) {
	puts("ola");
	glBindBuffer(GL_ARRAY_BUFFER,m->buffers[0]);
	glVertexPointer(3,GL_FLOAT,0,&m->vertexes[0]);
	puts("oi");
	glColor3f(0,0,1);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER,m->buffers[1]);
	glDrawElements(GL_TRIANGLES, m->indexes->size(),GL_UNSIGNED_INT,NULL);
}
