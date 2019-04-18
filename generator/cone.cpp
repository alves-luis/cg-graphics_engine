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


    if (slices < 0 || stacks < 0)
        return 1;

    float angle=(float) 2*M_PI/slices;
    float division=height/stacks;
    float baseY = height/2;

    writeToFile(0.0f, 0.0f - baseY, 0.0f, file);

    for(int i=0; i<= slices;i++){

        for (int j = 0; j < stacks +1; j++) {

            float div = (float) j / stacks;
            float radius = (float) (1.0 - (div)) * botRad;

            float x = radius * cos(i * angle);
            float y = j * division - baseY;
            float z = radius * sin(i * angle);

            writeToFile(x, y, z, file);

        }
    }

    int b1,b2,b3,iA,iB,iC,iD,l;
    int k=stacks+1;
    for(int i=0;i<k;i++){
        //para ligar última slice à primeira
        if (i == slices)
            l = 0;
        else
            l = i;

        b1=0;
        b2=k*l+1;
        b3=k*(l+1)+1;
        writeIndexToFile(b1,file);
        writeIndexToFile(b2,file);
        writeIndexToFile(b3,file);

        for(int j=1;j<stacks+1;j++){

            iA= k*l+j;
            iB= k*l+j+1;
            iC= k*(l+1)+j;
            iD= k*(l+1)+j+1;

            writeIndexToFile(iA,file);
            writeIndexToFile(iB,file);
            writeIndexToFile(iC,file);

            writeIndexToFile(iC,file);
            writeIndexToFile(iB,file);
            writeIndexToFile(iD,file);
        }
    }

    return 0;
}