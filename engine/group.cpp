#include "headers/group.h"
#include "headers/scale.h"
#include "headers/translation.h"
#include <stdlib.h>

struct group {
	std::vector<Model> * models;
	std::vector<Group> * children;
	Scale scale;
	Translation translation;
};

Group newGroup() {
	Group g = (Group) malloc(sizeof(struct group));
	if (g) {
		g->models = new std::vector<Model>();
		g->children = new std::vector<Group>();
		g->scale = newOperation3f();
		if (g->scale) { // set default scales to 1
			setX(g->scale,1);
			setY(g->scale,1);
			setZ(g->scale,1);
		}
		g->translation = newOperation3f();
		if (g->translation) { // set default translation to 0
			setX(g->translation,0);
			setY(g->translation,0);
			setZ(g->translation,0);
		}
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

void addScale(Group g, float x, float y, float z) {
	if (g) {
		setX(g->scale,x);
		setY(g->scale,y);
		setZ(g->scale,z);
	}
}

void addTranslation(Group g, float x, float y, float z) {
	if (g) {
		setX(g->translation,x);
		setY(g->translation,y);
		setZ(g->translation,z);
	}
}