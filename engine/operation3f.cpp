#include "operation3f.h"
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