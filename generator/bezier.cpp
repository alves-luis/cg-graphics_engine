#include "bezier.h"
#include "writetofile.h"
#include <string>
#include <fstream>
#include <sstream>

float bezierM[4][4] = {{ -1.0f, 3.0f, -3.0f, 1.0f},
					   { 3.0f, -6.0f, 3.0f, 0.0f},
					   { -3.0f, 3.0f, 0.0f, 0.0f},
					   { 1.0f, 0.0f, 0.0f, 0.0f}};

void multMatrixVector(float *m, float *v, float *res) {

	for (int j = 0; j < 4; ++j) {
		res[j] = 0;
		for (int k = 0; k < 4; ++k) {
			res[j] += v[k] * m[j * 4 + k];
		}
	}
}

void multVectorMatrix(float *v, float *m, float *res) {
	for(int i = 0; i < 4; ++i) {
		res[i] = 0;
		for(int j = 0; j < 4; ++j) {
			res[i] += v[j] * m[j*4+i];
		}
	}
}


int parseBezierPatch(char * fileName, std::vector<Vertex> * controlPoints, std::vector<int> * indices) {
	std::ifstream file (fileName);
	std::string line;

	int numPatches = 0;
	int numControlPoints = 0;
	int current_line = 0;

	while(std::getline(file,line)) {
		std::istringstream stringStream(line);

		if (current_line == 0) {
			if (!(stringStream >> numPatches)) {
				fprintf(stderr,"PARSING FAILURE! Could not retrieve number of patches!");
				return 1;
			}
		}
		// parse patches
		else if (current_line > 0 && current_line <= numPatches) {

			unsigned long pos = 0;
			std::string token;
			std::string stringNoStream = stringStream.str();
			int index;
			while((pos = stringNoStream.find(',')) != std::string::npos) {
				token = stringNoStream.substr(0,pos);
				std::stringstream auxStream(token);
				auxStream >> index;
				(*indices).push_back(index);
				stringNoStream.erase(0,pos + 1);
			}
			std::stringstream auxStream(stringNoStream);
			auxStream >> index;
			(*indices).push_back(index);

		}
		// parse num of control points
		else if (current_line == numPatches + 1) {
			if (!(stringStream >> numControlPoints)) {
				fprintf(stderr,"PARSING FAILURE! Could not retrieve number of control points!");
				return 1;
			}
		}
		// parse control points
		else if (current_line < numPatches + numControlPoints + 2) {
			unsigned long pos = 0;
			std::string token;
			std::string stringNoStream = stringStream.str();
			float axis[3];
			int i = 0;
			while((pos = stringNoStream.find(',')) != std::string::npos) {
				token = stringNoStream.substr(0,pos);
				std::stringstream auxStream(token);
				auxStream >> axis[i];
				stringNoStream.erase(0,pos + 1);
				i++;
			}
			std::stringstream auxStream(stringNoStream);
			auxStream >> axis[2];
			Vertex v = newVertex();
			setX(v,axis[0]);
			setY(v,axis[1]);
			setZ(v,axis[2]);
			(*controlPoints).push_back(v);
		}
		current_line++;
	}
	return 0;
}

void getBezier(float u, float v, float ** pX, float ** pY, float ** pZ, float * coords) {
	float U[4] = { u*u*u, u*u, u, 1};
	float V[4] = { v*v*v, v*v, v, 1};

	float UM[4]; // U*M
	multVectorMatrix(U,*bezierM,UM);

	float UMP[3][4]; // U*M*P
	multVectorMatrix(UM,(float *)pX,UMP[0]);
	multVectorMatrix(UM,(float *)pY,UMP[1]);
	multVectorMatrix(UM,(float *)pZ,UMP[2]);

	float VM_t[4]; // (VM) transposed
	multMatrixVector(*bezierM,V,VM_t);

	for(int i = 0; i < 3; i++) {
		coords[i] = 0;

		for(int j = 0; j < 4; j++) {
			coords[i] += VM_t[j] * UMP[i][j];
		}
	}
}

int generateBezierModel(std::vector<Vertex> * controlPoints, std::vector<int> * indices, int tessellation, char * fileName) {

	FILE * file = openFile(fileName);
	if (!file) {
		fprintf(stderr,"INVALID FILE! %s\n",fileName);
		return 2;
	}

	// each vertex has 3 components, 16 vertexes per patch
	float pX[4][4];
	float pY[4][4];
	float pZ[4][4];

	// 16 vertexes for each patch
	for(int i = 0; i < (*indices).size(); i += 16) {

		// copy 16 vertexes to P matrix
		for(int a = 0; a < 4; a++) {
			for(int b = 0; b < 4; b++) {
				// index of index vector (makes lots of sense, I know)
				int index = (*indices).at(i + a * 4 + b);
				pX[a][b] = getX((*controlPoints).at(index));
				pY[a][b] = getY((*controlPoints).at(index));
				pZ[a][b] = getZ((*controlPoints).at(index));
			}
		}

		// until tesselation + 1 to avoid ifs when last point
		for(int u = 0; u <= tessellation; u++) {

			float coordsP[3];

			// same as comment b4
			for(int v = 0; v <= tessellation; v++) {

				getBezier(u / (float) tessellation, v / (float) tessellation, (float **)pX, (float **)pY, (float **) pZ, coordsP);
				writeVertexToFile(coordsP[0],coordsP[1],coordsP[2],file);
			}
		}
	}

	// indexes
	int indicesPerPatch = (tessellation + 1) * (tessellation + 1);
	for(int i = 0; i < (*indices).size(); i += 16) {

		int currentPatch = i / 16;

		for(int u = 0; u < tessellation; u++) {
			for(int v = 0; v < tessellation; v++) {
				// A -- B
				// C -- D
				int indexA = currentPatch * indicesPerPatch + ((tessellation + 1) * u) + v;
				int indexB = indexA + 1;
				int indexC = currentPatch * indicesPerPatch + (tessellation + 1) * (u + 1) + v;
				int indexD = indexC + 1;

				writeIndexToFile(indexA,file);
				writeIndexToFile(indexC,file);
				writeIndexToFile(indexB,file);

				writeIndexToFile(indexC,file);
				writeIndexToFile(indexD,file);
				writeIndexToFile(indexB,file);

			}
		}
	}
}