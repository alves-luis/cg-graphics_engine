#include "headers/rotation.h"
#include <stdlib.h>


struct rotation{

    int angle;
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

void setAngle(Rotation r, int angle) {
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


