#include "headers/operation3f.h"
#include <stdlib.h>

struct operation3f {
	float x;
	float y;
	float z;
};

Operation3f newOperation3f() {
	Operation3f r = (Operation3f) (malloc(sizeof(struct operation3f)));
	if (r) {
		r->x = 0;
		r->y = 0;
		r->z = 0;
	}
	return r;
}

void setX(Operation3f o, float x) {
	if (o) {
		o->x = x;
	}
}

void setY(Operation3f o, float y) {
	if (o) {
		o->y = y;
	}
}

void setZ(Operation3f o, float z) {
	if (o) {
		o->z = z;
	}
}

float getX(Operation3f o) {
	if (o)
		return o->x;
	else
		return 0;
}

float getY(Operation3f o) {
	if (o)
		return o->y;
	else
		return 0;
}

float getZ(Operation3f o) {
	if (o)
		return o->z;
	else
		return 0;
}