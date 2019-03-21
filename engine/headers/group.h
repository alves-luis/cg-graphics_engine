#ifndef GROUP_H
#define GROUP_H

#include <vector>
#include "model.h"
#include "translation.h"
#include "scale.h"
#include "rotation.h"

/**
 * Group is a pointer to the actual implementation
 * */
typedef struct group * Group;

/**
 * Allocs memory to a new group. Sets default scale to 1, translation and rotation to 0.
 * @return pointer to the new group, or NULL if failed
 * */
Group newGroup();
std::vector<Model> * getModels(Group g);
std::vector<Group> * getGroups(Group g);
void addModel(Group g, Model m);
void addGroup(Group g, Group toBeAdded);
void addScale(Group g, float x, float y, float z);
void addRotation(Group g, float angle, float x, float y, float z);
void addTranslation(Group g, float x, float y, float z);
Translation getTranslation(Group g);
Scale getScale(Group g);
Rotation getRotation(Group g);
char * getNthTransformation(Group g, int n);

#endif
