#ifndef OPERATION3F_H
#define OPERATION3F_H

typedef struct operation3f * Operation3f;
Operation3f newOperation3f();
void setX(Operation3f o, float x);
void setY(Operation3f o, float y);
void setZ(Operation3f o, float z);

#endif
