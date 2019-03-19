#include <stdio.h>
#include <stdlib.h>
#include "parser.h"
#include "model.h"
#include "vertex.h"
#include "tinyxml/tinyxml2.h"
#include "group.h"

#ifndef XMLCheckResult
#define XMLCheckResult(a_eResult) if (a_eResult != XML_SUCCESS) { printf("Error: %i\n", a_eResult); return a_eResult; }
#endif

using namespace tinyxml2;

/**
 * This function, given a filename, reads its vertixes in a .3d format
 * Then, stores those vertexes in a Model passed as an argument
 * @param fname file name
 * @return 0 if success
 * */
int parse3D(char * fname, Model * model) {
	FILE * file = fopen(fname,"r");

	if (file == NULL)
		return 1;

	float x, y, z;
	char * line = (char *) malloc(sizeof(char)*1024);

	if (line == NULL)
		return 2;

	size_t size;
	Model m = newModel(fname);

	if (m == NULL)
		return 3;

	Vertex v;
	while((getline(&line, &size, file)) > 0) {
		int suc = sscanf(line,"%f %f %f",&x,&y,&z);
		if (suc != 3) {// if can't get 3 axes, can't parse and return failure;
			freeModel(m);
			return 4;
		}
		v = newVertex();
		setX(v,x);
		setY(v,y);
		setZ(v,z);
		addVertex(m,v);
	}
	*model = m;
	free(line);

	return 0;
}

int parseModels(XMLElement * models, Group g) {

	XMLElement * model = models->FirstChildElement("model");

	while(model != NULL) {

		char * fileName = (char *) model->Attribute("file");
		Model m;
		int error = parse3D(fileName,&m);
		if (error) // if error in parsing file 3D, don't parse anymore files
			return error;

		addModel(g,m);

		model = model->NextSiblingElement("model");
	}

	return 0;
}

int parseGroup(XMLElement * group, Group g) {

	XMLElement * tag = group->FirstChildElement(NULL);

	while(tag != NULL) {
		char * tagName = const_cast<char *>(tag->Name());
		int error = 0;

		if (strcmp(tagName,"translate") == 0) {

		}
		else if (strcmp(tagName,"rotate") == 0) {

		}
		else if (strcmp(tagName,"scale") == 0) {

		}
		else if (strcmp(tagName,"group") == 0) {
			Group child = newGroup();
			error = parseGroup(tag,child);
			addGroup(g,child);
		}
		else if (strcmp(tagName,"models") == 0) {
			error = parseModels(tag,g);
		}

		if (error) // if error stop parsing
			return error;

		tag = tag->NextSiblingElement(NULL);
	}
}

/**
 * This function, given a file name, loads its XML content using
 * tinyxml2
 * @param fname file name
 * @return 0 if success
 * */
int loadXML(char * fname, std::vector<Group> * groups) {
	XMLDocument doc;

	XMLError err = doc.LoadFile(fname);
	if (err)
		return err;

	XMLElement* scene = doc.FirstChildElement("scene");
	if (!scene)
		return XML_ERROR_PARSING_ELEMENT;

	XMLElement* group = scene->FirstChildElement("group");

	while(group != NULL) {
		Group parsedGroup = newGroup();
		int error = parseGroup(group,parsedGroup);
		if (error) // if error in parsing group, don't parse anymore
			return error;

		groups->push_back(parsedGroup);
		group = group->NextSiblingElement("group");
	}

	return 0;
}
