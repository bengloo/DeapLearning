#include "math.h"
int productMat2d(mat2D_t * matDest,mat2D_t matFrst,mat2D_t matScd){
    //on verifi la validité des dimenssion utilisé
    if(matFrst.x!=matScd.y){
        DEBUG_S4("Dimmension %dx%d %dx%d incompatible pour un produit matriciel\n",matFrst.x,matFrst.y,matScd.x,matScd.y);
        return 0;
    }
    //on definit les dimenssion de la matrice de destination.
    if(matDest->x!=matFrst.x&&matDest->y!=matScd.y){
        if(matDest->x!=0 &&matDest->y!=0){
            free(matDest->mat);
        }
        matDest->x=matScd.x;
        matDest->y=matFrst.y;
        alouerMemoire(matDest);
    }
    //DEBUG_C(afficherMat2d(*matDest,"matDest"););
    //on remplis la matrice de destination
    for(int i = 0; i < matDest->x; i++)
    {
        for(int j = 0; j < matDest->y; j++)
        {
            matDest->mat[i][j]=0;
            //printf("next\n");
            for(int k = 0; k < matScd.y; k++)
            {
                //printf("%d-%d %d-%d %d-%d\n",i,j,k,i,j,k);
                matDest->mat[i][j] += matFrst.mat[k][j] * matScd.mat[i][k];
            }
        }
    }

    return 1;
};
int producTranspoMat2d(mat2D_t * matDest,mat2D_t matFrst,mat2D_t matScd){
    //on verifi la validité des dimenssion utilisé
    if(matFrst.y!=matScd.y){
        DEBUG_S4("Dimmension %dx%d %dx%d incompatible pour un produit matriciel\n",matFrst.y,matFrst.x,matScd.x,matScd.y);
        return 0;
    }
    //on definit les dimenssion de la matrice de destination.
    if(matDest->x!=matFrst.y&&matDest->y!=matScd.y){
        if(matDest->x!=0 &&matDest->y!=0){
            free(matDest->mat);
        }
        matDest->x=matScd.x;
        matDest->y=matFrst.x;
        alouerMemoire(matDest);
    }
    //DEBUG_C(afficherMat2d(*matDest,"matDest"););
    //on remplis la matrice de destination
    for(int i = 0; i < matDest->x; i++)
    {
        for(int j = 0; j < matDest->y; j++)
        {
            matDest->mat[i][j]=0;
            //printf("next\n");
            for(int k = 0; k < matScd.y; k++)
            {
                //printf("%d-%d %d-%d %d-%d\n",i,j,k,i,j,k);
                matDest->mat[i][j] += matFrst.mat[j][k] * matScd.mat[i][k];
            }
        }
    }

    return 1;
};
int productConstMat2d(mat2D_t * matDest,mat2D_t mat,DATATYPEMAT2D val){
    if(matDest->x!=mat.x&&matDest->y!=mat.y){
        if(matDest->x!=0 &&matDest->y!=0){
            free(matDest->mat);
        }
        matDest->x=mat.x;
        matDest->y=mat.y;
        alouerMemoire(matDest);
    }
    
    for(int i = 0; i < matDest->x; i++)
    {
        for(int j = 0; j < matDest->y; j++)
        {
            matDest->mat[i][j]= mat.mat[i][j]*val;
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
        alouerMemoire(matDest);
    }
    for(int i = 0; i < mat.x; i++)
    {
        for(int j = 0; j < mat.y; j++)
        {
            matDest->mat[i][j]= mat.mat[i][j]+val;
        }
    }
};
DATATYPEMAT2D sommeMat2D(mat2D_t mat){
    DATATYPEMAT2D res=0;
    for(int i = 0; i < mat.x; i++)
    {
        for(int j = 0; j < mat.y; j++)
        {
            res+= mat.mat[i][j];
        }
    }
    return res;
};   

void subMat2d(mat2D_t *matDest, mat2D_t mat,mat2D_t mat2){
    //on definit les dimenssion de la matrice de destination.
    if(matDest->x!=mat.x&&matDest->y!=mat.y){
        if(matDest->x!=0 &&matDest->y!=0){
            free(matDest->mat);
        }
        matDest->x=mat.x;
        matDest->y=mat.y;
        alouerMemoire(matDest);
    }
    for(int i = 0; i < mat.x; i++)
    {
        for(int j = 0; j < mat.y; j++)
        {
            matDest->mat[i][j]= mat.mat[i][j]-mat2.mat[i][j];
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
        alouerMemoire(matDest);
    }
    for(int i=0;i<matDest->y;i++){
        matDest->mat[0][i]=1/(1+exp(-matVal.mat[0][i]));
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
        alouerMemoire(mat);
    }
    //on remplis la matrice de destination
    for(int i = 0; i < mat->x; i++)
    {
        for(int j = 0; j < mat->y; j++)
        {
            mat->mat[i][j]=(DATATYPEMAT2D)rand()/((DATATYPEMAT2D)RAND_MAX/BORNEMAX);
        }
    }
}
void initBolMat2d(mat2D_t *mat,mat2D_t data,int sizex,int sizey){
    //on definit les dimenssion de la matrice de destination.
    if(mat->x!=sizex && mat->y!=sizey){
        if(mat->x!=0 && mat->y!=0){
            free(mat->mat);
        }
        mat->x=sizex;
        mat->y=sizey;
        alouerMemoire(mat);
    }
    //on remplis la matrice de destination
    for(int i = 0; i < mat->x; i++)
    {
        for(int j = 0; j < mat->y; j++)
        {
            mat->mat[i][j]=data.mat[0][j]>data.mat[1][j];
        }
    }
}
void libererMat2d(mat2D_t* mat){
    free(mat->mat);
    initNullMat2d(mat);
};
void afficherMat2d(mat2D_t mat,const char * nom){
    printf("MAT %s:%dx%d\n",nom,mat.x,mat.y);
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
                        printf(". .  .|");
                }
            }
            printf("|\n");
        }
        else{
            if(i==MAX_y_Print)
                printf("|.. .   .|\n");
        }
    }
}

void alouerMemoire(mat2D_t *matDest){
    matDest->mat=(DATATYPEMAT2D**) malloc( matDest->x * sizeof(DATATYPEMAT2D*));
    assert( matDest->mat != NULL );
    for (int i = 0; i < matDest->x; i++){
        matDest->mat[i] = (DATATYPEMAT2D*)malloc(matDest->y * sizeof(DATATYPEMAT2D));
        assert( matDest->mat[i] != NULL );
    }
}