#include "math.h"

int productMat2d(mat2D_t * matDest,mat2D_t matFrst,mat2D_t matScd){
    //on verifi la validité des dimenssion utilisé
    if(matFrst.y!=matScd.x)return 0;
    //on definit les dimenssion de la matrice de destination.
    if(matDest->x!=matFrst.x&&matDest->y!=matScd.y){
        if(matDest->x!=0 &&matDest->y!=0){
            free(matDest->mat);
        }
        matDest->x=matFrst.x;
        matDest->y=matScd.y;
        matDest->mat=(float**) malloc( matDest->x * matDest->y * sizeof(float));
    }
    //on remplis la matrice de destination
    for(int i = 0; i < matDest->x; i++)
    {
        for(int j = 0; j < matDest->y; j++)
        {
            matDest->mat[i][j]=0;
            for(int k = 0; k < matDest->y; k++)
            {
                matDest->mat[i][j] += matFrst.mat[i][k] * matScd.mat[k][j];
            }
        }
    }

    return 1;
};

void initMat2d(mat2D_t* mat){
    //free(mat->mat);
    mat->mat=NULL;
    mat->x=0;
    mat->y=0;
};

void libererMat2d(mat2D_t* mat){
    free(mat->mat);
    initMat2D(mat);
};