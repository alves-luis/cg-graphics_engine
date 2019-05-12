#ifndef ENGINE_COLOR_H
#define ENGINE_COLOR_H

typedef struct color * Color;

Color newColor();

void setDiffuse(Color c, float * dif);
void setSpecular(Color c, float * spec);
void setEmissive(Color c, float * em);
void setAmbient(Color c, float * am);
void drawColor(Color c);
#endif
