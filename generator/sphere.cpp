#include "sphere.h"
#include "writetofile.h"
#define _USE_MATH_DEFINES
#include <math.h>
#include <stdio.h>

/**
 * This function, given a radius beta and alpha, returns the cartesian X
 * @param rad radius of the sphere
 * @param beta vertical displacement
 * @param alpha horizontal displacement
 * @return X
 * */
float calcX(float rad, float beta, float alpha) {
  return rad * sin(beta) * sin(alpha);
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
  return rad * sin(beta) * cos(alpha);
}

/**
 * This function draws a rectangle based on current beta, alpha, stack and slice
 * Rectangle looks like this:
 * A --- D
 * B --- C
 * @param rad radius of sphere
 * @param beta current vertical displacement
 * @param alpha current horizontal displacement
 * @param stack current stack
 * @param slice current slice
 * @param baseAlpha size of 1 alfa
 * @param baseBeta size of 1 beta
 * @param file file pointer to write the points of the rectangle
 * */
void draw(float rad, float beta, float alpha, int stack, int slice, float baseAlpha, float baseBeta, FILE * file) {
  // start drawing rectangles
  float xA, yA, zA, xB, yB, zB, xC, yC, zC, xD, yD, zD;

  // A --- D
  // B --- C
  xA = calcX(rad,beta,alpha);
  yA = calcY(rad,beta);
  zA = calcZ(rad,beta,alpha);

  alpha = (slice+1)*baseAlpha;
  xD = calcX(rad,beta,alpha);
  yD = yA;
  zD = calcZ(rad,beta,alpha);

  beta = (stack+1)*baseBeta;
  xC = calcX(rad,beta,alpha);
  yC = calcY(rad,beta);
  zC = calcZ(rad,beta,alpha);

  alpha = slice*baseAlpha;
  xB = calcX(rad,beta,alpha);
  yB = yC;
  zB = calcZ(rad,beta,alpha);

  writeToFile(xB,yB,zB,file);
  writeToFile(xC,yC,zC,file);
  writeToFile(xD,yD,zD,file);
  writeToFile(xB,yB,zB,file);
  writeToFile(xD,yD,zD,file);
  writeToFile(xA,yA,zA,file);
}

int createSphere(float rad, int slices, int stacks, char * fname) {
  FILE * file = openFile(fname);
  // invalid arguments
  if (rad < 0 || slices < 1 || stacks < 1)
    return 1;

  float horiStep = static_cast<float>((M_PI * 2) / slices);
  float vertStep = static_cast<float>((M_PI) / stacks);

  for(int i = 0; i < stacks; i++) {
    float beta = i * vertStep; // current vertical angle
    for(int j = 0; j < slices; j++) {
      float alpha = j * horiStep; // current horizontal angle
      draw(rad,beta,alpha,i,j,horiStep,vertStep,file);

    }
  }
  closeFile(file);

  return 0;


}

