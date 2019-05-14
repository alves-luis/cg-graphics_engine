#include <GL/glew.h>
#include <malloc.h>
#include "headers/light.h"

struct light {
	GLenum number; // number of the light
	float position[4]; // position
	float ambient[4]; // ambient component
	float diffuse[4]; // diffuse component
	float specular[4]; // specular component
	float spotDirection[3]; // direction
	float spotExponent;
	float spotCut;
};

Light newLight(GLenum i, float * pos, float * amb, float * dif, float * spec, float *sD, float sE, float sC) {
	Light result = (Light) malloc(sizeof(struct light));
	if (!result)
		return NULL;
	result->number = i;
	for(int i = 0; i < 4; i++) {
		result->position[i] = pos[i];
		result->ambient[i] = amb[i];
		result->diffuse[i] = dif[i];
		result->specular[i] = spec[i];
		if (i < 3)
			result->spotDirection[i] = sD[i];
	}
	result->spotExponent = sE;
	result->spotCut = sC;
	return result;
}

void drawLight(Light l) {
	if (!l)
		return;
	glClearColor(0, 0, 0, 0);
	glLightfv(l->number,GL_POSITION,l->position);
	glLightfv(l->number,GL_AMBIENT,l->ambient);
	glLightfv(l->number,GL_DIFFUSE,l->diffuse);
	glLightfv(l->number,GL_SPECULAR,l->specular);
	glLightfv(l->number,GL_SPOT_DIRECTION,l->spotDirection);
	glLightf(l->number,GL_SPOT_EXPONENT,l->spotExponent);
	glLightf(l->number,GL_SPOT_CUTOFF,l->spotCut);
}

void enableLight(Light l) {
	if (!l)
		return;
	glEnable(l->number);
}