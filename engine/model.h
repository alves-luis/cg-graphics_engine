#ifndef MODEL_H
#define MODEL_H

#include "vertex.h"

typedef struct model * Model;
Model newModel(char * name);
void addVertex(Model m, Vertex v);
Vertex getVertex(Model m, int i);
int getSize(Model m);
void freeModel(Model m);
#endif
