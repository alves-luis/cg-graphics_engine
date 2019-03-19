#include "group.h"
#include <stdlib.h>

struct group {
	std::vector<Model> * models;
	std::vector<Group> * children;

};

Group newGroup() {
	Group g = (Group) malloc(sizeof(struct group));
	if (g) {
		g->models = new std::vector<Model>();
		g->children = new std::vector<Group>();
	}
	return g;
}

void addModel(Group g, Model m) {
	if (g) {
		g->models->push_back(m);
	}
}

void addGroup(Group g, Group toBeAdded) {
	if (g) {
		g->children->push_back(toBeAdded);
	}
}