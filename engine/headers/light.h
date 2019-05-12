#ifndef ENGINE_LIGHT_H
#define ENGINE_LIGHT_H

typedef struct light * Light;

Light newLight(GLenum i, float * pos, float * amb, float * dif, float * spec, float *sD, float sE, float sC);
void drawLight(Light l);
#endif
