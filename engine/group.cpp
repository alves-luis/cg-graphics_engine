#include "headers/group.h"
#include <stdlib.h>
#include <map>

struct group {
	std::vector<Model> * models;
	std::vector<Group> * children;
	Scale scale;
	Translation translation;
	Rotation rotation;
	int transformationCount;
	std::map<int,char*> * transformationOrder;
};

Group newGroup() {
	Group g = (Group) malloc(sizeof(struct group));
	if (g) {
		g->models = new std::vector<Model>();
		g->children = new std::vector<Group>();
		g->transformationCount = 0;
		g->scale = newOperation3f();
		if (g->scale) { // set default scales to 1
			setX(g->scale,1);
			setY(g->scale,1);
			setZ(g->scale,1);
		}
		g->rotation = newRotation(false);
		g->translation = newTranslation(false);
		g->transformationOrder = new std::map<int,char*>();
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
		g->transformationOrder->insert(std::pair<int,char*>(g->transformationCount++,"scale"));
	}
}

void addRotation(Group g, Rotation r){
	if(g){
		g->rotation = r;
		g->transformationOrder->insert(std::pair<int,char*>(g->transformationCount++,"rotation"));
	}
}

void addTranslation(Group g, Translation t) {
	if (g) {
		g->translation = t;
		g->transformationOrder->insert(std::pair<int,char*>(g->transformationCount++,"translation"));
	}
}

std::vector<Model> * getModels(Group g) {
	if (g) {
		return g->models;
	}
	else {
		return NULL;
	}
}

std::vector<Group> * getGroups(Group g) {
	if (g) {
		return g->children;
	}
	else {
		return NULL;
	}
}

Translation getTranslation(Group g) {
	if (g) {
		return g->translation;
	}
	else {
		return NULL;
	}
}

Scale getScale(Group g) {
	if (g) {
		return g->scale;
	}
	else {
		return NULL;
	}
}

Rotation getRotation(Group g) {
	if (g)
		return g->rotation;
	else
		return NULL;
}

char * getNthTransformation(Group g, int n) {
	if (g && n >= 0 && n < g->transformationOrder->size())
		return g->transformationOrder->at(n);
	else
		return NULL;
}

void initializeVBO(Group g) {
	if (g) {
		std::vector<Model> * models = g->models;
		std::vector<Group> * children = g->children;
		if (models)
			for(Model m : *models) {
				initializeVBO(m);
			}
		if (children)
			for(Group child : *children)
				initializeVBO(child);
	}
}
