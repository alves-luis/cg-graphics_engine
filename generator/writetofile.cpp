#include "writetofile.h"
#include <stdio.h>
#include <stdlib.h>

int writeToFile(float x, float y, float z, FILE * file) {

  if(file == NULL)
  {
    printf("Error!");
    return 1;
  }
  fprintf(file, "%f %f %f\n",x,y,z);
  return 0;
}

FILE * openFile(char * fname) {
  FILE * f = fopen(fname,"w");
  return f;
}

void closeFile(FILE * f) {
  fclose(f);
}