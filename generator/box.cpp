#include "box.h"
#include "writetofile.h"

#define _USE_MATH_DEFINES
#include <math.h>


int createBox(float x, float y, float z, int div, char * fname) {
  int i;
  // invalid arguments
  if (x < 0 || y < 0 || z < 0 || div<0)
    return 1;

  float x0=x/2;
  float y0=y/2;
  float z0=z/2;

  float nx=x/div;
  float nz=z/div;
  
  //face de baixo
  for (i = 0; i < div; i++) {
    writeToFile(nx*i -x0 , -y0, -z0,fname);
    writeToFile(nx*i - x0, -y0, z0,fname);
    writeToFile(nx*(i+1) - x0, -y0, z0,fname);
  }
  for (i = 0; i < div; i++) {
    writeToFile(nx*i - x0, -y0, -z0,fname);
    writeToFile(nx*(i + 1) - x0, -y0, z0,fname);
    writeToFile(nx*(i + 1) - x0, -y0, -z0,fname);
  }
  //face cima
  for (i = 0; i < div; i++) {
    writeToFile(nx*i - x0, y0, -z0,fname);
    writeToFile(nx*i - x0,  y0,  z0,fname);
    writeToFile(nx*(i + 1) - x0, y0, z0,fname);
  }
  for (i = 0; i < div; i++) {
    writeToFile(nx*i - x0,  y0, -z0,fname);
    writeToFile(nx*(i + 1) - x0,  y0, z0,fname);
    writeToFile(nx*(i + 1) - x0,  y0, -z0,fname);
  }
  // face lado
  for (i = 0; i < div; i++) {
    writeToFile(-x0, -y0, nz*i-z0,fname);
    writeToFile(-x0, y0, nz*(i+1)-z0,fname);
    writeToFile(-x0, -y0, nz*(i+1)-z0,fname);
  }
  for (i = 0; i < div; i++) {
    writeToFile(-x0, -y0, nz*i-z0,fname);
    writeToFile(-x0, y0, nz*i-z0,fname);
    writeToFile(-x0, y0, nz*(i + 1)-z0,fname);
  }
  //face lado
  for (i = 0; i < div; i++) {
    writeToFile(x0, -y0, nz*i-z0,fname);
    writeToFile(x0, y0, nz*(i + 1)-z0,fname);
    writeToFile(x0, -y0, nz*(i + 1)-z0,fname);
  }
  for (i = 0; i < div; i++) {
    writeToFile(x0, -y0, nz*i-z0,fname);
    writeToFile(x0, y0, nz*i-z0,fname);
    writeToFile(x0, y0, nz*(i + 1)-z0,fname);
  }
  //face tras
  for (i = 0; i < div; i++) {
    writeToFile(nx*i - x0, -y0, -z0,fname);
    writeToFile(nx*(i + 1) - x0, -y0, -z0,fname);
    writeToFile(nx*i - x0, y0, -z0,fname);
  }
  for (i = 0; i < div; i++) {
    writeToFile(nx*i - x0, y0, -z0,fname);
    writeToFile(nx*(i + 1) - x0, -y0, -z0,fname);
    writeToFile(nx*(i + 1) - x0, y0, -z0,fname);
  }
  //face  frente
  for (i = 0; i < div; i++) {
    writeToFile(nx*i-x0, -y0, z0,fname);
    writeToFile(nx*(i + 1) - x0, -y0, z0,fname);
    writeToFile(nx*i-x0, y0, z0,fname);
  }
  for (i = 0; i < div; i++) {
    writeToFile(nx*i-x0, y0, z0,fname);
    writeToFile(nx*(i + 1) - x0, -y0, z0,fname);
    writeToFile(nx*(i + 1)-x0, y0, z0,fname);
  }
  return 0;
}
