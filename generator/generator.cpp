#include "sphere.h"
#include "plane.h"
#include "box.h"
#include "cone.h"
#include <string.h>
#include <stdlib.h>
#include <stdio.h>

// Helper struct to parse arguments
typedef struct args {
    float floats[3]; // max number of floats as args
    int ints[2]; // max number of ints as args
} * Arguments;

// Sphere uses 3 args (radius, slices and stacks)
const int SPHERE_ARGS = 3;

// Box uses 3 args (1 optional) (xDim, yDim, zDim, numDiv)
const int BOX_ARGS = 3;

// Cone uses 4 args (botRad, height, slices, stacks)
const int CONE_ARGS = 4;

// Plane uses 1 arg (dim)
const int PLANE_ARGS = 1;

// Minimum number of args: generator <primitive> ... <filename>
const int MIN_ARGS = 4;

/**
 * Helper function to put args into proper types. Returns NULL if error.
 * */
Arguments argsUpdate(char**argv, int numFloat, int numInt) {
  Arguments result = (Arguments) malloc(sizeof(struct args));

  if (!result)
    return result;

  for(int i = 0; i < numFloat; i++)
    if (argv[i])
      result->floats[i] = atof(argv[i]);
    else
      return NULL;

  argv += numFloat;

  for(int i = 0; i < numInt; i++)
    if (argv[i])
      result->ints[i] = atoi(argv[i]);
    else
      return NULL;

  return result;
}

int printError(char * error) {
  printf("Invalid %s!\n",error);
  return 1;
}

/**
 * What is called when using the generator
 */
int main(int argc, char** argv) {

  if (argc < MIN_ARGS)
    return printError("number of arguments");

  char * prim = argv[1];

  if (strcmp(prim,"plane") == 0) {

    Arguments args = argsUpdate(argv+2,1,0);

    if (!args)
      return printError("arguments for plane");

    createPlane(args->floats[0],argv[2+PLANE_ARGS]);
    free(args);

  }
  else if(strcmp(prim,"cone") == 0) {

    if (argc < 2 + CONE_ARGS)
      return printError("arguments for cone");

    Arguments args = argsUpdate(argv+2,2,2);

    if (!args)
      return printError("arguments for cone");

    createCone(args->floats[0],args->floats[1],args->ints[0],args->ints[1],argv[2+CONE_ARGS]);
    free(args);

  }
  else if (strcmp(prim,"sphere") == 0) {

    if (argc < 2 + SPHERE_ARGS)
      printError("arguments for sphere");

    Arguments args = argsUpdate(argv+2,1,2);

    if (!args)
      return printError("arguments for sphere");

    int result = createSphere(args->floats[0], args->ints[0], args->ints[1],argv[2+SPHERE_ARGS]);
    free(args);

    if (result) // if failed to create sphere, throw error
      return result;

  }
  else if (strcmp(prim,"box") == 0) {

    if (argc < 2 + BOX_ARGS)
      return printError("arguments for box");

    Arguments args;
    bool divisions = false;

    if (argc == 2 + BOX_ARGS)  // if no number of divisions
      args = argsUpdate(argv+2, 3, 0);

    else if (argc == 3 + BOX_ARGS) { // if number of divisions specified
      args = argsUpdate(argv+2,3,1);
      divisions = true;
    }

    if (!args)
      return printError("arguments for box");

    if (divisions)
      createBox(args->floats[0],args->floats[1],args->floats[2],args->ints[0],argv[3+BOX_ARGS]);
    else
      createBox(args->floats[0],args->floats[1],args->floats[2],0,argv[2+BOX_ARGS]);

    free(args);
  }

  return 0;
}

