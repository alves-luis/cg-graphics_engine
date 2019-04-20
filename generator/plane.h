#ifndef PLANE_H
#define PLANE_H

/**
 * The function, given a size and a filename, writes the vertices of the corresponding plane
 * in the given file name.
 * @param size Size of the side of the plane.
 * @param fname name of the file in which the vertices will be written.
 * @returns 0 if successful */
int createPlane(float size, char * fname);
#endif
