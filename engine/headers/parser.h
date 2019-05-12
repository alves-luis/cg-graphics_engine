#ifndef PARSER_H
#define PARSER_H

#include "group.h"
#include "light.h"
#include <vector>

/**
 * Given a file name and a vector of Groups, parses the file
 * and puts all the XML content in the vector.
 * Returns 0 if all went well
 * @param fname name of file
 * @param groups pointer to store the parsed data
 * @return 0 if all went good
 * */
int loadXML(char * fname, std::vector<Group> * groups, std::vector<Light> * lights);

#endif
