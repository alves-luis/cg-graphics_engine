#include "cone.h"
#include "writetofile.h"
#include "vertex.h"

#define _USE_MATH_DEFINES
#include <math.h>
#include <stdio.h>
#include <vector>



/**
 * Esta função, dado um raio, uma altura, um número de slices e de stacks e
 * um nome de um ficheiro, gera todos os vértices necessários para a
 * formação de triângulos, que juntos formarão um cone. Os vértices gerados
 * serão guardados num ficheiro .3d
 * @param botRad Raio da base do cone;
 * @param slices Número de slices (cortes verticais) do cone;
 * @param stacks Número de stacks (cortes horizontais) do cone;
 * @param fname Nome do ficheiro onde serão guardados os vértices gerados;
 * O número de triângulos que serão usados para a
 * base do cone é proporcional ao número de slices fornecidas, enquanto
 * que o número de triângulos necessários para a superfície lateral é proporcional
 * ao número de stacks e slices
 */
int createCone(float botRad, float height, int slices, int stacks, char * fname){
    FILE * file = openFile(fname);


    if (slices < 0 || stacks < 0)
        return 1;

    float angle=(float) 2*M_PI/slices;
    float division=height/stacks;
    float baseY = height/2;

    std::vector<Vertex> normals;
    std::vector<Vertex> texture;

    for(int i = 0; i <= slices; i++) {
    	// center
		writeVertexToFile(0,- baseY, 0, file);

		Vertex norm = newVertex();
		setX(norm,0.0f);
		setY(norm,-1.0f);
		setZ(norm,0.0f);
		normals.push_back(norm);

		Vertex t = newVertex();
		setX(t,(float) i / slices);
		setY(t,1);
		texture.push_back(t);

		// around the center
		float x = botRad * cos( i * angle);
		float y = -baseY;
		float z = botRad * sin( i * angle);


		writeVertexToFile(x,y,z,file);

    	Vertex n = newVertex();
    	setX(n,0.0f);
    	setY(n,-1.0f);
    	setZ(n,0.0f);
    	normals.push_back(n);

    	Vertex tex = newVertex();
    	setX(tex,(float) i / slices);
    	setY(tex,0.0f);
    	texture.push_back(tex);
    }

    float normY = static_cast<float>(sin(M_PI - atan(height / botRad)));

    for(int i=0; i<= slices;i++){

        for (int j = 0; j < stacks +1; j++) {

            float div = (float) j / stacks;
            float radius = (float) (1.0 - (div)) * botRad;

            float x = radius * cos(i * angle);
            float y = j * division - baseY;
            float z = radius * sin(i * angle);

			writeToFile(x, y, z, file);

            Vertex norm = newVertex();
			setX(norm,cos(i * angle));
			setY(norm, normY);
			setZ(norm, sin(i * angle));
            normals.push_back(norm);

            Vertex t = newVertex();
            setX(t,(float) i / slices);
			setY(t,(float) j / stacks);
			texture.push_back(t);
        }
    }

	int b1,b2,b3;
	for(int i=0;i < slices;i++) {
		b1 = i * 2;
		b2 = i * 2 + 3;
		b3 = i * 2 + 1;
		writeIndexToFile(b1, file);
		writeIndexToFile(b2, file);
		writeIndexToFile(b3, file);
	}
    int iA,iB,iC,iD;
    for(int i=0;i < slices;i++){
        for(int j=0;j<stacks;j++){

            iA= (slices + 1)* 2 + i * (slices + 1) + j;
            iB= (slices + 1)* 2 + i * (slices + 1) + j + 1;
            iC= (slices + 1)* 2 + (i + 1) * (slices + 1) + j;
            iD= (slices + 1)* 2 + (i + 1) * (slices + 1) + j + 1;

            writeIndexToFile(iA,file);
            writeIndexToFile(iB,file);
            writeIndexToFile(iC,file);

            writeIndexToFile(iC,file);
            writeIndexToFile(iB,file);
            writeIndexToFile(iD,file);
        }
    }
    for(Vertex v : normals)
    	writeVertexToFile(getX(v),getY(v),getZ(v),file);
    for(Vertex v : texture)
    	writeTextureToFile(getX(v),getY(v),file);

    return 0;
}