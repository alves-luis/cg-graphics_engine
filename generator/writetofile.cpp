#include "writetofile.h"
#include <stdio.h>
#include <stdlib.h>

int writeBlankToFile(FILE * fName){
  if(file == NULL)
  {
    printf("Error!");
    return 1;
  }
  fprintf(file, "\n");
  return 0;
}

int writeNormalToFile(float x, float y, float z, FILE * fName){

   if(file == NULL)
  {
    printf("Error!");
    return 1;
  }
  fprintf(file, "%f %f %f\n",x,y,z);
  return 0;

}


int writeVertexToFile(float x, float y, float z, FILE * file) {

  if(file == NULL)
  {
    printf("Error!");
    return 1;
  }
  fprintf(file, "%f %f %f\n",x,y,z);
  return 0;
}

int writeTextureToFile(float x, float y, FILE * file) {

	if(file == NULL)
	{
		printf("Error!");
		return 1;
	}
	fprintf(file, "%f %f\n",x,y);
	return 0;
}

int writeIndexToFile(int i, FILE * file) {
  if (file == NULL) {
    printf("Error!");
    return 1;
  }
  fprintf(file,"%d\n",i);
  return 0;
}

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