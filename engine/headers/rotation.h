#ifndef ROTATION_H
#define ROTATION_H

#include "operation3f.h"

/**
 * Opaque data struct which represents a Rotation
 * */
typedef struct rotation * Rotation;

/**
 * Allocates memory for a new Rotation. Default values are 0
 * for the angle and 0 for all the axis of the vector of rotation.
 * @param time if true, then no angle, but time to do 360 rotation
 * @return Pointer to the allocated memory
 * */
Rotation newRotation(bool time);

/**
 * Setter for the angle
 * @param r Rotation
 * @param angle new angle of rotation
 * */
void setAngle(Rotation r, float angle);

/**
 * Setter for the time
 * @param r Rotation
 * @param time to do a full 360 rotation
 * */
void setTime(Rotation r, float time);

/**
 * Setter for the X axis of rotation
 * @param r Rotation
 * @param x value of vector rotation
 * */
void setX(Rotation r, float x);

/**
 * Setter for the Y axis of rotation
 * @param r Rotation
 * @param y value of vector rotation
 * */
void setY(Rotation r, float y);

/**
 * Setter for the Z axis of rotation
 * @param r Rotation
 * @param z value of vector rotation
 * */
void setZ(Rotation r, float z);

/**
 * Getter for the X axis of rotation
 * @param r Rotation
 * @return value of x
 * */
float getX(Rotation r);

/**
 * Getter for the Y axis of rotation
 * @param r Rotation
 * @return value of y
 * */
float getY(Rotation r);

/**
 * Getter for the Z axis of rotation
 * @param r Rotation
 * @return value of z
 * */
float getZ(Rotation r);

/**
 * Getter for the angle of rotation
 * @param r Rotation
 * @return angle
 * */
float getAngle(Rotation r);

/**
 * Getter for the time of the 360 rotation
 * @param r Rotation
 * @return time, or 0 if invalid rotation
 * */
float getTime(Rotation r);

void drawRotation(Rotation r);

#endif
