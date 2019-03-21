#include "headers/rotation.h"
#include <stdlib.h>


struct rotation{

    float angle;
    Operation3f axis;

};

Rotation newRotation(){
    Rotation r= (Rotation) malloc (sizeof(struct rotation));
    if(r) {
        r->angle = 0;
        r->axis = newOperation3f();
    }
    return r;
}

void setAngle(Rotation r, float angle) {
    if (r) {
        r->angle = angle;
    }
}

void setX(Rotation r, float x){
    if(r) {
        setX(r->axis, x);
    }
}

void setY(Rotation r, float y){
    if(r) {
        setY(r->axis, y);
    }
}

void setZ(Rotation r, float z){
    if(r) {
        setZ(r->axis, z);
    }
}

float getAngle(Rotation r) {
    if (r)
        return r->angle;
    else
        return 0;
}

float getX(Rotation r) {
    if (r)
        return getX(r->axis);
    else
        return 0;
}

float getY(Rotation r) {
    if (r)
        return getY(r->axis);
    else
        return 0;
}

float getZ(Rotation r) {
    if (r)
        return getZ(r->axis);
    else
        return 0;
}


