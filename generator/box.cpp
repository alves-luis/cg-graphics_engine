#include "box.h"
#include "writeToFile.h"
#include <stdio.h>

#define _USE_MATH_DEFINES
#include <math.h>

int indexA, indexB, indexC, indexD;

void drawXZ(float x0, float y0, float z0, float nx, float nz, int div, FILE * file) {

  for(int t = 0; t < div; t++) {
    float z = nz * t - z0;

    for(int i = 0; i < div; i++) {
      float x = nx * i - x0;

      // Face de baixo


      writeVertexToFile(x, -y0, z,file);
      writeVertexToFile(x + nx, -y0, z + nz,file);
      writeVertexToFile(x, -y0, z + nz,file);
	  
      writeVertexToFile(x + nx, -y0, z,file);
      
	    
      // Face de cima

      writeVertexToFile(x, y0, z,file);
    
      writeVertexToFile(x, y0,  z + nz,file);
    
      writeVertexToFile(x + nx, y0, z + nz,file);
    
      writeVertexToFile(x + nx,  y0, z + nz,file);
    
    }
  }
}

void drawYZ(float x0, float y0, float z0, float ny, float nz, int div, FILE * file) {

  for(int t = 0; t < div; t++) {
    float y = ny * t - y0;

    for(int i = 0; i < div; i++) {
      float z = nz*i - z0;

      // Face da esquerda
	
      writeVertexToFile(-x0, y, z,file);
    
      writeVertexToFile(-x0, y, z + nz,file);

      writeVertexToFile(-x0, y + ny, z + nz,file);
    
      writeVertexToFile(-x0,y + ny, z,file); 
    
      // Face da direita

      writeVertexToFile(x0, y, z,file);
    
      writeVertexToFile(x0, y + ny, z + nz,file);
      
      writeVertexToFile(x0, y, z + nz,file);
    
	    
      writeVertexToFile(x0, y + ny, z,file);
      
    }
  }
}

void drawXY(float x0, float y0, float z0, float nx, float ny, int div, FILE * file) {
  for (int t = 0; t < div; t++) {
    float y = ny * t - y0;

    for (int i = 0; i < div; i++) {
      float x = nx * i - x0;

      // Face de tras

      writeVertexToFile(x, y, -z0,file);
    
      writeVertexToFile(x, y + ny, -z0,file);
    
      writeVertexToFile(x + nx, y, -z0,file);
    

      writeVertexToFile(x + nx, y + ny, -z0,file);
      

      // Face da frente

      writeVertexToFile(x, y, z0,file);
    
      writeVertexToFile(x + nx, y, z0,file);
    
      writeVertexToFile(x, y + ny, z0,file);
    
      

      writeVertexToFile(x + nx, y + ny, z0,file);
      
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

  for(int t = 0; t < div; t++) {
    for(int i = 0; i < div; i++) {
    
      indexA=0;
      indexB=indexA+1;
      indexC=indexB+1;
      writeIndexToFile(indexA,file);
      writeIndexToFile(indexB,file);
      writeIndexToFile(indexC,file);
      indexD=indexC+1;
      writeIndexToFile(indexA,file);
      writeIndexToFile(indexD,file);
      writeIndexToFile(indexB,file);
      
      // Face de cima

      indexA=indexD+1;
      indexB=indexA+1;
      indexC=indexB+1;
      writeIndexToFile(indexA,file);
      writeIndexToFile(indexB,file);
      writeIndexToFile(indexC,file);
      
      indexD=indexC+1;
      writeIndexToFile(indexA,file);
      writeIndexToFile(indexD,file);
      writeIndexToFile(indexB,file);
    }
  }
  for(int t = 0; t < div; t++) {
    for(int i = 0; i < div; i++) {
    
      indexA=indexD+1;
      indexB=indexA+1;
      indexC=indexB+1;
      writeIndexToFile(indexA,file);
      writeIndexToFile(indexB,file);
      writeIndexToFile(indexC,file);
      indexD=indexC+1;
      writeIndexToFile(indexA,file);
      writeIndexToFile(indexC,file);
      writeIndexToFile(indexD,file);
      
      // Face direita

      indexA=indexD+1;
      indexB=indexA+1;
      indexC=indexB+1;
      writeIndexToFile(indexA,file);
      writeIndexToFile(indexB,file);
      writeIndexToFile(indexC,file);
      
      indexD=indexC+1;
      writeIndexToFile(indexA,file);
      writeIndexToFile(indexC,file);
      writeIndexToFile(indexD,file);
    }
  }
  for(int t = 0; t < div; t++) {
    for(int i = 0; i < div; i++) {
    
      indexA=indexD+1;
      indexB=indexA+1;
      indexC=indexB+1;
      writeIndexToFile(indexA,file);
      writeIndexToFile(indexB,file);
      writeIndexToFile(indexC,file);
      indexD=indexC+1;
      writeIndexToFile(indexB,file);
      writeIndexToFile(indexD,file);
      writeIndexToFile(indexC,file);
      
      // Face frente

      indexA=indexD+1;
      indexB=indexA+1;
      indexC=indexB+1;
      writeIndexToFile(indexA,file);
      writeIndexToFile(indexB,file);
      writeIndexToFile(indexC,file);
      
      indexD=indexC+1;
      writeIndexToFile(indexB,file);
      writeIndexToFile(indexD,file);
      writeIndexToFile(indexC,file);
    }
  }
  return 0;
}
