#include <stdio.h>
#include "writetofile.h"



void normalize(float * a) {

	float l = sqrt(a[0]*a[0] + a[1] * a[1] + a[2] * a[2]);
	a[0] = a[0]/l;
	a[1] = a[1]/l;
	a[2] = a[2]/l;
}

void cross(float *a, float *b, float *res) {

	res[0] = a[1]*b[2] - a[2]*b[1];
	res[1] = a[2]*b[0] - a[0]*b[2];
	res[2] = a[0]*b[1] - a[1]*b[0];

}

void writeNormals(vector<float> a,vector<int> b, FILE * fName){

    float * p1;
    float * p2;
    float * p3;

    float v1[3];
    float v2[3];
    float res[3];

    for (auto i = b.begin(); i != b.end(); ++i){

        p1[0] = a[b[i++]];
        p1[1] = a[b[i++]];
        p1[2] = a[b[i++]];

        p2[0] = a[b[i++]];
        p2[1] = a[b[i++]];
        p2[2] = a[b[i++]];

        p3[0] = a[b[i++]];
        p3[1] = a[b[i++]];
        p3[2] = a[b[i++]];

        v1 = {p2[0] - p1[0], p2[1] - p1[1], p2[2] - p1[2]};
        v2 = {p3[0] - p1[0], p3[1] - p1[1], p3[2] - p1[2]};

        cross(v1,v2, res);
        normalize(res);
        writeNormalToFile(res[0], res[1], res[2], fName);
    }
        
}

