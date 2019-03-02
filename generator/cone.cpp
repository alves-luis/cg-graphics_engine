#include "cone.h"
#include "writetofile.h"
#define _USE_MATH_DEFINES
#include <math.h>
#include <stdio.h>

int createCone(float botRad, float height, int slices, int stacks, char * fname){

    float angle=(float) 2*M_PI/slices;
    float division=height/stacks;


    for(int i=0; i<slices; i++) {

        float bx1 = botRad * cos(i * angle);
        float bz1 = botRad * sin(i * angle);

        float bx2 = botRad * cos((i + 1) * angle);
        float bz2 = botRad * sin((i + 1) * angle);

        // base triangle
        writeToFile(0.0f, 0.0f, 0.0f, fname);
        writeToFile(bx1, 0.0f, bz1, fname);
        writeToFile(bx2, 0.0f, bz2, fname);


        for (int j = 0; j < stacks; j++) {

            //radius for j stacks
            float div = (float) j / stacks;
            float radiusD = (float) (1.0 - (div)) * botRad;

            //radius for j+1 stacks
            div = (float) (j + 1) / stacks;
            float radiusU = (float) (1.0 - (div)) * botRad;

            //d -> level j
            //u -> level j+1

            // coordinates of the vertex that is on the right and bottom
            float dx1 = radiusD * cos(i * angle);
            float dz1 = radiusD * sin(i * angle);

            // coordinates of the vertex that is on the left and bottom
            float dx2 = radiusD * cos((i + 1) * angle);
            float dz2 = radiusD * sin((i + 1) * angle);

            // coordinates of the vertex that is on the right and up
            float ux1 = radiusU * cos(i * angle);
            float uz1 = radiusU * sin(i * angle);

            // coordinates of the vertex that is on the left and up
            float ux2 = radiusU * cos((i + 1) * angle);
            float uz2 = radiusU * sin((i + 1) * angle);

            float dy = j * division;
            float uy = (j + 1) * division;

            // one triangle
            writeToFile(dx1, dy, dz1, fname);
            writeToFile(ux1, uy, uz1, fname);
            writeToFile(dx2, dy, dz2, fname);

            //another triangle
            writeToFile(dx2, dy, dz2, fname);
            writeToFile(ux1, uy, uz1, fname);
            writeToFile(ux2, uy, uz2, fname);

        }


    }


}