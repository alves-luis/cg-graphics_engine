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
#include "headers/light.h"

using namespace tinyxml2;


int parseLights(XMLElement * lights, std::vector<Light> * vecL) {
	XMLElement * light = lights->FirstChildElement("light");

	int currentLight = 0;
	while (light != NULL) {
		const char *type = light->Attribute("type");

		float pos[4] = { 0.0f, 0.0f, 0.0f, 1.0f }; // default is a point
		float amb[4] = { 0.0f, 0.0f, 0.0f, 1.0f }; // opengl default
		float dif[4] = { 1.0f, 1.0f, 1.0f, 1.0f }; //opengl default
		float spec[4] = { 1.0f, 1.0f, 1.0f, 1.0f}; // opengl default
		float spotD[3] = { 0.0f, 0.0f, -1.0f }; // opengl default
		float spotExp = 0.0f; // opengl default, uniform light dist
		float spotCut = 180.0f; // opengl default, uniform light dist

		light->QueryAttribute("posX", pos);
		light->QueryAttribute("posY", pos + 1);
		light->QueryAttribute("posZ", pos + 2);
		// if directional, it's vector
		if (strcmp(type,"DIRECTIONAL") == 0)
			pos[3] = 0.0f;

		light->QueryAttribute("ambR",amb);
		light->QueryAttribute("ambG",amb + 1);
		light->QueryAttribute("ambB",amb + 2);

		light->QueryAttribute("diffR",dif);
		light->QueryAttribute("diffG",dif + 1);
		light->QueryAttribute("diffB",dif + 2);

		light->QueryAttribute("specR",spec);
		light->QueryAttribute("specG",spec + 1);
		light->QueryAttribute("specB",spec + 2);

		light->QueryAttribute("dX", spotD);
		light->QueryAttribute("dY",spotD + 1);
		light->QueryAttribute("dZ", spotD + 2);

		light->QueryAttribute("exp",&spotExp);
		light->QueryAttribute("cut",&spotCut);

		GLenum i = GL_LIGHT0 + currentLight;
		glEnable(i);
		Light l = newLight(i,pos,amb,dif,spec,spotD,spotExp,spotCut);
		vecL->push_back(l);
		currentLight++;


		light = light->NextSiblingElement("light");
	}

	if (currentLight < 8)
		return 0;
	else
		return 1;
}

/**
 * This function, given a filename, reads its vertices in a .3d format
 * Then, stores those vertices in a Model passed as an argument
 * @param fname file name
 * @param m Model to add the vertices to
 * @return 0 if success
 * */
int parse3D(const std::string &fname, Model m) {
	std::ifstream file (fname);

	std::string line;

	if (m == nullptr) {
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

	while(model != nullptr) {

		std::string fileName = std::string(model->Attribute("file"));

		Model m;

		if (modelsMap->find(fileName) == modelsMap->end()) {

			m = newModel(fileName);

			int error = parse3D(fileName,m);
			if (error) { // if error in parsing file 3D, don't parse anymore files
				fprintf(stderr,"PARSING FAILURE! Error parsing %s file!\n",fileName.c_str());
				return error;
			}
			modelsMap->insert(std::pair<std::string,Model>(fileName,m));
		}
		else {
			Model old = modelsMap->find(fileName)->second;
			m = newModel(fileName);
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
	x = y = z = 0.0f; //no default axis for rotation
	angle = 0; // default angle is 0
	Rotation r;

	XMLError timeAttribute = rotate->QueryAttribute("time",&angle);
	// if does not have time, should have angle
	if (timeAttribute == XML_NO_ATTRIBUTE) {
		rotate->QueryAttribute("angle",&angle);
		r = newRotation(false);
		setAngle(r,angle);
	}
	// if has time, set time
	else {
		r = newRotation(true);
		setTime(r,angle);
	}
	rotate->QueryAttribute("axisX",&x);
	rotate->QueryAttribute("axisY",&y);
	rotate->QueryAttribute("axisZ",&z);
	setX(r,x);
	setY(r,y);
	setZ(r,z);

	rotate = rotate -> NextSiblingElement("rotate");

	if (rotate) {// if more rotates, it's invalid and don't parse
		fprintf(stderr,"PARSING FAILURE! Cannot have more than 1 rotation per generation!\n");
		return 2;
	}

	addRotation(g,r);
	return 0;
}

int parseTranslate(XMLElement * translate, Group g) {
	Translation t;
	float time;
	time = 0.0f; // default translation is 0

	XMLError timeAttribute = translate->QueryAttribute("time",&time);
	// if no attribute, static translation
	if (timeAttribute == XML_NO_ATTRIBUTE) {
		t = newTranslation(false);
		float x,y,z;
		x = y = z = 0; // default translation is 0
		translate->QueryAttribute("X",&x);
		translate->QueryAttribute("Y",&y);
		translate->QueryAttribute("Z",&z);
		setX(t,x);
		setY(t,y);
		setZ(t,z);
	}
	// dynamic translation
	else {
		t = newTranslation(true);
		setTime(t,time);
		XMLElement * point = translate->FirstChildElement(nullptr);
		while(point != nullptr) {
			Vertex v = newVertex();
			float x, y,z;
			point->QueryAttribute("X",&x);
			point->QueryAttribute("Y",&y);
			point->QueryAttribute("Z",&z);
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

	XMLElement * tag = group->FirstChildElement(nullptr);

	while(tag != nullptr) {
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

		tag = tag->NextSiblingElement(nullptr);
	}
	return 0;
}

int loadXML(char * fname, std::vector<Group> * groups, std::vector<Light> * lights) {

	if (fname)
		printf("Loading %s\n",fname);

	XMLDocument doc;
	auto * models = new std::map<std::string,Model>();

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

	// lights should be at the start of the xml
	XMLElement* light = scene->FirstChildElement("lights");
	if (light != NULL) {// if there are any
		int error = parseLights(light, lights);
		if (error) {
			fprintf(stderr,"Maximum number of lights exceeded!");
			return error;
		}
	}

	XMLElement* group = scene->FirstChildElement("group");

	while(group != nullptr) {
		Group parsedGroup = newGroup();
		int error = parseGroup(group,parsedGroup,models);
		if (error) // if error in parsing group, don't parse anymore
			return error;

		groups->push_back(parsedGroup);
		group = group->NextSiblingElement("group");
	}

	return 0;
}
