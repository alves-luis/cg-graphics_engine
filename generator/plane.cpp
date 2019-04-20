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

    //
    writeVertexToFile(x,0,z,file);
    writeVertexToFile(-x,0,-z,file);
    writeVertexToFile(-x,0,z,file);
    writeVertexToFile(x,0,-z,file);

    writeIndexToFile(0,file);
    writeIndexToFile(1,file);
    writeIndexToFile(2,file);
    writeIndexToFile(1,file);
    writeIndexToFile(0,file);
    writeIndexToFile(3,file);

    closeFile(file);
    return 0;
}
