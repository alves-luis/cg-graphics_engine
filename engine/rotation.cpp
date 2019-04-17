#include "headers/rotation.h"
#include <stdlib.h>
#include <GL/glew.h>
#include <GL/glut.h>


struct rotation{

    float angle;
    bool time;
    Operation3f axis;

};

Rotation newRotation(bool time){
    auto r= (Rotation) malloc (sizeof(struct rotation));
    if(r) {
        r->time = time;
        r->angle = 0;
        r->axis = newOperation3f();
    }
    return r;
}

void setAngle(Rotation r, float angle) {
    if (r && !(r->time)) {
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

void setTime(Rotation r, float time) {
    if (r && r->time) {
        r->angle = static_cast<float>(time * 1e3);
    }
}

float getAngle(Rotation r) {
    if (r)
        return r->angle;
    else
        return 0;
}

float getTime(Rotation r) {
    if (r && r->time)
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

void drawRotation(Rotation r) {
    if (r && r->time) {
        glRotatef(glutGet(GLUT_ELAPSED_TIME) * 360 / r->angle,getX(r->axis),getY(r->axis),getZ(r->axis));
    }
    else if (r) {
        glRotatef(r->angle,getX(r->axis),getY(r->axis),getZ(r->axis));
    }
}


