#ifndef TRANSLATE_H
#define TRANSLATE_H
#ifdef __APPLE__
#include <GLUT/glut.h>
#else
#include <GL/glew.h>
#include <GL/glut.h>
#endif
#include "operation3f.h"
#include "vertex.h"


/**
 * A Translation was just an Operation3f
 * */
typedef struct translation * Translation;

/**
 * Method that allocates memory for a new translation
 * @param extended if is defined by a catmull-rom
 * @return pointer to translation, or NULL if failed
 * */
Translation newTranslation(bool extended);

/**
 * Method that adds a new point to the translation
 * @param f translation that will get a new shiny point
 * @param v Vertex containing the coords of the point
 * */
void addPoint(Translation f, Vertex v);

/**
 * Method that retrieves a point in the given index of a translation
 * (extended)
 * @param t Translation that will provide a shiny point
 * @param i Index of point
 * @return Vertex, or NULL if invalid index or not extended
 * */
Vertex getPoint(Translation t, int i);

/**
 * Method that sets the number of seconds the translation takes
 * @param t Translation
 * @param time Number of seconds to run the translation
 * */
void setTime(Translation t, float time);

/**
 * Method that returns the time associated with the translation
 * @param t translation
 * @return time or -1 if invalid t
 * */
float getTime(Translation t);

/**
 * Sets the x value of the given translation (not extended)
 * @param t Translation to set the X value
 * @param x new x value
 * */
void setX(Translation t, float x);

/**
 * Sets the y value of the given translation (not extended)
 * @param t Translation to set the Y value
 * @param y new y value
 * */
void setY(Translation t, float y);

/**
 * Sets the z value of the given translation (not extended)
 * @param t Translation to set the Z value
 * @param z new z value
 * */
void setZ(Translation t, float z);

/**
 * Given a translation (not extended), returns its X value
 * @param t Translation to retrieve the X value
 * @return X value
 * */
float getX(Translation t);

/**
 * Given a translation, returns its Y value
 * @param t Translation to retrieve the Y value
 * @return Y value
 * */
float getY(Translation t);

/**
 * Given a translation, return its Z value
 * @param t Translation to retrieve the Z value
 * @return Z value
 * */
float getZ(Translation t);

/**
 * Method that returns the position and derivative of the point in the curve
 * @param gt time elapsed
 * @param pos position
 * @param deriv derivatives
 * */
void getGlobalCatmullRomPoint(Translation t, float gt, float * pos, float * deriv);

/**
 * Method that executes the translation
 * @param t Translation
 * */
void drawTranslation(Translation t);


#endif
