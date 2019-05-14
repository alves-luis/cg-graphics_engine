#include "box.h"
#include "writetofile.h"
#include "vertex.h"
#include <stdio.h>
#include <vector>

#define _USE_MATH_DEFINES
#include <math.h>

void drawXZ(float x0, float y0, float z0, float nx, float nz, int div, FILE * file, std::vector<Vertex> * normals, std::vector<Vertex> * textures) {
	// Face de Cima
	for(int i = 0; i <= div; i++) {
		for(int j = 0; j <= div; j++) {
			writeVertexToFile(x0 - i * nx,y0,z0 - j * nz,file);
			Vertex norm = newVertex();
			setX(norm,0.0f);
			setY(norm,1.0f);
			setZ(norm,0.0f);
			normals->push_back(norm);
			Vertex tex = newVertex();
			setX(tex, static_cast<float>(i)/div);
			setY(tex, static_cast<float>(j)/div);
			textures->push_back(tex);
		}
	}
	// Face de baixo
	for(int i = 0; i <= div; i++) {
		for(int j = 0; j <= div; j++) {
			writeVertexToFile(x0 - i * nx, -y0, z0 - j * nz,file);
			Vertex norm = newVertex();
			setX(norm,0.0f);
			setY(norm,-1.0f);
			setZ(norm,0.0f);
			normals->push_back(norm);
			Vertex tex = newVertex();
			setX(tex, static_cast<float>(i)/div);
			setY(tex, static_cast<float>(j)/div);
			textures->push_back(tex);
		}
	}
}

void drawYZ(float x0, float y0, float z0, float ny, float nz, int div, FILE * file, std::vector<Vertex> * normals, std::vector<Vertex> * textures) {
	// Face da Esquerda
	for(int i = 0; i <= div; i++) {
		for(int j = 0; j <= div; j++) {
			writeVertexToFile(-x0, y0 - ny*i, z0 - nz*j,file);
			Vertex norm = newVertex();
			setX(norm,-1.0f);
			setY(norm,0.0f);
			setZ(norm,0.0f);
			normals->push_back(norm);
			Vertex tex = newVertex();
			setX(tex, static_cast<float>(i)/div);
			setY(tex, static_cast<float>(j)/div);
			textures->push_back(tex);
		}
	}
	// Face da Direita
	for(int i = 0; i <= div; i++) {
		for(int j = 0; j <= div; j++) {
			writeVertexToFile(x0,y0 - ny*i, z0 - nz*j,file);
			Vertex norm = newVertex();
			setX(norm,1.0f);
			setY(norm,0.0f);
			setZ(norm,0.0f);
			normals->push_back(norm);
			Vertex tex = newVertex();
			setX(tex, static_cast<float>(i)/div);
			setY(tex, static_cast<float>(j)/div);
			textures->push_back(tex);
		}
	}
}

void drawXY(float x0, float y0, float z0, float nx, float ny, int div, FILE * file, std::vector<Vertex> * normals, std::vector<Vertex> * textures) {
	// Face da frente
	for(int i = 0; i <= div; i++) {
		for(int j = 0; j <= div; j++) {
			writeVertexToFile(x0 - j*nx , y0 - i * ny,z0,file);
			Vertex norm = newVertex();
			setX(norm,0.0f);
			setY(norm,0.0f);
			setZ(norm,1.0f);
			normals->push_back(norm);
			Vertex tex = newVertex();
			setX(tex, static_cast<float>(j)/div);
			setY(tex, static_cast<float>(i)/div);
			textures->push_back(tex);
		}
	}
	// Face de tras
	for(int i = 0; i <= div; i++) {
		for(int j = 0; j <= div; j++) {
			writeVertexToFile(x0 - j*nx, y0 - i * ny, -z0,file);
			Vertex norm = newVertex();
			setX(norm,0.0f);
			setY(norm,0.0f);
			setZ(norm,-1.0f);
			normals->push_back(norm);
			Vertex tex = newVertex();
			setX(tex, static_cast<float>(j)/div);
			setY(tex, static_cast<float>(i)/div);
			textures->push_back(tex);
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

	std::vector<Vertex> normals;
	std::vector<Vertex> textures;

	drawXZ(x0,y0,z0,nx,nz,div,file,&normals,&textures);
	drawYZ(x0,y0,z0,ny,nz,div,file,&normals,&textures);
	drawXY(x0,y0,z0,nx,ny,div,file,&normals,&textures);
	generateIndices(div,file);

	for(Vertex v : normals)
		writeVertexToFile(getX(v),getY(v),getZ(v),file);
	for(Vertex v : textures)
		writeTextureToFile(getX(v),getY(v),file);

	return 0;
}
