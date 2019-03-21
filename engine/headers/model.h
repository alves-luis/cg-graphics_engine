#ifndef MODEL_H
#define MODEL_H

#include "vertex.h"

/**
 * Model is a pointer to the actual struct
 * */
typedef struct model * Model;

/**
 * Allocs memory for a new Model
 * @param name Model Name
 * @param color Color name
 * @return Pointer to the model
 * */
Model newModel(char * name, char * color);

/**
 * Adds a vertex to a model
 * @param m Model to add the vertex to
 * @param v Vertex to add to the model
 * */
void addVertex(Model m, Vertex v);

/**
 * Returns the i-th vertex of a model
 * @param m Model to retrieve the vertex from
 * @param i index of the vertex
 * @return Pointer to the Vertex
 * */
Vertex getVertex(Model m, int i);

/**
 * Returns the name of the model
 * @param m Model to retrieve the name from
 * @return name of model or NULL if invalid model
 * */
char * getName(Model m);

/**
 * Returns the color of the model
 * @param m Model to retrieve the color from
 * @return name of color or NULL if invalid model
 * */
char * getColor(Model m);

/**
 * Returns the number of vertexes in the model
 * @param m Model to get the info
 * @return number of vertexes
 * */
int getSize(Model m);

/**
 * Frees up the memory of a model
 * @param m Model to cleanup*/
void freeModel(Model m);
#endif
