#ifndef ROTATION_H
#define ROTATION_H

#include "operation3f.h"

typedef struct rotation * Rotation;
Rotation newRotation();
void setAngle(Rotation r, float angle);
void setX(Rotation r, float x);
void setY(Rotation r, float y);
void setZ(Rotation r, float z);
float getX(Rotation r);
float getY(Rotation r);
float getZ(Rotation r);
float getAngle(Rotation r);

#endif
