#include "box.h"
#include "writetofile.h"
#include <stdio.h>

#define _USE_MATH_DEFINES
#include <math.h>

void drawXZ(float x0, float y0, float z0, float nx, float nz, int div, FILE * file) {
	// Face de Cima
	for(int i = 0; i <= div; i++) {
		for(int j = 0; j <= div; j++) {
			writeVertexToFile(x0 - i * nx,y0,z0 - j * nz,file);
		}
	}
	// Face de baixo
	for(int i = 0; i <= div; i++) {
		for(int j = 0; j <= div; j++) {
			writeVertexToFile(x0 - i * nx, -y0, z0 - j * nz,file);
		}
	}
}

void drawYZ(float x0, float y0, float z0, float ny, float nz, int div, FILE * file) {
	// Face da Esquerda
	for(int i = 0; i <= div; i++) {
		for(int j = 0; j <= div; j++) {
			writeVertexToFile(-x0, y0 - ny*i, z0 - nz*j,file);
		}
	}
	// Face da Direita
	for(int i = 0; i <= div; i++) {
		for(int j = 0; j <= div; j++) {
			writeVertexToFile(x0,y0 - ny*i, z0 - nz*j,file);
		}
	}
}

void drawXY(float x0, float y0, float z0, float nx, float ny, int div, FILE * file) {
	// Face da frente
	for(int i = 0; i <= div; i++) {
		for(int j = 0; j <= div; j++) {
			writeVertexToFile(x0 - j*nx , y0 - i * ny,z0,file);
		}
	}
	// Face de tras
	for(int i = 0; i <= div; i++) {
		for(int j = 0; j <= div; j++) {
			writeVertexToFile(x0 - j*nx, y0 - i * ny, -z0,file);
		}
	}
}
void generateIndices(int div, FILE * file) {
	int currentIndex = 0;
	for(int numPlanos = 0; numPlanos < 3; numPlanos++) {
		// Face para fora
		// D -- C
		// B -- A
		for (int i = 0; i < div; i++) {
			for (int j = 0; j < div; j++) {
				int indexA = i * (div + 1) + j + currentIndex;
				int indexB = (i + 1) * (div + 1) + j + currentIndex;
				int indexC = indexA + 1;
				int indexD = indexB + 1;
				writeIndexToFile(indexA, file);
				writeIndexToFile(indexC, file);
				writeIndexToFile(indexB, file);

				writeIndexToFile(indexB, file);
				writeIndexToFile(indexC, file);
				writeIndexToFile(indexD, file);
			}
		}
		currentIndex += (div + 1) * (div + 1);
		// Face com orientaçao contraria
		// D -- C
		// B -- A
		for (int i = 0; i < div; i++) {
			for (int j = 0; j < div; j++) {
				int indexA = i * (div + 1) + j + currentIndex;
				int indexB = (i + 1) * (div + 1) + j + currentIndex;
				int indexC = indexA + 1;
				int indexD = indexB + 1;

				writeIndexToFile(indexD, file);
				writeIndexToFile(indexC, file);
				writeIndexToFile(indexB, file);

				writeIndexToFile(indexC, file);
				writeIndexToFile(indexA, file);
				writeIndexToFile(indexB, file);
			}
		}
		currentIndex += (div + 1) * (div + 1);
	}
}

int createBox(float x, float y, float z, int div, char * name) {
	FILE * file = openFile(name);
	// invalid arguments
	if (x < 0 || y < 0 || z < 0 || div<0)
		return 1;

	// starting coords
	float x0=x/2;
	float y0=y/2;
	float z0=z/2;

	// baby steps
	float nx=x/div;
	float ny=y/div;
	float nz=z/div;

	drawXZ(x0,y0,z0,nx,nz,div,file);
	drawYZ(x0,y0,z0,ny,nz,div,file);
	drawXY(x0,y0,z0,nx,ny,div,file);
	generateIndices(div,file);
	return 0;
}
