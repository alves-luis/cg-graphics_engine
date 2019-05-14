#ifndef MODEL_H
#define MODEL_H

#include <string>
#include <vector>
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
Model newModel(std::string name);

/**
 * Adds a vertex to a model
 * @param m Model to add the vertex to
 * @param v Vertex to add to the model
 * */
void addVertex(Model m, float v);

/**
 * Adds an index to a model
 * @param m Model to add the index to
 * @param i index to add
 * */
void addIndex(Model m, unsigned int i);

/**
 * Adds a normal to a model
 * @param m model to add
 * @param x coord
 * */
void addNormal(Model m, float x);

/**
 * Adds a texture to a model
 * @param m model to add
 * @param x coord to add
 * */
void addTexture(Model m, float x);

/**
 * Returns the i-th vertex of a model
 * @param m Model to retrieve the vertex from
 * @param i index of the vertex
 * @return vertex value
 * */
float getVertex(Model m, int i);

/**
 * Returns the i-th index of a model
 * @param m Model to retrieve the index from
 * @param i index of the index. ahah
 * @return int (-1 if error)
 * */
int getIndex(Model m, int i);

/**
 * Returns the name of the model
 * @param m Model to retrieve the name from
 * @return name of model or NULL if invalid model
 * */
std::string getName(Model m);

/**
 * Returns the number of vertexes in the model
 * @param m Model to get the info
 * @return number of vertexes
 * */
int getSize(Model m);

/**
 * Returns the number of indexes in the model
 * @param m Model to get the info
 * @return number of indexes
 * */
int getNumIndexes(Model m);

/**
 * Frees up the memory of a model
 * @param m Model to cleanup*/
void freeModel(Model m);

/**
 * Generates the buffers associated with this model
 * @param m Model
 * */
void initializeVBO(Model m);

/**
 * Draws using the buffer and vertexes of this model
 * @param m Model
 * */
void drawVBO(Model m);

/**
 * Returns a pointer to the indexes of this model
 * @param m Model
 * @return vector of indexes
 * */
std::vector<unsigned int> * getIndexes(Model m);

/**
 * Returns a pointer to the vertexes of this model
 * @param m Model
 * @return vector of floats
 * */
std::vector<float> * getVertexes(Model m);

void setIndexes(Model m, std::vector<unsigned int> * in);
void setVertexes(Model m, std::vector<float> * ver);
void setDiffuse(Model m, float * dif);
void setSpecular(Model m, float * spec);
void setEmissive(Model m, float * em);
void setAmbient(Model m, float * am);
void setTexture(Model m, std::string texture);
void loadTexture(Model m);
#endif
