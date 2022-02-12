#include <stdlib.h>
#include <stdio.h>
#include <assert.h>
#include "debug.h"
#include <math.h>
#define DATATYPEMAT2D float
#define MAX_X_Print 100
#define MAX_y_Print 1000
typedef struct 
{
    int x;
    int y;
    DATATYPEMAT2D **mat;
}mat2D_t;

int productMat2d(mat2D_t * matDest,mat2D_t matFrst,mat2D_t matScd);
int productConstMat2d(mat2D_t * matDest,DATATYPEMAT2D val);
void initNullMat2d(mat2D_t* mat);
//void initCstMat2d(mat2D_t* mat);
void initRdmMat2d(mat2D_t* mat,int sizex,int sizey);
void libererMat2d(mat2D_t* mat);

