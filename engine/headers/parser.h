#ifndef PARSER_H
#define PARSER_H

#include "model.h"
#include "group.h"
#include <vector>
#include <map>

int loadXML(char * fname, std::vector<Group> * groups, std::map<char*,Model> * models);


#endif
