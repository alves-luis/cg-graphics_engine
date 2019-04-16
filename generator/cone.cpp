#include "cone.h"
#include "writetofile.h"
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

    std::vector<int> indexes;


    if (slices < 0 || stacks < 0)
        return 1;

    float angle=(float) 2*M_PI/slices;
    float division=height/stacks;
    float baseY = height/2;

    writeToFile(0.0f, 0.0f - baseY, 0.0f, file);

    for(int i=0; i<= slices;i++){

        for (int j = 0; j < stacks +1; j++) {

            //radius for j stacks
            float div = (float) j / stacks;
            float radiusD = (float) (1.0 - (div)) * botRad;



            //d -> level j
            // ux1
            //  |
            //  |
            // dx1


            float dx1 = radiusD * cos(i * angle);
            float dz1 = radiusD * sin(i * angle);
            float dy = j * division - baseY;


            // one triangle [dx1,ux1,dx2]
            writeToFile(dx1, dy, dz1, file);

        }
    }

    int iA,iB,iC,iD,l;
    int k=stacks+1;
    for(int i=0;i<k;i++){
        if (i == slices)
            l = 0;
        else
            l = i;
        indexes.push_back(0);
        indexes.push_back(k*l+1);
        indexes.push_back(k*(l+1)+1);

        for(int j=1;j<stacks+1;j++){

            iA= k*l+j;
            iB= k*l+j+1;
            iC= k*(l+1)+j;
            iD= k*(l+1)+j+1;

            indexes.push_back(iA);
            indexes.push_back(iB);
            indexes.push_back(iC);

            indexes.push_back(iC);
            indexes.push_back(iB);
            indexes.push_back(iD);

        }

    }

    for(int i : indexes) {
        writeIndexToFile(i, file);
    }
    return 0;
}