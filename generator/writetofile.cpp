#include "writetofile.h"
#include <stdio.h>

int writeToFile(float x, float y, float z, char * fName) {
  printf("%f %f %f\n",x,y,z);
  return 1;
}