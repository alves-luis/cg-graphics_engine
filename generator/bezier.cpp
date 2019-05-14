#include "bezier.h"
#include "writetofile.h"
#include <string>
#include <fstream>
#include <sstream>
#include <cmath>

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

void cross(float *a, float *b, float *res) {

	res[0] = a[1]*b[2] - a[2]*b[1];
	res[1] = a[2]*b[0] - a[0]*b[2];
	res[2] = a[0]*b[1] - a[1]*b[0];
}


void normalize(float *a) {

	float l = sqrt(a[0]*a[0] + a[1] * a[1] + a[2] * a[2]);
	a[0] = a[0]/l;
	a[1] = a[1]/l;
	a[2] = a[2]/l;
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

void getBezier(float u, float v, float ** pX, float ** pY, float ** pZ, float * coords, float * norm, float * tex) {
	float U[4] = { u*u*u, u*u, u, 1};
	float V[4] = { v*v*v, v*v, v, 1};
	float DU[4] = { 3*u*u, 2*u, 1, 0};
	float DV[4] = { 3*v*v, 2*v, 1, 0};
	float dU[3];
	float dV[3];

	// B(u,v) = U * M * P(x,y,z) * M_t * V
	// dB(u,v)/u = DU * M * P(x,y,z) * M_t * V_t
	// dB(u,v)/v = U * M * P(x,y,z) * M_t * dV
	// M_t = M (symmetric matrix)
	float MV[4];
	multMatrixVector(*bezierM,V,MV);

	// dB / u => M_t * V_t
	float uMV[4];
	multMatrixVector(*bezierM,V,uMV);

	// db / v => M_t * dV
	float vMV[4];
	multMatrixVector(*bezierM,DV,vMV);

	float PMV[3][4];
	multMatrixVector((float *)pX,MV,PMV[0]);
	multMatrixVector((float *)pY,MV,PMV[1]);
	multMatrixVector((float *)pZ,MV,PMV[2]);

	// dB / u => P * MV
	float uPMV[3][4];
	multMatrixVector((float *)pX,uMV,uPMV[0]);
	multMatrixVector((float *)pY,uMV,uPMV[1]);
	multMatrixVector((float *)pZ,uMV,uPMV[2]);

	// dB / v => P * MdV
	float vPMV[3][4];
	multMatrixVector((float *)pX,vMV,vPMV[0]);
	multMatrixVector((float *)pY,vMV,vPMV[1]);
	multMatrixVector((float *)pZ,vMV,vPMV[2]);

	float MPMV[3][4];
	multMatrixVector(*bezierM,PMV[0],MPMV[0]);
	multMatrixVector(*bezierM,PMV[1],MPMV[1]);
	multMatrixVector(*bezierM,PMV[2],MPMV[2]);

	// dB / u => M * P * M * V
	float uMPMV[3][4];
	multMatrixVector(*bezierM,uPMV[0],uMPMV[0]);
	multMatrixVector(*bezierM,uPMV[1],uMPMV[1]);
	multMatrixVector(*bezierM,uPMV[2],uMPMV[2]);

	// dB / v => M * P * M * dV
	float vMPMV[3][4];
	multMatrixVector(*bezierM,vPMV[0],vMPMV[0]);
	multMatrixVector(*bezierM,vPMV[1],vMPMV[1]);
	multMatrixVector(*bezierM,vPMV[2],vMPMV[2]);

	for(int i = 0; i < 3; i++) {
		coords[i] = 0.0f;
		dU[i] = 0.0f;
		dV[i] = 0.0f;
		for(int j = 0; j < 4; j++) {
			coords[i] += U[j] * MPMV[i][j];
			dU[i] += DU[j] * uMPMV[i][j];
			dV[i] += U[j] * vMPMV[i][j];
		}
	}

	normalize(dU);
	normalize(dV);
	cross(dV,dU,norm);
	normalize(norm);

	tex[0] = u;
	tex[1] = v;
}

int generateBezierModel(std::vector<Vertex> * controlPoints, std::vector<int> * indices, int tessellation, char * fileName) {

	FILE * file = openFile(fileName);
	if (!file) {
		fprintf(stderr,"INVALID FILE! %s\n",fileName);
		return 2;
	}

	// each vertex has 3 components, 16 floats per patch
	float pX[4][4];
	float pY[4][4];
	float pZ[4][4];

	std::vector<Vertex> normals;
	std::vector<Vertex> textures;

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
			float norm[3];
			float tex[2];

			// same as comment b4
			for(int v = 0; v <= tessellation; v++) {

				getBezier(u / (float) tessellation, v / (float) tessellation, (float **)pX, (float **)pY, (float **) pZ, coordsP, norm, tex);
				writeVertexToFile(coordsP[0],coordsP[1],coordsP[2],file);
				Vertex n = newVertex();
				setX(n,norm[0]);
				setY(n,norm[1]);
				setZ(n,norm[2]);
				normals.push_back(n);
				Vertex t = newVertex();
				setX(t,tex[0]);
				setY(t,tex[1]);
				setZ(t,0.0f);
				textures.push_back(t);
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

	for(Vertex v : normals)
		writeVertexToFile(getX(v), getY(v), getZ(v), file);
	for(Vertex v : textures)
		writeTextureToFile(getX(v),getY(v),file);
}