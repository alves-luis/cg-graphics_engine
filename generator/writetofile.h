#ifndef WRITETOFILE_H
#define WRITETOFILE_H

#include <stdio.h>

int writeToFile(float x, float y, float z, FILE * fName);
FILE * openFile(char * fname);
void closeFile(FILE * f);
#endif
