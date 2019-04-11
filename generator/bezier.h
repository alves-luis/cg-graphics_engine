#ifndef BEZIER_H
#define BEZIER_H

#include <vector>
#include "vertex.h"

/**
 * Given a file name, puts the control points and indices of a given
 * Bezier patch in the given vectors
 * @param fileName file which contains the patch
 * @param controlPoints vector where the controlpoints are stored
 * @param indices vector where the indices are stored
 * @return 0 if success
 * */
int parseBezierPatch(char * fileName, std::vector<Vertex> * controlPoints, std::vector<int> * indices);

/**
 * Given control points and indices, and a tesselation level, returns
 * the list of triangles to draw the surface, in the file
 * @param controlPoints
 * @param indices
 * @param tesselation*/
int generateBezierModel(std::vector<Vertex> * controlPoints, std::vector<int> * indices, int tessellation, char * file);

#endif BEZIER_H
