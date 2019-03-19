#include <stdio.h>
#include <stdlib.h>
#include "parser.h"
#include "model.h"
#include "vertex.h"
#include "tinyxml/tinyxml2.h"

using namespace tinyxml2;

/**
 * This function, given a filename, reads its vertixes in a .3d format
 * Then, stores those vertexes in a Model named after the file
 * and pushes the model to the global variable models.
 * @param fname file name
 * @return 0 if success
 * */
int parse3D(char * fname, std::vector<Model> * models) {
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
	(*models).push_back(m);
	free(line);

	return 0;
}

/**
 * This function, given a file name, loads its XML content using
 * tinyxml2
 * @param fname file name
 * @return 0 if success
 * */
int loadXML(char * fname, std::vector<Model> * models) {
	XMLDocument doc;

	XMLError err = doc.LoadFile(fname);
	if (err)
		return err;

	XMLElement* scene = doc.FirstChildElement("scene");
	if (!scene)
		return XML_ERROR_PARSING_ELEMENT;

	XMLElement* model = scene->FirstChildElement("model");

	while(model != NULL) {

		char * fileName = (char *) model->Attribute("file");

		int error = parse3D(fileName,models);
		if (error) // if error in parsing file 3D, don't parse anymore files
			return error;

		model = model->NextSiblingElement("model");
	}
	return 0;
}
