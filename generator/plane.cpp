//#include "plane.h"
#define _USE_MATH_DEFINES
#include <math.h>
#include "writetofile.h"
#include "plane.h"


int createPlane(float size, char * fname) {
    FILE * file = openFile(fname);
    float x, z;
    
    x = size / 2;
    z = size / 2;

    // 1º Triângulo
    writeToFile(x,0,z,file);
    writeToFile(-x,0,-z,file);
    writeToFile(-x,0,z,file);
    // 2º Triângulo
    writeToFile(-x,0,-z,file);
    writeToFile(x,0,z,file);
    writeToFile(x,0,-z,file);
    closeFile(file);
}