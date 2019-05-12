#include <malloc.h>
#include "headers/color.h"
#include <GL/glew.h>

struct color {
	float diffuse[4];
	float specular[4];
	float emissive[4];
	float ambient[4];
};

Color newColor() {
	Color c = (Color) malloc(sizeof(struct color));
	if (!c)
		return NULL;
	for(int i = 0; i < 4; i++) {
		if (i != 3) {
			c->diffuse[i] = 0.8f;
			c->specular[i] = 0.0f;
			c->emissive[i] = 0.0f;
			c->ambient[i] = 0.2f;
		}
		else {
			c->diffuse[i] = 1.0f;
			c->specular[i] = 1.0f;
			c->emissive[i] = 1.0f;
			c->ambient[i] = 1.0f;
		}
	}
	return c;
}

void setDiffuse(Color c, float * dif) {
	if (!c)
		return;
	for(int i = 0; i < 3; i++)
		c->diffuse[i] = dif[i];
}

void setSpecular(Color c, float * spec) {
	if (!c)
		return;
	for(int i = 0; i < 3; i++)
		c->specular[i] = spec[i];
}

void setEmissive(Color c, float * em) {
	if (!c)
		return;
	for(int i = 0; i < 3; i++)
		c->emissive[i] = em[i];
}

void setAmbient(Color c, float * am) {
	if (!c)
		return;
	for(int i = 0; i < 3; i++)
		c->ambient[i] = am[i];
}

void drawColor(Color c) {
	glMaterialfv(GL_FRONT, GL_DIFFUSE, c->diffuse);
	glMaterialfv(GL_FRONT, GL_SPECULAR, c->specular);
	glMaterialfv(GL_FRONT, GL_EMISSION, c->emissive);
	glMaterialfv(GL_FRONT, GL_AMBIENT, c->ambient);
}

