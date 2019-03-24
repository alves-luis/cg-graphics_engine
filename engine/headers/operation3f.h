#ifndef OPERATION3F_H
#define OPERATION3F_H

/**
 * Opaque data struct of an operation with 3 floats
 * */
typedef struct operation3f * Operation3f;

/**
 * Allocs memory to a Operation3f. Default values are 0.
 * @return pointer to the allocated memory, or NULL if failed*/
Operation3f newOperation3f();

/**
 * Sets the x value of the given operation
 * @param o Operation to set the X value
 * @param x new x value
 * */
void setX(Operation3f o, float x);

/**
 * Sets the y value of the given operation
 * @param o Operation to set the Y value
 * @param y new y value
 * */
void setY(Operation3f o, float y);

/**
 * Sets the z value of the given operation
 * @param o Operation to set the Z value
 * @param z new z value
 * */
void setZ(Operation3f o, float z);

/**
 * Given an operation, returns its X value
 * @param o Operation to retrieve the X value
 * @return X value
 * */
float getX(Operation3f o);

/**
 * Given an operation, returns its Y value
 * @param o Operation to retrieve the Y value
 * @return Y value
 * */
float getY(Operation3f o);

/**
 * Given an operation, return its Z value
 * @param o Operation to retrieve the Z value
 * @return Z value
 * */
float getZ(Operation3f o);

#endif
