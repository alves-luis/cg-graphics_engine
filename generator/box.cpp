#include "box.h"
#include "writetofile.h"

#define _USE_MATH_DEFINES
#include <math.h>


int createBox(float x, float y, float z, int div, char * fname) {
  int i;
  // invalid arguments
  if (x < 0 || y < 0 || z < 0 || div<0)
    return 1;

  //face de baixo
  for (i = 0; i < div; i++) {
    writeToFile((x/div)*i -(x/2) , -(y / 2), -(z / 2),fname);
    writeToFile((x / div)*i - (x / 2), -(y / 2), (z / 2),fname);
    writeToFile((x / div)*(i+1) - (x / 2), -(y / 2), (z / 2),fname);
  }
  for (i = 0; i < div; i++) {
    writeToFile((x / div)*i - (x / 2), -(y / 2), -(z / 2),fname);
    writeToFile((x / div)*(i + 1) - (x / 2), -(y / 2), (z / 2),fname);
    writeToFile((x / div)*(i + 1) - (x / 2), -(y / 2), -(z / 2),fname);
  }
  //face cima
  for (i = 0; i < div; i++) {
    writeToFile((x / div)*i - (x / 2), (y / 2), -(z / 2),fname);
    writeToFile((x / div)*i - (x / 2),  (y / 2),  (z / 2),fname);
    writeToFile((x / div)*(i + 1) - (x / 2), (y / 2), (z / 2),fname);
  }
  for (i = 0; i < div; i++) {
    writeToFile((x / div)*i - (x / 2),  (y / 2), -(z / 2),fname);
    writeToFile((x / div)*(i + 1) - (x / 2),  (y / 2), (z / 2),fname);
    writeToFile((x / div)*(i + 1) - (x / 2),  (y / 2), -(z / 2),fname);
  }
  // face lado
  for (i = 0; i < div; i++) {
    writeToFile(-(x/2), -(y/2), (z / div)*i-(z / 2),fname);
    writeToFile(-(x/2), (y/2), (z / div)*(i+1)-(z / 2),fname);
    writeToFile(-(x/2), -(y/2), (z / div)*(i+1)-(z / 2),fname);
  }
  for (i = 0; i < div; i++) {
    writeToFile(-(x/2), -(y/2), (z / div)*i-(z / 2),fname);
    writeToFile(-(x/2), (y/2), (z / div)*i-(z / 2),fname);
    writeToFile(-(x/2), (y/2), (z / div)*(i + 1)-(z / 2),fname);
  }
  //face lado
  for (i = 0; i < div; i++) {
    writeToFile((x/2), -(y/2), (z / div)*i-(z / 2),fname);
    writeToFile((x/2), (y/2), (z / div)*(i + 1)-(z / 2),fname);
    writeToFile((x/2), -(y/2), (z / div)*(i + 1)-(z / 2),fname);
  }
  for (i = 0; i < div; i++) {
    writeToFile((x/2), -(y/2), (z / div)*i-(z / 2),fname);
    writeToFile((x/2), (y/2), (z / div)*i-(z / 2),fname);
    writeToFile((x/2), (y/2), (z / div)*(i + 1)-(z / 2),fname);
  }
  //face tras
  for (i = 0; i < div; i++) {
    writeToFile((x / div)*i - (x / 2), -(y / 2), -(z / 2),fname);
    writeToFile((x / div)*(i + 1) - (x / 2), -(y / 2), -(z / 2),fname);
    writeToFile((x / div)*i - (x / 2), (y / 2), -(z / 2),fname);
  }
  for (i = 0; i < div; i++) {
    writeToFile((x / div)*i - (x / 2), (y / 2), -(z / 2),fname);
    writeToFile((x / div)*(i + 1) - (x / 2), -(y / 2), -(z / 2),fname);
    writeToFile((x / div)*(i + 1) - (x / 2), (y / 2), -(z / 2),fname);
  }
  //face  frente
  for (i = 0; i < div; i++) {
    writeToFile((x / div)*i-(x / 2), -(y / 2), (z / 2),fname);
    writeToFile((x / div)*(i + 1) - (x / 2), -(y / 2), (z / 2),fname);
    writeToFile((x / div)*i-(x / 2), (y / 2), (z / 2),fname);
  }
  for (i = 0; i < div; i++) {
    writeToFile((x / div)*i-(x / 2), (y / 2), (z / 2),fname);
    writeToFile((x / div)*(i + 1) - (x / 2), -(y / 2), (z / 2),fname);
    writeToFile((x / div)*(i + 1)-(x / 2), (y / 2), (z / 2),fname);
  }
  return 0;
}
