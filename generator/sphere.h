#ifndef SPHERE_H
#define SPHERE_H

#include <stdio.h>

/**
 * This function, given a radius, number of slices and stacks, and a filename, writes the
 * vertixes of the corresponding sphere in given filename
 * @param rad radius of sphere
 * @param slices number of slices
 * @param stacks number of stacks
 * @param fname filename
 * @returns 0 if successful*/
int createSphere(float rad, int slices, int stacks, char * fname);

#endif
