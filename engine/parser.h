#ifndef PARSER_H
#define PARSER_H

#include "model.h"
#include <vector>

int parse3D(char * fname, std::vector<Model> * vector);
int loadXML(char * fname, std::vector<Model> * models);

#endif
