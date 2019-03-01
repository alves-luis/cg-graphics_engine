#include "box.h"
#define _USE_MATH_DEFINES
#include <math.h>

using namespace std;

int createBox(float x, float y, float z, int div, string fname) {
  int i;
  // invalid arguments
  if (x < 0 || y < 0 || z < 0 || div<0)
    return 1;

  //face de baixo
  for (i = 0; i < div; i++) {
    writetofile((x/div)*i -(x/2) , -(y / 2), -(z / 2),fname);
    writetofile((x / div)*i - (x / 2), -(y / 2), (z / 2),fname);
    writetofile((x / div)*(i+1) - (x / 2), -(y / 2), (z / 2),fname);
  }
  for (i = 0; i < div; i++) {
    writetofile((x / div)*i - (x / 2), -(y / 2), -(z / 2),fname);
    writetofile((x / div)*(i + 1) - (x / 2), -(y / 2), (z / 2),fname);
    writetofile((x / div)*(i + 1) - (x / 2), -(y / 2), -(z / 2),fname);
  }
  //face cima
  for (i = 0; i < div; i++) {
    writetofile((x / div)*i - (x / 2), (y / 2), -(z / 2),fname);
    writetofile((x / div)*i - (x / 2),  (y / 2),  (z / 2),fname);
    writetofile((x / div)*(i + 1) - (x / 2), (y / 2), (z / 2),fname);
  }
  for (i = 0; i < div; i++) {
    writetofile((x / div)*i - (x / 2),  (y / 2), -(z / 2),fname);
    writetofile((x / div)*(i + 1) - (x / 2),  (y / 2), (z / 2),fname);
    writetofile((x / div)*(i + 1) - (x / 2),  (y / 2), -(z / 2),fname);
  }
  // face lado
  for (i = 0; i < div; i++) {
    writetofile(-(x/2), -(y/2), (z / div)*i-(z / 2),fname);
    writetofile(-(x/2), (y/2), (z / div)*(i+1)-(z / 2),fname);
    writetofile(-(x/2), -(y/2), (z / div)*(i+1)-(z / 2),fname);
  }
  for (i = 0; i < div; i++) {
    writetofile(-(x/2), -(y/2), (z / div)*i-(z / 2),fname);
    writetofile(-(x/2), (y/2), (z / div)*i-(z / 2),fname);
    writetofile(-(x/2), (y/2), (z / div)*(i + 1)-(z / 2),fname);
  }
  //face lado
  for (i = 0; i < div; i++) {
    writetofile((x/2), -(y/2), (z / div)*i-(z / 2),fname);
    writetofile((x/2), (y/2), (z / div)*(i + 1)-(z / 2),fname);
    writetofile((x/2), -(y/2), (z / div)*(i + 1)-(z / 2),fname);
  }
  for (i = 0; i < div; i++) {
    writetofile((x/2), -(y/2), (z / div)*i-(z / 2),fname);
    writetofile((x/2), (y/2), (z / div)*i-(z / 2),fname);
    writetofile((x/2), (y/2), (z / div)*(i + 1)-(z / 2),fname);
  }
  //face tras
  for (i = 0; i < div; i++) {
    writetofile((x / div)*i - (x / 2), -(y / 2), -(z / 2),fname);
    writetofile((x / div)*(i + 1) - (x / 2), -(y / 2), -(z / 2),fname);
    writetofile((x / div)*i - (x / 2), (y / 2), -(z / 2),fname);
  }
  for (i = 0; i < div; i++) {
    writetofile((x / div)*i - (x / 2), (y / 2), -(z / 2),fname);
    writetofile((x / div)*(i + 1) - (x / 2), -(y / 2), -(z / 2),fname);
    writetofile((x / div)*(i + 1) - (x / 2), (y / 2), -(z / 2),fname);
  }
  //face  frente
  for (i = 0; i < div; i++) {
    glColor3f(1, 0, 0);
    writetofile((x / div)*i-(x / 2), -(y / 2), (z / 2),fname);
    writetofile((x / div)*(i + 1) - (x / 2), -(y / 2), (z / 2),fname);
    writetofile((x / div)*i-(x / 2), (y / 2), (z / 2),fname);
  }
  for (i = 0; i < div; i++) {
    writetofile((x / div)*i-(x / 2), (y / 2), (z / 2),fname);
    writetofile((x / div)*(i + 1) - (x / 2), -(y / 2), (z / 2),fname);
    writetofile((x / div)*(i + 1)-(x / 2), (y / 2), (z / 2),fname);
  }
  return 0;
}
