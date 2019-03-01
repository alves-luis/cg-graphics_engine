#include "writetofile.h"
#include <stdio.h>

int writeToFile(float x, float y, float z, char * fName) {
  FILE * file;

  file=fopen(fName,"ab+");
  if(file == NULL)
  {
    printf("Error!");
    exit(1);
  }
  fprintf(file, "%f %f %f\n",x,y,z);
  fclose(file);
  return 1;
}