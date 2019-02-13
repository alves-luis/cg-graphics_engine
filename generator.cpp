#include <iostream>

/**
 * What is called when using the generator
 */
int main(int argc, char** argv) {

  if (argc < 2) {
    std::cout << "Invalid arguments!";
    return 1;
  }
  else
    std::cout << argv[1];
  return 0;
}

