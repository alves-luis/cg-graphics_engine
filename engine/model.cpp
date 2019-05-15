#include <utility>

#include "headers/model.h"
#include "headers/vertex.h"
#include "headers/scale.h"
#include "headers/color.h"
#include <vector>
#include <stdlib.h>
#include <string.h>
#ifdef __APPLE__
#include <GLUT/glut.h>
#else
#include <GL/glew.h>
#include <GL/glut.h>
#include <cstdio>
#include <string>
#include <IL/il.h>

#endif

struct model {
    std::vector<float> * vertexes;
    std::vector<unsigned int> * indexes;
    std::vector<float> * textureCoords;
    std::vector<float> * normals;
    GLuint vertexBuffer[1];
    GLuint indexBuffer[1];
    GLuint normalBuffer[1];
    GLuint textureBuffer[1];
    std::string * texture;
    GLuint textureID;
    bool hasTexture;
    std::string * modelName;
    bool hasColor;
    Color color;
};

Model newModel(std::string name) {
  Model m = (Model) malloc(sizeof(struct model));
  if (!m)
    return NULL;
  m->vertexes = new std::vector<float>();
  m->indexes = new std::vector<unsigned int>();
  m->textureCoords = new std::vector<float>();
  m->normals = new std::vector<float>();
  m->modelName = new std::string(std::move(name));
  m->color = newColor();
  m->hasTexture = false;
  m->hasColor = false;
  return m;
}

void addVertex(Model m, float v) {
  if (m) {
    m->vertexes->push_back(v);
  }
}

void addIndex(Model m, unsigned int i) {
  if (m) {
    m->indexes->push_back(i);
  }
}

void addTexture(Model m, float x) {
	if (m) {
		m->textureCoords->push_back(x);
	}
}

void addNormal(Model m, float x) {
	if (m) {
		m->normals->push_back(x);
	}
}

float getVertex(Model m, int i) {
  if (m) {
    float v = m->vertexes->at(i);
    return v;
  }
  else
    return -1;
}

int getIndex(Model m, int i) {
  if (m)
    return m->indexes->at(i);
  else
    return -1;
}

std::string getName(Model m) {
  if (m)
    return *(m->modelName);
  else
    return NULL;
}

int getSize(Model m) {
  if (m)
    return (int) m->vertexes->size();
  else
    return 0;
}

int getNumIndexes(Model m) {
  if (m)
    return (int) m->indexes->size();
  else
    return 0;
}

void freeModel(Model m) {
  if (m) {
    m->vertexes->clear();
    m->indexes->clear();
  }
}

std::vector<float> * getVertexes(Model m) {
  if (m)
    return m->vertexes;
  else
    return nullptr;
}

std::vector<unsigned int> * getIndexes(Model m) {
  if (m)
    return m->indexes;
  else
    return NULL;
}

std::vector<float> * getNormals(Model m) {
	if (m)
		return m->normals;
	else
		return NULL;
}

std::vector<float> * getTextureCoords(Model m) {
	if (m)
		return m->textureCoords;
	else
		return NULL;
}

void setVertexes(Model m, std::vector<float> * ver) {
  if (m)
    m->vertexes = ver;
}

void setIndexes(Model m, std::vector<unsigned int> * in) {
  if (m)
    m->indexes = in;
}

void setNormals(Model m, std::vector<float> * n) {
	if (m)
		m->normals = n;
}
void setTextureCoords(Model m, std::vector<float> * v) {
	if (m)
		m->textureCoords = v;
}

void initializeVBO(Model m) {
  if (m) {
  	std::vector<float> vertexes = *m->vertexes;
  	std::vector<unsigned int> indexes = *m->indexes;
  	std::vector<float> normals = *m->normals;
  	std::vector<float> textureCds = *m->textureCoords;
  	float * vertex = &vertexes[0];
  	unsigned int * index = &indexes[0];
  	float * norm = &normals[0];
  	float * tex = &textureCds[0];

  	glGenBuffers(1,m->vertexBuffer);
    glBindBuffer(GL_ARRAY_BUFFER,m->vertexBuffer[0]);
    glBufferData(GL_ARRAY_BUFFER,m->vertexes->size() * sizeof(float),vertex,GL_STATIC_DRAW);

    glGenBuffers(1,m->indexBuffer);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER,m->indexBuffer[0]);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER,m->indexes->size() * sizeof(unsigned int), index,GL_STATIC_DRAW);

    glGenBuffers(1,m->normalBuffer);
    glBindBuffer(GL_ARRAY_BUFFER,m->normalBuffer[0]);
    glBufferData(GL_ARRAY_BUFFER,m->normals->size() * sizeof(float), norm,GL_STATIC_DRAW);

    if (m->hasTexture) {
    	glGenBuffers(1,m->textureBuffer);
    	glBindBuffer(GL_ARRAY_BUFFER,m->textureBuffer[0]);
    	glBufferData(GL_ARRAY_BUFFER,m->textureCoords->size() * sizeof(float), tex, GL_STATIC_DRAW);
    }
  }
}

void drawVBO(Model m) {
	drawColor(m->color);

	glBindBuffer(GL_ARRAY_BUFFER,m->vertexBuffer[0]);
	glVertexPointer(3,GL_FLOAT,0,nullptr);

	glBindBuffer(GL_ARRAY_BUFFER,m->normalBuffer[0]);
	glNormalPointer(GL_FLOAT,0,0);

	if (m->hasTexture) {
		glBindBuffer(GL_ARRAY_BUFFER,m->textureBuffer[0]);
		glTexCoordPointer(2,GL_FLOAT,0,0);
		glBindTexture(GL_TEXTURE_2D,m->textureID);
	}


	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER,m->indexBuffer[0]);
	glDrawElements(GL_TRIANGLES, m->indexes->size(),GL_UNSIGNED_INT,NULL);
	glClearColor(0,0,0,0);
	if (m->hasTexture)
		glBindTexture(GL_TEXTURE_2D,0);
}

void setDiffuse(Model m, float * dif) {
  if (!m)
    return;
  m->hasColor = true;
  setDiffuse(m->color,dif);
}

void setSpecular(Model m, float * spec) {
  if (!m)
    return;
  m->hasColor = true;
  setSpecular(m->color,spec);
}

void setEmissive(Model m, float * em) {
  if (!m)
    return;
  m->hasColor = true;
  setEmissive(m->color,em);
}

void setAmbient(Model m, float * am) {
  if (!m)
    return;
  m->hasColor = true;
  setAmbient(m->color,am);
}

void setTexture(Model m, std::string texture) {
  if (m) {
    m->texture = new std::string(std::move(texture));
    m->hasTexture = true;
    m->hasColor = false;
  }
}

void loadTexture(Model m) {
	if (m && m->hasTexture) {
		unsigned int t, tw, th;
		unsigned char *texData;

		ilInit();
		ilEnable(IL_ORIGIN_SET);
		ilOriginFunc(IL_ORIGIN_LOWER_LEFT);
		ilGenImages(1, &t);
		ilBindImage(t);
		ilLoadImage((ILstring) m->texture->c_str());
		tw = ilGetInteger(IL_IMAGE_WIDTH);
		th = ilGetInteger(IL_IMAGE_HEIGHT);
		ilConvertImage(IL_RGBA, IL_UNSIGNED_BYTE);
		texData = ilGetData();

		glGenTextures(1, &m->textureID);

		glBindTexture(GL_TEXTURE_2D, m->textureID);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);

		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, tw, th, 0, GL_RGBA, GL_UNSIGNED_BYTE, texData);
		glGenerateMipmap(GL_TEXTURE_2D);

		glBindTexture(GL_TEXTURE_2D, 0);
	}
}
