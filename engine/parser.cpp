#include <stdio.h>
#include <stdlib.h>
#include <map>
#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include "headers/parser.h"
#include "headers/model.h"
#include "headers/vertex.h"
#include "tinyxml/tinyxml2.h"
#include "headers/group.h"

using namespace tinyxml2;

/**
 * This function, given a filename, reads its vertices in a .3d format
 * Then, stores those vertices in a Model passed as an argument
 * @param fname file name
 * @param m Model to add the vertices to
 * @return 0 if success
 * */
int parse3D(std::string fname, Model m) {
	std::ifstream file (fname);

	std::string line;

	if (m == NULL) {
		fprintf(stderr,"PARSING FAILURE! Cannot add vertices to NULL Model!\n");
		return 3;
	}

	bool indexes = false;
	while(std::getline(file,line)) {
		std::istringstream stringStream(line);

		float x, y, z;
		if (!indexes) {
			if (!(stringStream >> x >> y >> z)) {
				// could not get 3 floats, so they're indexes
				indexes = true;
				addIndex(m, static_cast<unsigned int>(x));
			} else {
				addVertex(m, x);
				addVertex(m, y);
				addVertex(m, z);
			}
		}
		else {
			unsigned int index;
			stringStream >> index;
			addIndex(m,index);
		}
	}
	if (!indexes) // never seen indexes
		return 4;

	file.close();

	return 0;
}

/**
 * Given an XMLElement (a group of <models>), parses all the <model> tags and adds them to Group g
 * Also, maintains a map modelsMap of already loaded Models.
 * @param models current tag
 * @param g Group to store the models to
 * @param modelsMap map of Models, to avoid reloading .3d files
 * @return 0 if all went good
 * */
int parseModels(XMLElement * models, Group g, std::map<std::string,Model> * modelsMap) {

	XMLElement * model = models->FirstChildElement("model");

	while(model != NULL) {

		std::string fileName = std::string(model->Attribute("file"));

		Model m;
		char * color = (char *) model->Attribute("color");

		if (!color) {
			color = "white"; // default color
		}
		if (modelsMap->find(fileName) == modelsMap->end()) {

			m = newModel(fileName,color);

			int error = parse3D(fileName,m);
			if (error) { // if error in parsing file 3D, don't parse anymore files
				fprintf(stderr,"PARSING FAILURE! Error parsing %s file!\n",fileName.c_str());
				return error;
			}
			modelsMap->insert(std::pair<std::string,Model>(fileName,m));
		}
		else {
			Model old = modelsMap->find(fileName)->second;
			m = newModel(fileName,color);
			setVertexes(m,getVertexes(old));
			setIndexes(m,getIndexes(old));
		}

		addModel(g,m);

		model = model->NextSiblingElement("model");
	}
	return 0;
}

int parseScale(XMLElement * scale, Group g) {

	float x,y,z;
	x = y = z = 1.0f; // default scale is 1
	scale->QueryAttribute("X",&x);
	scale->QueryAttribute("Y",&y);
	scale->QueryAttribute("Z",&z);

	scale = scale->NextSiblingElement("scale");

	if (scale) {// if more scales, it's invalid and don't parse
		fprintf(stderr,"PARSING FAILURE! Cannot have more than 1 scale per generation!\n");
		return 2;
	}

	addScale(g,x,y,z);
	return 0;
}

int parseRotation(XMLElement * rotate, Group g){

	float angle;
	float x,y,z;
	x=y=z=0.0f; //no default axis for rotation
	angle=0; // default angle is 0
	rotate->QueryAttribute("angle",&angle);
	rotate->QueryAttribute("axisX",&x);
	rotate->QueryAttribute("axisY",&y);
	rotate->QueryAttribute("axisZ",&z);

	rotate = rotate -> NextSiblingElement("rotate");

	if (rotate) {// if more rotates, it's invalid and don't parse
		fprintf(stderr,"PARSING FAILURE! Cannot have more than 1 rotation per generation!\n");
		return 2;
	}

	addRotation(g,angle,x,y,z);
	return 0;
}

int parseTranslate(XMLElement * translate, Group g) {
	Translation t;
	float time;
	time = 0.0f; // default translation is 0

	XMLError timeAttribute = translate->QueryFloatAttribute("time",&time);
	// if no attribute, static translation
	if (timeAttribute == XML_NO_ATTRIBUTE) {
		t = newTranslation(false);
		float x,y,z;
		x = y = z; // default translation is 0
		translate->QueryFloatAttribute("X",&x);
		translate->QueryFloatAttribute("Y",&y);
		translate->QueryFloatAttribute("Z",&z);
		setX(t,x);
		setY(t,y);
		setZ(t,z);
	}
	// dynamic translation
	else {
		t = newTranslation(true);
		setTime(t,time);
		XMLElement * point = translate->FirstChildElement(NULL);
		while(point != NULL) {
			Vertex v = newVertex();
			float x, y,z;
			point->QueryFloatAttribute("X",&x);
			point->QueryFloatAttribute("Y",&y);
			point->QueryFloatAttribute("Z",&z);
			setX(v,x);
			setY(v,y);
			setZ(v,z);
			addPoint(t,v);
			point = point->NextSiblingElement("point");
		}

	}

	translate = translate->NextSiblingElement("translate");

	if (translate) { // if more translates, it's invalid and don't parse
		fprintf(stderr,"PARSING FAILURE! Cannot have more than 1 translation per generation!\n");
		return 2;
	}
	addTranslation(g,t);

	return 0;
}

int parseGroup(XMLElement * group, Group g, std::map<std::string,Model> * models) {

	XMLElement * tag = group->FirstChildElement(NULL);

	while(tag != NULL) {
		char * tagName = const_cast<char *>(tag->Name());

		if (!tagName) {
			fprintf(stderr,"PARSING FAILURE! Could not retrieve name of tag!\n");
		}

		int error = 0;

		if (strcmp(tagName,"translate") == 0) {
			error = parseTranslate(tag,g);
		}
		else if (strcmp(tagName,"rotate") == 0) {
			error = parseRotation(tag,g);
		}
		else if (strcmp(tagName,"scale") == 0) {
			error = parseScale(tag,g);
		}
		else if (strcmp(tagName,"group") == 0) {
			Group child = newGroup();
			error = parseGroup(tag,child,models);
			addGroup(g,child);
		}
		else if (strcmp(tagName,"models") == 0) {
			error = parseModels(tag,g,models);
		}

		if (error) { // if error stop parsing
			fprintf(stderr,"PARSING FAILURE! Error parsing a group!\n");
			return error;
		}

		tag = tag->NextSiblingElement(NULL);
	}
	return 0;
}

int loadXML(char * fname, std::vector<Group> * groups) {

	if (fname)
		printf("Loading %s\n",fname);

	XMLDocument doc;
	std::map<std::string,Model> * models= new std::map<std::string,Model>();

	XMLError err = doc.LoadFile(fname);
	if (err) {
		fprintf(stderr,"TINYXML FAILURE! Error code: %d\n",err);
		return err;
	}

	XMLElement* scene = doc.FirstChildElement("scene");
	if (!scene) {
		fprintf(stderr,"TINYXML FAILURE! Error code: %d\n",XML_ERROR_PARSING_ELEMENT);
		return XML_ERROR_PARSING_ELEMENT;
	}

	XMLElement* group = scene->FirstChildElement("group");

	while(group != NULL) {
		Group parsedGroup = newGroup();
		int error = parseGroup(group,parsedGroup,models);
		if (error) // if error in parsing group, don't parse anymore
			return error;

		groups->push_back(parsedGroup);
		group = group->NextSiblingElement("group");
	}

	return 0;
}
