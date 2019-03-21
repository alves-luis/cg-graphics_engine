#ifndef GROUP_H
#define GROUP_H

#include <vector>
#include "model.h"
#include "translation.h"
#include "scale.h"
#include "rotation.h"

typedef struct group * Group;
Group newGroup();
std::vector<Model> * getModels(Group g);
std::vector<Group> * getGroups(Group g);
void addModel(Group g, Model m);
void addGroup(Group g, Group toBeAdded);
void addScale(Group g, float x, float y, float z);
void addRotation(Group g, int angle, float x, float y, float z);
void addTranslation(Group g, float x, float y, float z);
Translation getTranslation(Group g);
Scale getScale(Group g);
Rotation getRotation(Group g);
int getTransformationCount(Group g);

#endif
