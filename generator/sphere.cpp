#include "sphere.h"
#define _USE_MATH_DEFINES
#include <math.h>

using namespace std;

int createSphere(float rad, int slices, int stacks, string fname) {
  // invalid arguments
  if (rad < 0 || slices < 0 || stacks < 0)
    return 1;

  float horizStep = ((M_PI * 2) / slices);
  float vertStep = (M_PI) / stacks;


}

