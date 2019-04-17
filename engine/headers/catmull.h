#ifndef CATMULL_H
#define CATMULL_H

void buildRotMatrix(float *x, float *y, float *z, float *m);
void cross(float *a, float *b, float *res);
void normalize(float *a);
void getCatmullRomPoint(float t, float * p0, float * p1, float * p2, float * p3, float * pos, float * deriv);

#endif
