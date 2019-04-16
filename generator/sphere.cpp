#include "sphere.h"
#include "writetofile.h"
#include "vertex.h"

#define _USE_MATH_DEFINES
#include <math.h>
#include <stdio.h>
#include <vector>

/**
 * This function, given a radius beta and alpha, returns the cartesian X
 * @param rad radius of the sphere
 * @param beta vertical displacement
 * @param alpha horizontal displacement
 * @return X
 * */
float calcX(float rad, float beta, float alpha) {
  return rad * sin(beta) * cos(alpha);
}

/**
 * This function, given a radius beta and alpha, returns the cartesian Y
 * @param rad radius of the sphere
 * @param beta vertical displacement
 * @param alpha horizontal displacement
 * @return Y
 * */
float calcY(float rad, float beta) {
  return rad * cos(beta);
}

/**
 * This function, given a radius beta and alpha, returns the cartesian Z
 * @param rad radius of the sphere
 * @param beta vertical displacement
 * @param alpha horizontal displacement
 * @return Z
 * */
float calcZ(float rad, float beta, float alpha) {
  return rad * sin(beta) * sin(alpha);
}

int createSphere(float rad, int slices, int stacks, char * fname) {
  FILE * file = openFile(fname);
  // invalid arguments
  if (rad < 0 || slices < 1 || stacks < 1)
    return 1;

  float baseAlpha = static_cast<float>((M_PI * 2) / slices);
  float baseBeta = static_cast<float>((M_PI) / stacks);


  // until stacks + 1 so that no need to do if checking
  // it repeats the first vertex of a stack and slice at the end
  for(int stack = 0; stack <= stacks; stack++) {

    float beta = stack * baseBeta; // current vertical angle

    for(int slice = 0; slice <= slices; slice++) {

      float alpha = slice * baseAlpha; // current horizontal angle

      float x,y,z;

      x = calcX(rad,beta,alpha);
      y = calcY(rad,beta);
      z = calcZ(rad,beta,alpha);

      writeVertexToFile(x,y,z,file);
    }
  }

  for(int stack = 0; stack < stacks; stack++) {
  	for(int slice = 0; slice < slices; slice++) {
  		// A --- C
  		// B --- D
  		int indexA, indexB, indexC, indexD;
  		indexA = stack * (slices + 1) + slice;
  		indexB = (stack + 1) * (slices + 1) + slice;
  		indexC = indexA + 1;
  		indexD = indexB + 1;

  		writeIndexToFile(indexA,file);
		writeIndexToFile(indexB,file);
		writeIndexToFile(indexC,file);

		writeIndexToFile(indexB,file);
		writeIndexToFile(indexD,file);
		writeIndexToFile(indexC,file);
  	}
  }

  closeFile(file);

  return 0;


}

