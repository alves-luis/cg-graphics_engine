#ifndef VERTEX_H
#define VERTEX_H

/**
 * Vertex is actually a pointer to a struct
 * */
typedef struct vertex * Vertex;

/**
 * Allocs memory to a new Vertex
 * @return Pointer to the Vertex
 * */
Vertex newVertex();

/**
 * Returns the X component of a given Vertex
 * @param v Vertex to get the info from
 * @return x value of the vertex
 * */
float getX(Vertex v);

/**
 * Returns the Y component of a given Vertex
 * @param v Vertex to get the info from
 * @return y value of the vertex
 * */
float getY(Vertex v);

/**
 * Returns the Z component of a given Vertex
 * @param v Vertex to get the info from
 * @return z value of the vertex
 * */
float getZ(Vertex v);

/**
 * Sets the X component of a given Vertex
 * @param v Vertex to set the value
 * @param x new value of x
 * */
void setX(Vertex v, float x);

/**
 * Sets the Y component of a given Vertex
 * @param v Vertex to set the value
 * @param y new value of y
 * */
void setY(Vertex v, float y);

/**
 * Sets the Z component of a given Vertex
 * @param v Vertex to set the value
 * @param z new value of z
 * */
void setZ(Vertex v, float z);

/**
 * Cleans up memory of a given Vertex
 * @param v vertex to free the memory of
 * */
void freeVertex(Vertex v);
#endif
