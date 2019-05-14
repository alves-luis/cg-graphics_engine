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


void generateNormals(int div, FILE * file) {

		for (int i = 0; i < div; i++) { //xz cima
			for (int j = 0; j < div; j++) {
				for (int a = 0; a < 6; a++) {
					writeNormalToFile(0, 1, 0,file);
				}
			}
		}
		
		for (int i = 0; i < div; i++) { //xz baixo
			for (int j = 0; j < div; j++) {
				for (int a = 0; a < 6; a++) {
					writeNormalToFile(0, -1, 0,file);
				}
			}
		}

		for (int i = 0; i < div; i++) { //yz esquerda
			for (int j = 0; j < div; j++) {
				for (int a = 0; a < 6; a++) {
					writeNormalToFile(-1, 0, 0,file);
				}
			}
		}

		for (int i = 0; i < div; i++) { //yz direita
			for (int j = 0; j < div; j++) {
				for (int a = 0; a < 6; a++) {
					writeNormalToFile(1, 0, 0,file);
				}
			}
		}

		for (int i = 0; i < div; i++) { //xz frente
			for (int j = 0; j < div; j++) {
				for (int a = 0; a < 6; a++) {
					writeNormalToFile(0, 0, 1,file);
				}
			}
		}

		for (int i = 0; i < div; i++) { //xz trás
			for (int j = 0; j < div; j++) {
				for (int a = 0; a < 6; a++) {
					writeNormalToFile(0, 0, -1,file);
				}
			}
		}
}

	

	void drawTextCoords(int div, FILE * file) {
		int n = 1 / 6;
		int t = n/div;
		int k = 0;
		
		// Face da frente
		for (int i = 0; i <= div; i++) {
			for (int j = 0; j <= div; j++) {
				writeTextureToFile(k + t * i, k + t * j, file);
			}
		}
		k= 1 / 6;
		// Face de tras
		for (int i = 0; i <= div; i++) {
			for (int j = 0; j <= div; j++) {
				writeTextureToFile(k + t * i, k + t * j, file);
			}
		}
		k = 2 / 6;
		// Face da frente
		for (int i = 0; i <= div; i++) {
			for (int j = 0; j <= div; j++) {
				writeTextureToFile(k + t * i, k + t * j, file);
			}
		}
		k = 3 / 6;
		// Face de tras
		for (int i = 0; i <= div; i++) {
			for (int j = 0; j <= div; j++) {
				writeTextureToFile(k + t * i, k + t * j, file);
			}
		}
		k = 4 / 6;
		// Face da frente
		for (int i = 0; i <= div; i++) {
			for (int j = 0; j <= div; j++) {
				writeTextureToFile(k + t * i, k + t * j, file);
			}
		}
		k = 5 / 6;
		// Face de tras
		for (int i = 0; i <= div; i++) {
			for (int j = 0; j <= div; j++) {
				writeTextureToFile(k + t * i, k + t * j, file);
			}
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
	generateNormals(div, file);
	drawTextCoords(div, file);
	return 0;
}
