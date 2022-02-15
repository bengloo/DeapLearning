#include "math.h"
void productMat2d(mat2D_t * matDest,mat2D_t matFrst,mat2D_t matScd){
    //on verifi la validité des dimenssion utilisé
    if(matFrst.x!=matScd.y){
        DEBUG_S4("Dimmension %dx%d %dx%d incompatible pour un produit matriciel\n",matFrst.x,matFrst.y,matScd.x,matScd.y);
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
};
void producTranspoMat2d(mat2D_t * matDest,mat2D_t matFrst,mat2D_t matScd){
    //on verifi la validité des dimenssion utilisé
    if(matFrst.y!=matScd.y){
        DEBUG_S4("Dimmension %dx%d %dx%d incompatible pour un produit matriciel\n",matFrst.x,matFrst.y,matScd.x,matScd.y);
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
};
void productConstMat2d(mat2D_t * matDest,mat2D_t mat,DATATYPEMAT2D val){
    if(matDest->mat==NULL||mat.mat==NULL)DEBUG_S("Dimenssion matrice non definit prductConstMat2D");
    for(int i = 0; i < matDest->x; i++)
    {
        for(int j = 0; j < matDest->y; j++)
        {
            matDest->mat[i][j]= mat.mat[i][j]*val;
        }
    }
};

void addConstMat2d(mat2D_t *matDest, mat2D_t mat,DATATYPEMAT2D val){
    if(matDest->mat==NULL||mat.mat==NULL)DEBUG_S("Dimenssion matrice non definit addConstMat2d");
    //on definit les dimenssion de la matrice de destination.
    if(matDest->x!=mat.x&&matDest->y!=mat.y){
        if(matDest->x!=0 &&matDest->y!=0){
            libererMat2d(matDest);
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
    if(mat.mat==NULL)DEBUG_S("Dimenssion matrice non definit sommeMat2D");
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
    if(mat.mat==NULL)DEBUG_S("Dimenssion matrice non definit subMat2D");
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
    }
    for(int i=0;i<matDest->y;i++){
        matDest->mat[0][i]=1/(1+exp(-matVal.mat[0][i]));
    }
}

void initRdmMat2d(mat2D_t* mat,int sizex,int sizey){
    //on definit les dimenssion de la matrice de destination.
    mat->x=sizex;
    mat->y=sizey;
    alouerMemoire(mat);
    //on remplis la matrice de destination
    srand((unsigned int)time(NULL));
    for(int i = 0; i < mat->x; i++)
    {
        for(int j = 0; j < mat->y; j++)
        {
            mat->mat[i][j]=(DATATYPEMAT2D)rand()/((DATATYPEMAT2D)RAND_MAX/BORNEMAX);
        }
    }
}
void initNullMat2d(mat2D_t* mat,int sizex,int sizey){
    /*if(mat->x!=0 && mat->y!=0&&mat->mat!=NULL){
        libererMat2d(mat);
    }*/
    mat->x=sizex;
    mat->y=sizey;
    alouerMemoire(mat);
    
    //on remplis la matrice de destination
    for(int i = 0; i < sizex; i++)
    {
        for(int j = 0; j < sizey; j++)
        {
            mat->mat[i][j]=0;
        }
    }
}
void initBolMat2d(mat2D_t *mat,mat2D_t data,int sizex,int sizey){
    //on definit les dimenssion de la matrice de destination.
    if(mat->x!=sizex || mat->y!=sizey){
        if(mat->mat!=NULL)
            libererMat2d(mat);
        
        mat->x=sizex;
        mat->y=sizey;
        alouerMemoire(mat);
    }
    //on remplis la matrice de destination
    for(int i = 0; i < mat->x; i++)
    {
        for(int j = 0; j < mat->y; j++)
        {
            mat->mat[i][j]=data.mat[0][j]>data.mat[1][j]*2-0.2;
        }
    }
}
void libererMat2d(mat2D_t* mat){
    if((mat->x!=0||mat->y!=0)&&mat->mat!=NULL){
        for(int i=0;i<mat->x;i++){
            free(mat->mat[i]);
        }
        free(mat->mat);
        mat->x=0;
        mat->y=0;
        mat->mat=NULL;
    }
};
void afficherMat2d(mat2D_t mat,const char * nom){
    printf("MAT %s:%dx%d\n",nom,mat.x,mat.y);
    for(int i = 0;i<mat.y; i++)
    {
        if(i<MAX_y_Print){
            printf("|");
            for(int j = 0; j < mat.x; j++)
            {
                if(j!=0)printf(";");
                if(j<MAX_X_Print){
                    printf("%f",mat.mat[j][i]);
                }
                else{
                    if(j==MAX_X_Print-1)
                        printf(". .  .|");
                }
            }
            printf("|\n");
        }
        else{
            if(i==MAX_y_Print)printf("|.. .   .|\n");
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