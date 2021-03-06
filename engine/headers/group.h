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

/**
 * Given a Group, returns its models
 * @param g Group to retrieve the models from
 * @return pointer to the vector of models
 * */
std::vector<Model> * getModels(Group g);

/**
 * Given a Group, return its children Groups
 * @param g Group to retrieve the groups from
 * @return pointer to the vector of groups
 * */
std::vector<Group> * getGroups(Group g);

/**
 * Given a Group, add a Model to it
 * @param g Group to add the model to
 * @param m Model to be added to the Group
 * */
void addModel(Group g, Model m);

/**
 * Given a Group, add another Group to it
 * @param g Group to add the group to
 * @param toBeAdded Group to add as children to g
 * */
void addGroup(Group g, Group toBeAdded);

/**
 * Given a group, adds a scale by the xAxis, yAxis and zAxis
 * @param g Group to add the Scale to
 * @param x scale factor in xAxis
 * @param y scale factor in yAxis
 * @param z scale factor in zAxis
 * */
void addScale(Group g, float x, float y, float z);

/**
 * Given a group, adds a Rotation of a given angle by a given vector
 * @param g Group to add the Rotation to
 * @param r Pointer to the rotation
 * */
void addRotation(Group g, Rotation r);

/**
 * Given a group, adds a Translation to the group
 * @param g Group to add the Translation to
 * @param t Translation
 * */
void addTranslation(Group g, Translation t);

/**
 * Given a group, returns the translation associated with that group
 * @param g Group to retrieve the translation
 * @return Translation
 * */
Translation getTranslation(Group g);

/**
 * Given a group, returns the scale associated with that group
 * @param g Group to retrieve the scale
 * @return Scale
 * */
Scale getScale(Group g);

/**
 * Given a group, returns the rotation associated with that group
 * @param g Group to retrieve the rotation
 * @return Rotation
 * */
Rotation getRotation(Group g);

/**
 * Given a group, and an index, returns the n-th transformation in the sequence of
 * transformations. Does not return the pointer, returns the textual representation
 * of that transfomation. Either NULL, "rotation", "scale" or "translation"
 * @param g Group to retrieve the info from
 * @param n index of transformation (0-2)
 * @return textual representation
 * */
char * getNthTransformation(Group g, int n);

/**
 * Generates all the buffers of the models in that group
 * @param g Group
 * */
void initializeVBO(Group g);

void loadTexture(Group g);

#endif
