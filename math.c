#include "math.h"

int productMat2d(mat2D_t * matDest,mat2D_t matFrst,mat2D_t matScd){
    //on verifi la validité des dimenssion utilisé
    if(matFrst.y!=matScd.x){
        DEBUG_S2("Dimmension %d %d incompatible pour un produit matriciel\n",matFrst.y,matScd.x);
        return 0;
    }
    //on definit les dimenssion de la matrice de destination.
    if(matDest->x!=matFrst.x&&matDest->y!=matScd.y){
        if(matDest->x!=0 &&matDest->y!=0){
            free(matDest->mat);
        }
        matDest->x=matFrst.x;
        matDest->y=matScd.y;
        matDest->mat=(DATATYPEMAT2D**) malloc( matDest->x * matDest->y * sizeof(DATATYPEMAT2D));
        assert( matDest->mat != NULL );
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
int producTranspoMat2d(mat2D_t * matDest,mat2D_t matFrst,mat2D_t matScd){
    //on verifi la validité des dimenssion utilisé
    if(matFrst.x!=matScd.x){
        DEBUG_S2("Dimmension %d %d incompatible pour un produit matriciel\n",matFrst.x,matScd.x);
        return 0;
    }
    //on definit les dimenssion de la matrice de destination.
    if(matDest->x!=matFrst.y&&matDest->y!=matScd.y){
        if(matDest->x!=0 &&matDest->y!=0){
            free(matDest->mat);
        }
        matDest->x=matFrst.y;
        matDest->y=matScd.y;
        matDest->mat=(DATATYPEMAT2D**) malloc( matDest->x * matDest->y * sizeof(DATATYPEMAT2D));
        assert( matDest->mat != NULL );
    }
    //on remplis la matrice de destination
    for(int i = 0; i < matDest->x; i++)
    {
        for(int j = 0; j < matDest->y; j++)
        {
            matDest->mat[i][j]=0;
            for(int k = 0; k < matDest->y; k++)
            {
                matDest->mat[i][j] += matFrst.mat[k][i] * matScd.mat[k][j];
            }
        }
    }

    return 1;
};
int productConstMat2d(mat2D_t * matDest,DATATYPEMAT2D val){
    for(int i = 0; i < matDest->x; i++)
    {
        for(int j = 0; j < matDest->y; j++)
        {
            matDest->mat[i][j]= matDest->mat[i][j]*val;
        }
    }
    return 1;
};

void addConstMat2d(mat2D_t *matDest, mat2D_t mat,DATATYPEMAT2D val){
    //on definit les dimenssion de la matrice de destination.
    if(matDest->x!=mat.x&&matDest->y!=mat.y){
        if(matDest->x!=0 &&matDest->y!=0){
            free(matDest->mat);
        }
        matDest->x=mat.x;
        matDest->y=mat.y;
        matDest->mat=(DATATYPEMAT2D**) malloc( matDest->x * matDest->y * sizeof(DATATYPEMAT2D));
        assert( matDest->mat != NULL );
    }
    for(int i = 0; i < mat.x; i++)
    {
        for(int j = 0; j < mat.y; j++)
        {
            matDest->mat[i][j]= mat.mat[i][j]+val;
        }
    }
};

void sigmoidMat2d(mat2D_t *matDest,mat2D_t matVal){
    if(matVal.x!=1){
        DEBUG_S("La fonction sigmoid ne s'applique que sur les dimentsion 1xN\n");
        return;
    }
    if(matDest->x!=matVal.x&&matDest->y!=matVal.y){
        if(matDest->x!=0 &&matDest->y!=0){
            free(matDest->mat);
        }
        matDest->x=matVal.x;
        matDest->y=matVal.y;
        matDest->mat=(DATATYPEMAT2D**) malloc( matDest->x * matDest->y * sizeof(DATATYPEMAT2D));
        assert( matDest->mat != NULL );
    }
    for(int i=0;i<matDest->y;i++){
        matDest->mat[1][i]=1/(1+exp(-matVal.mat[1][i]));
    }
}
void initNullMat2d(mat2D_t* mat){
    //free(mat->mat);
    mat->mat=NULL;
    mat->x=0;
    mat->y=0;
};

void initRdmMat2d(mat2D_t* mat,int sizex,int sizey){
    //on definit les dimenssion de la matrice de destination.
    if(mat->x!=sizex && mat->y!=sizey){
        if(mat->x!=0 && mat->y!=0){
            free(mat->mat);
        }
        mat->x=sizex;
        mat->y=sizey;
        mat->mat=(DATATYPEMAT2D**) malloc( sizex * sizey * sizeof(DATATYPEMAT2D));
        assert( mat->mat != NULL );
    }
    //on remplis la matrice de destination
    for(int i = 0; i < mat->x; i++)
    {
        for(int j = 0; j < mat->y; j++)
        {
            mat->mat[i][j]=(float)rand();
        }
    }
}

void libererMat2d(mat2D_t* mat){
    free(mat->mat);
    initNullMat2d(mat);
};
void afficherMat2d(mat2D_t mat){
    printf("MAT:%dx%d\n",mat.x,mat.y);
    for(int i = 0; i < mat.y; i++)
    {
        if(i<MAX_y_Print){
            printf("|");
            for(int j = 0; j < mat.x; j++)
            {
                if(j!=0)printf(";");
                if(j<MAX_X_Print){
                    printf("%2f",mat.mat[j][i]);
                }
                else{
                    if(j==MAX_X_Print)
                        printf("...");
                }
            }
            printf("|\n");
        }
        else{
            if(i==MAX_y_Print)
                printf("...\n");
        }
    }
}