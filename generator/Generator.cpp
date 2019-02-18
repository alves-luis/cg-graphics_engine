#include <iostream>
#include <string>
#include "Point.h"

using namespace std;

// Sphere uses 3 args (radius, slices and stacks)
const int SPHERE_ARGS = 3;

// Box uses 3 args (1 optional) (xDim, yDim, zDim, numDiv)
const int BOX_ARGS = 3;

// Cone uses 4 args (botRad, height, slices, stacks)
const int CONE_ARGS = 4;

// Plane uses 1 arg (dim)
const int PLANE_ARGS = 1;

// Minimum number of args: generator <primitive> ... <filename>
const int MIN_ARGS = 3;

void createPlane(float size, string fname) {

}

void createBox(float x, float y, float z, int div, string fname) {

}

void createSphere(float rad, int slices, int stacks, string fname) {

}

void createCone(float botRad, float height, int slices, int stacks, string fname) {

}

/**
 * Helper function to put args into int. Returns NULL if error.
 * */
float * argsUpdate(char**argv, int max) {
  float * result = (float *) malloc(sizeof(float)*max);

  if (!result)
    return result;

  for(int i = 0; i < max; i++)
    if (argv[i+2])
      result[i] = stof(argv[i+2]);
    else
      return NULL;

  return result;
}

/**
 * What is called when using the generator
 */
int main(int argc, char** argv) {

  if (argc < MIN_ARGS) {
    cout << "Invalid arguments!";
    return 1;
  }

  string prim = argv[1];
  if(prim == "cone") {

    if (argc < 2 + CONE_ARGS) {
      cout << "Invalid arguments!";
      return 1;
    }

    float * args = argsUpdate(argv,CONE_ARGS);
    if (!args) {
      cout << "Invalid arguments!";
      return 1;
    }
    createCone(args[0],args[1], static_cast<int>(args[2]), static_cast<int>(args[3]),argv[2+CONE_ARGS]);
    free(args);
  }
  else if (prim == "sphere") {

    if (argc < 2 + SPHERE_ARGS) {
      cout << "Invalid arguments!";
      return 1;
    }

    float * args = argsUpdate(argv,SPHERE_ARGS);
    if (!args) {
      cout << "Invalid arguments!";
      return 1;
    }
    createSphere(args[0], static_cast<int>(args[1]), static_cast<int>(args[2]),argv[2+SPHERE_ARGS]);
    free(args);
  }
  else if (prim == "box") {

    if (argc < 2 + BOX_ARGS) {
      cout << "Invalid arguments!";
      return 1;
    }

    float * args;
    bool divisions = false;
    if (argc == 2 + BOX_ARGS) { // if no number of divisions
      args = argsUpdate(argv, BOX_ARGS);
    }
    else if (argc == 3 + BOX_ARGS) { // if number of divisions specified
      args = argsUpdate(argv, BOX_ARGS + 1);
      divisions = true;
    }

    if (!args) {
      cout << "Invalid arguments!";
      return 1;
    }

    if (divisions)
      createBox(args[0],args[1],args[2],args[3],argv[3+BOX_ARGS]);
    else
      createBox(args[0],args[1],args[2],0,argv[2+BOX_ARGS]);

    free(args);
  }

  return 0;
}

