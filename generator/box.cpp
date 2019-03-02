#include "box.h"
#include "writetofile.h"
#include <stdio.h>

#define _USE_MATH_DEFINES
#include <math.h>

int createBox(float x, float y, float z, int div, char * name) {
  FILE * file = openFile(name);
  int i,t;
  // invalid arguments
  if (x < 0 || y < 0 || z < 0 || div<0)
    return 1;

  float x0=x/2;
  float y0=y/2;
  float z0=z/2;

  float nx=x/div;
  float nz=z/div;


  float b=y0/div;
  float c=z0/div;

    //face de baixo
  for (t = 0; t < div; t++) {
    for (i = 0; i < div; i++) {
      writeToFile(nx*i -x0 , -y0, -c*t,file);
      writeToFile(nx*(i+1) - x0, -y0, c*t,file);
      writeToFile(nx*i - x0, -y0, c*t,file);
    }
  }
  for (t = 0; t < div; t++) {
    for (i = 0; i < div; i++) {
      writeToFile(nx*i - x0, -y0, -c*t,file);
      writeToFile(nx*(i + 1) - x0, -y0, -c*t,file);
      writeToFile(nx*(i + 1) - x0, -y0, c*t,file);

    }
  }
    //face cima
  for (t = 0; t < div; t++) {
    for (i = 0; i < div; i++) {
      writeToFile(nx*i - x0, y0, -c*t,file);
      writeToFile(nx*i - x0,  y0,  c*t,file);
      writeToFile(nx*(i + 1) - x0, y0, c*t,file);
    }
  }
  for (t = 0; t < div; t++) {
    for (i = 0; i < div; i++) {
      writeToFile(nx*i - x0,  y0, -c*t,file);
      writeToFile(nx*(i + 1) - x0,  y0, c*t,file);
      writeToFile(nx*(i + 1) - x0,  y0, -c*t,file);
    }
  }
    // face lado esquerdo
  for (t = 0; t < div; t++) {
    for (i = 0; i < div; i++) {
      writeToFile(-x0, -b*t, nz*i-z0,file);
      writeToFile(-x0, -b*t, nz*(i+1)-z0,file);
      writeToFile(-x0, b*t, nz*(i+1)-z0,file);
     
    }
  }
  for (t = 0; t < div; t++) {
    for (i = 0; i < div; i++) {
      writeToFile(-x0, -b*t, nz*i-z0,file);
      writeToFile(-x0, b*t, nz*(i + 1)-z0,file);
      writeToFile(-x0, b*t, nz*i-z0,file);
      
    }
  }
    //face lado direito
  for (t = 0; t < div; t++) {
    for (i = 0; i < div; i++) {
      writeToFile(x0, -b*t, nz*i-z0,file);
      writeToFile(x0, b*t, nz*(i + 1)-z0,file);
      writeToFile(x0, -b*t, nz*(i + 1)-z0,file);
    }
  }
  for (t = 0; t < div; t++) {
    for (i = 0; i < div; i++) {
      writeToFile(x0, -b*t, nz*i-z0,file);
      writeToFile(x0, b*t, nz*i-z0,file);
      writeToFile(x0, b*t, nz*(i + 1)-z0,file);
    }
  }
    //face tras
  for (t = 0; t < div; t++) {
    for (i = 0; i < div; i++) {
      writeToFile(nx*i - x0, -b*t, -z0,file);
      writeToFile(nx*i - x0, b*t, -z0,file);
      writeToFile(nx*(i + 1) - x0, -b*t, -z0,file);
      
    }
  }
  for (t = 0; t < div; t++) {
    for (i = 0; i < div; i++) {
      writeToFile(nx*i - x0, b*t, -z0,file);
      writeToFile(nx*(i + 1) - x0, b*t, -z0,file);
      writeToFile(nx*(i + 1) - x0, -b*t, -z0,file);
      
    }
  }
    //face  frente
  for (t = 0; t < div; t++) {
    for (i = 0; i < div; i++) {
      writeToFile(nx*i-x0, -b*t, z0,file);
      writeToFile(nx*(i + 1) - x0, -b*t, z0,file);
      writeToFile(nx*i-x0, b*t, z0,file);
    }
  }
  for (t = 0; t < div; t++) {
    for (i = 0; i < div; i++) {
      writeToFile(nx*i-x0, b*t, z0,file);
      writeToFile(nx*(i + 1) - x0, -b*t, z0,file);
      writeToFile(nx*(i + 1)-x0, b*t, z0,file);
    }
  }
  return 0;
}
