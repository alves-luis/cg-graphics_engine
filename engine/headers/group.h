#ifndef GROUP_H
#define GROUP_H

#include <vector>
#include "model.h"

typedef struct group * Group;
Group newGroup();
std::vector<Model> getModels(Group g);
void addModel(Group g, Model m);
void addGroup(Group g, Group toBeAdded);
void addScale(Group g, float x, float y, float z);
void addTranslation(Group g, float x, float y, float z);

#endif
