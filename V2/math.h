#include <stdlib.h>
#include <stdio.h>
#include <assert.h>
#include "debug.h"
#include <math.h>
#include <float.h>
#define DATATYPEMAT2D float
#define EPSILLONE FLT_MIN
#define BORNEMAX 10
#define MAX_X_Print 2
#define MAX_y_Print 5
typedef struct 
{
    int x;
    int y;
    DATATYPEMAT2D **mat;
}mat2D_t;

void productMat2d(mat2D_t * matDest,mat2D_t matFrst,mat2D_t matScd);
void producTranspoMat2d(mat2D_t * matDest,mat2D_t matFrst,mat2D_t matScd);
void productConstMat2d(mat2D_t * matDest,mat2D_t mat,DATATYPEMAT2D val);
void addConstMat2d(mat2D_t *matDest, mat2D_t mat,DATATYPEMAT2D val);
DATATYPEMAT2D sommeMat2D(mat2D_t mat);
void subMat2d(mat2D_t *matDest, mat2D_t mat,mat2D_t mat2);
void sigmoidMat2d(mat2D_t *matDest,mat2D_t matVal);
void initNullMat2d(mat2D_t* mat,int sizex,int sizey);
void initRdmMat2d(mat2D_t* mat,int sizex,int sizey);
void initBolMat2d(mat2D_t* mat,mat2D_t data,int sizex,int sizey);
void afficherMat2d(mat2D_t mat,const char*nom);
void libererMat2d(mat2D_t* mat);
void alouerMemoire(mat2D_t *matDest);

