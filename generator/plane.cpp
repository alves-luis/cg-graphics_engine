//#include "plane.h"
#define _USE_MATH_DEFINES
#include <math.h>
#include "writeToFile.h"

using namespace std;

void createPlane(float size, string fname) {

    float x, z;
    
    x = size / 2;
    z = size / 2;

    // 1º Triângulo
    writetofile(x,0,z,fname);
    writetofile(-x,0,z,fname);
    writetofile(-x,0,-z,fname);
    // 2º Triângulo
    writetofile(-x,0,-z,fname);
    writetofile(x,0,-z,fname);
    writetofile(x,0,z,fname);
}