#ifndef PARSER_H
#define PARSER_H

#include "model.h"
#include "group.h"
#include <vector>

int loadXML(char * fname, std::vector<Group> * groups);

#endif
