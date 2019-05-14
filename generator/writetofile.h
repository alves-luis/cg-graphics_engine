#ifndef WRITETOFILE_H
#define WRITETOFILE_H

#include <stdio.h>

/**
 * Esta função, dadas as coordenadas x,y e z de um vértice, escreve
 * no formato x y z numa nova linha do ficheiro file
 * @param x coordenada x do vértice
 * @param y coordenada y do vértice
 * @param z coordenada z do vértice
 * @param file ficheiro para escrever
 * @return 0 if successful
 * */
int writeVertexToFile(float x, float y, float z, FILE * fName);

/**
 * Esta funçao, dado um index, escreve no formato i
 * numa nova linha do ficheiro fName
 * @param i index a escrever
 * @param fName ficheiro para escrever
 * @return 0 se sucesso*/
int writeIndexToFile(int i, FILE * fName);

/**
 * Esta função, dado um ficheiro, devolve um pointer para este (aberto)
 * @param fname nome do ficheiro
 * @return NULL if can't open, or actual pointer if successful
 * */
FILE * openFile(char * fname);

/**
 * Esta função, dado um file pointer, fecha o ficheiro
 * @param f file pointer
 * */
void closeFile(FILE * f);

/**
 * DEPRECATED
 * Esta função, dadas as coordenadas x,y e z de um vértice, escreve
 * no formato x y z numa nova linha do ficheiro file
 * @param x coordenada x do vértice
 * @param y coordenada y do vértice
 * @param z coordenada z do vértice
 * @param file ficheiro para escrever
 * @return 0 if successful
 * */
int writeToFile(float x, float y, float z, FILE * fName);


int writeBlankToFile(FILE * fName);

int writeNormalToFile(float x, float y, float z, FILE * fName);

#endif
