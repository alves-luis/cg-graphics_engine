#include "headers/vertex.h"
#include <stdlib.h>

struct vertex {
    float x;
    float y;
    float z;
};

Vertex newVertex() {
  auto v = (Vertex) malloc(sizeof(struct vertex));
  if (!v)
    return nullptr;
  v->x = 0;
  v->y = 0;
  v->z = 0;
  return v;
}
float getX(Vertex v) {
  if (v)
    return v->x;
  else
    return 1;
}

float getY(Vertex v) {
  if (v)
    return v->y;
  else
    return 1;
}

float getZ(Vertex v) {
  if (v)
    return v->z;
  else
    return 1;
}

void setX(Vertex v, float x) {
  if (v)
    v->x = x;
}
void setY(Vertex v, float y) {
  if (v)
    v->y = y;
}
void setZ(Vertex v, float z) {
  if (v)
    v->z = z;
}

void freeVertex(Vertex v) {
  if (v)
    free(v);
}
