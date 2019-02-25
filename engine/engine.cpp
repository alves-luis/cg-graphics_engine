#include "tinyxml/tinyxml2.h"
#include <iostream>

using namespace tinyxml2;
using namespace std;

typedef struct models {

};

int parse3D(const char * fname) {
  return 1;
}

int loadXML(char * fname) {
  XMLDocument doc;

  XMLError err = doc.LoadFile(fname);
  if (err)
    return err;

  XMLElement* scene = doc.FirstChildElement("scene");
  if (!scene)
    return XML_ERROR_PARSING_ELEMENT;

  XMLElement* model = scene->FirstChildElement("model");
  while(model != NULL) {
    const char * fileName = model->Attribute("file");
    cout << fileName << "\n";
    int error = parse3D(fileName);
    model = model->NextSiblingElement("model");
  }
}

int main(int argc, char** argv) {

  if (argc < 2) {
    cout << "Invalid configuration file!\n";
    return 1;
  }

  int error = loadXML(argv[1]);
  cout << error;
}