#include "main.h"
#include <math.h>

mat2D_t X;//data utilisé
mat2D_t Y;//état analysé
mat2D_t Ypredict;//état analysé
mat2D_t W;//parametre deaplearning
mat2D_t Z;//modelle neurone
mat2D_t A;//fonction d'activation
DATATYPEMAT2D b;
int main(/*int argc, char const *argv[]*/)
{
    DEBUG_S("début du programme\n");
    initRdmMat2d(&X,NBPARAM,NBDATA);
    DEBUG_C(afficherMat2d(X,"X"););
    DATATYPEMAT2D loss[NBDATA];
    initBolMat2d(&Y,X,1,NBDATA);
    DEBUG_S("   début artificial neurone\n");
    artificial_neurone(loss,&W,&b,X,Y,LEARNINGRATE,NBITER);
    DEBUG_S("   fin artificial neurone\n");
    DEBUG_S("   début prédiction\n");
    initBolMat2d(&Ypredict,X,1,NBDATA);
    afficherMat2d(A,"A");
    afficherMat2d(Z,"Z");
    afficherMat2d(Ypredict,"Ypredict");
    afficherMat2d(X,"X");
    afficherMat2d(W,"W");
    predict(&A,&Z,&Ypredict,X,W,b);
    DEBUG_S("   fin prédiction\n");
    printf("score:%f\n",acurencyScore(Y,Ypredict));
    DEBUG_S("fin du programme\n");
    libererMat2d(&W);
    libererMat2d(&X);
    libererMat2d(&Y);
    libererMat2d(&Z);
    libererMat2d(&A);
    libererMat2d(&Ypredict);
}

void initialisation(mat2D_t *W, DATATYPEMAT2D *b,mat2D_t X){
    initRdmMat2d(W,1,NBPARAM);
    *b=(DATATYPEMAT2D)rand()/((DATATYPEMAT2D)RAND_MAX/BORNEMAX);
}
void model(mat2D_t * A,mat2D_t*Z,mat2D_t X,mat2D_t W, DATATYPEMAT2D b){
    //Z=X*W+b
    productMat2d(Z,X,W);
    addConstMat2d(Z,*Z,b);
    //DEBUG_C(afficherMat2d(*Z,"Z"););
    //A=sigmoïde(Z)
    sigmoidMat2d(A,*Z);
    //DEBUG_C(afficherMat2d(*A,"A"););
}

DATATYPEMAT2D log_loss(mat2D_t A,mat2D_t Y){
    if(A.x!=1||Y.x!=1||A.y!=Y.y){
        DEBUG_S("dimenssion incompatible log_loss\n");
        return 0;
    };

    DATATYPEMAT2D res=0;
    for(int i=0;i<Y.y;i++){
        res+= -Y.mat[0][i]*log(A.mat[0][i])-(1-Y.mat[0][i])*log(1-A.mat[0][i]);
    }
    return res*1/Y.y;
}

void gradiants(mat2D_t*dW,DATATYPEMAT2D*db, mat2D_t A,mat2D_t X,mat2D_t Y){
    mat2D_t aux1;
    initNullMat2d(&aux1);
    subMat2d(&aux1,A,Y);
    //DEBUG_C(afficherMat2d(aux1,"aux1"););
    producTranspoMat2d(dW,X,aux1);
    //DEBUG_C(afficherMat2d(*dW,"dW"););
    *db=sommeMat2D(aux1)*1/Y.y;
    productConstMat2d(dW,*dW,1/Y.y);
    libererMat2d(&aux1);
    
}

void update(mat2D_t *W,DATATYPEMAT2D *b,mat2D_t dW,DATATYPEMAT2D db,DATATYPEMAT2D learning_rate){
    mat2D_t aux1;
    initNullMat2d(&aux1);
    productConstMat2d(&aux1,dW,learning_rate);
    subMat2d(W,*W,aux1);
    *b=*b-learning_rate*db;
}

void artificial_neurone(DATATYPEMAT2D *LossList,mat2D_t *W,DATATYPEMAT2D *b,mat2D_t X,mat2D_t Y,DATATYPEMAT2D learning_rate,int n_iter){
    DEBUG_S("       début initialisation\n");
    initialisation(W,b,X);
    DEBUG_C(afficherMat2d(*W,"W"););
    DEBUG_C(printf("b:%f\n",*b););
    DEBUG_S("       fin initialisation\n");
    mat2D_t A;
    initNullMat2d(&A);
    mat2D_t dW;
    initNullMat2d(&dW);
    mat2D_t Z;
    initNullMat2d(&Z);
    DATATYPEMAT2D db;

    for(int i=0;i<n_iter;i++){
        //DEBUG_S1("           début modèle iteration:%d\n",i+1);
        model(&A,&Z,X,*W,*b);
        //DEBUG_S1("           fin modèle iteration:%d\n",i+1);
        //DEBUG_S1("           début logloss iteration:%d\n",i+1);
        LossList[i]=log_loss(A,Y);
        //printf("logloss[%d]=%f\n",i,LossList[i]);
        //DEBUG_S1("           fin logloss iteration:%d\n",i+1);
        //DEBUG_S1("           début gradiant iteration:%d\n",i+1);
        gradiants(&dW,&db,A,X,Y);
        //DEBUG_S1("           fin gradiant iteration:%d\n",i+1);
        //DEBUG_S1("           début update iteration:%d\n",i+1);
        update(W,b,dW,db,learning_rate);
        //DEBUG_C(afficherMat2d(*W,"W");)
        //DEBUG_C(printf("b:%f\n",*b);)
        //DEBUG_S1("           fin update iteration:%d\n",i+1);
    }
    afficherMat2d(*W,"W");
    printf("b:%f\n",*b);
    DEBUG_S("         début libération matrice\n");
    libererMat2d(&A);
    libererMat2d(&dW);
    libererMat2d(&Z);
    DEBUG_S("         fin libération matrice\n");
}
void predict(mat2D_t *A,mat2D_t *Z,mat2D_t *Y,mat2D_t X,mat2D_t W,DATATYPEMAT2D b){
    //printf("test1");
    model(A,Z,X,W,b);
    //printf("test2");
    for(int i=0;i<A->y;i++){
        //printf("test3");
        Y->mat[0][i]=A->mat[0][i]>0.5;
    }
};

DATATYPEMAT2D acurencyScore(mat2D_t Y,mat2D_t Ypredict){
    DATATYPEMAT2D res=0;
    for(int i=0;i<Y.x;i++){
        for(int j=0;j<Y.y;j++){
            res+=(Y.mat[i][j]==Ypredict.mat[i][j]);
        }   
    }
    return res/(Y.x*Y.y);
};