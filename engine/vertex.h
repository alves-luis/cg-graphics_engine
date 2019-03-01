#ifndef VERTEX_H
#define VERTEX_H

typedef struct vertex * Vertex;
Vertex newVertex();
float getX(Vertex v);
float getY(Vertex v);
float getZ(Vertex v);
void setX(Vertex v, float x);
void setY(Vertex v, float y);
void setZ(Vertex v, float z);
void freeVertex(Vertex v);
#endif
