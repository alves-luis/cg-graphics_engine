#ifndef ROTATION_H
#define ROTATION_H

#include "operation3f.h"

typedef struct rotation * Rotation;
Rotation newRotation();
void setAngle(Rotation r, int angle);
void setX(Rotation r, float x);
void setY(Rotation r, float y);
void setZ(Rotation r, float z);
void setOrder(Rotation r, int i);
float getX(Rotation r);
float getY(Rotation r);
float getZ(Rotation r);
int getOrder(Rotation r);

#endif //ENGINE_ROTATION_H
