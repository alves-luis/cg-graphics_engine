#include <iostream>
#include <string>

using namespace std;

const int SPHERE_ARGS = 3;
const int BOX_ARGS = 3;
const int CONE_ARGS = 4;

void createPlane(string fname) {

}

void createBox(int x, int y, int z, int div, string fname) {

}

void createSphere(int rad, int slices, int stacks, string fname) {

}

void createCone(int botRad, int height, int slices, int stacks, string fname) {

}

/**
 * Helper function to put args into int. Returns NULL if error.
 * */
int * argsUpdate(char**argv, int max) {
  int * result = (int *) malloc(sizeof(int)*max);

  if (!result)
    return result;

  for(int i = 0; i < max; i++)
    if (argv[i+2])
      result[i] = stoi(argv[i+2]);
    else
      return NULL;

  return result;
}

/**
 * What is called when using the generator
 */
int main(int argc, char** argv) {

  if (argc < 2) {
    cout << "Invalid arguments!";
    return 1;
  }

  string prim = argv[1];
  if(prim == "cone") {

    if (argc < 2 + CONE_ARGS) {
      cout << "Invalid arguments!";
      return 1;
    }

    int * args = argsUpdate(argv,CONE_ARGS);
    if (!args) {
      cout << "Invalid arguments!";
      return 1;
    }
    createCone(args[0],args[1],args[2],args[3],argv[2+CONE_ARGS]);
    free(args);
  }
  else if (prim == "sphere") {

    if (argc < 2 + SPHERE_ARGS) {
      cout << "Invalid arguments!";
      return 1;
    }

    int * args = argsUpdate(argv,SPHERE_ARGS);
    if (!args) {
      cout << "Invalid arguments!";
      return 1;
    }
    createSphere(args[0],args[1],args[2],argv[2+SPHERE_ARGS]);
    free(args);
  }
  else if (prim == "box") {

    if (argc < 2 + BOX_ARGS) {
      cout << "Invalid arguments!";
      return 1;
    }

    int * args;
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

