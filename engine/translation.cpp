#include <stdlib.h>
#include <vector>
#include <cmath>
#include "headers/translation.h"
#include "headers/catmull.h"

struct translation {
	Operation3f baseTranslation;
	bool extended;
	std::vector<Vertex> * points;
	float * previousY;
	float time;
};

Translation newTranslation(bool extended) {
	Translation result = (Translation) malloc(sizeof(struct translation));
	if (!result)
		return NULL;

	result->baseTranslation = newOperation3f();

	if (extended) {
		result->extended = true;
		result->points = new std::vector<Vertex>();
		result->previousY = (float *) malloc(sizeof(float) * 3);
		result->previousY[0] = 0;
		result->previousY[1] = 1;
		result->previousY[2] = 0;
		result->time = 0;
	}
	else {
		result->extended = false;
	}
	return result;
}

void addPoint(Translation f, Vertex v) {
	if (f && f->extended) {
		f->points->push_back(v);
	}
}

Vertex getPoint(Translation t, int i) {
	if (t && t->extended && t->points->size() > i) {
		return t->points->at(i);
	}
	else
		return nullptr;
}

void setTime(Translation t, float time) {
	if (t && t->extended) {
		t->time = time * (float) 1e3;
	}
}

float getTime(Translation t) {
	if (t && t->extended)
		return t->time;
	else
		return -1;
}

void setX(Translation t, float x) {
	if (t && !t->extended) {
		setX(t->baseTranslation,x);
	}
}

void setY(Translation t, float y) {
	if (t && !t->extended) {
		setY(t->baseTranslation,y);
	}
}

void setZ(Translation t, float z) {
	if (t && !t->extended) {
		setZ(t->baseTranslation,z);
	}
}

float getX(Translation t) {
	if (t && !t->extended) {
		return getX(t->baseTranslation);
	}
	else
		return 0;
}

float getY(Translation t) {
	if (t && !t->extended) {
		return getY(t->baseTranslation);
	}
	else
		return 0;
}

float getZ(Translation t) {
	if (t && !t->extended) {
		return getZ(t->baseTranslation);
	}
	else
		return 0;
}

void getGlobalCatmullRomPoint(Translation trans, float gt, float * pos, float * deriv) {
	if (trans && trans->extended) {
		int number_of_points = trans->points->size();
		float t = gt * number_of_points; // this is the real global t
		int index = static_cast<int>(floor(t)); // which segment
		t = t - index; // where within the segment

		// indices store the points
		int indices[4];
		indices[0] = (index + number_of_points - 1) % number_of_points;
		indices[1] = (indices[0] + 1) % number_of_points;
		indices[2] = (indices[1] + 1) % number_of_points;
		indices[3] = (indices[2] + 1) % number_of_points;

		float p[4][3];
		for(int i = 0; i < 4; i++) {
			p[i][0] = getX(trans->points->at(indices[i]));
			p[i][1] = getY(trans->points->at(indices[i]));
			p[i][2] = getZ(trans->points->at(indices[i]));
		}

		getCatmullRomPoint(t, p[0], p[1], p[2], p[3], pos, deriv);
	}
}

void drawTranslation(Translation t) {
	if (t && !t->extended)
		glTranslatef(getX(t->baseTranslation),getY(t->baseTranslation),getZ(t->baseTranslation));
	else if (t) {
		float pos[3];
		float deriv[3];

		float scaledT = glutGet(GLUT_ELAPSED_TIME) / t->time;

		getGlobalCatmullRomPoint(t,scaledT,(float *) pos, (float *) deriv);
		glTranslatef(pos[0],pos[1],pos[2]);

		normalize((float *)deriv);

		float z[3];
		cross((float *) deriv, t->previousY, (float * ) z);
		normalize((float *) z);

		cross((float *) z, (float *) deriv, t->previousY);
		normalize(t->previousY);

		float rotateMatrix[4][4];
		buildRotMatrix((float *) deriv,t->previousY,(float *) z,(float *) rotateMatrix);

		glMultMatrixf((float *) rotateMatrix);
	}
}

