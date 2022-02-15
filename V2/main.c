#include "main.h"
#include <math.h>

int main(/*int argc, char const *argv[]*/)
{
    DATATYPEMAT2D X[NBPARAM][NBDATA];//data utilisé compris entre 0 et 1
    _Bool Y[NBDATA];//état binaire analysé
    _Bool Ypredict[NBDATA];//état analysé
    DATATYPEMAT2D W[NBPARAM];//parametre deaplearning
    DATATYPEMAT2D Z[NBPARAM];//modelle neurone
    DATATYPEMAT2D A[NBPARAM];//resulat fonction d'activation
    DATATYPEMAT2D dW[NBPARAM];//gradiant
    DATATYPEMAT2D loss[NBITER];
    DATATYPEMAT2D b;

    DEBUG_S("début du programme\n");
    initRdmMat2d(&X,NBPARAM,NBDATA);
    /*X.mat[0][0]=1;
    X.mat[0][1]=2;
    X.mat[0][2]=3;
    X.mat[0][3]=4;
    X.mat[0][4]=5;
    X.mat[1][0]=4;
    X.mat[1][1]=5;
    X.mat[1][2]=6;
    X.mat[1][3]=2;
    X.mat[1][4]=3;*/
    DEBUG_C(afficherMat2d(X,"X"););
    initBolMat2d(&Y,X,1,NBDATA);
    /*Y.mat[0][0]=1;
    Y.mat[0][1]=0;
    Y.mat[0][2]=1;
    Y.mat[0][3]=0;
    Y.mat[0][4]=1;*/
    DEBUG_C(afficherMat2d(Y,"Y"););
    
    DEBUG_S("   début artificial neurone\n");
    artificial_neurone(&A,&Z,&dW ,loss,&W,&b,X,Y,LEARNINGRATE,NBITER);
    DEBUG_S("   fin artificial neurone\n");
    DEBUG_S("   début prédiction\n");
    initBolMat2d(&Ypredict,X,1,NBDATA);
    afficherMat2d(X,"X");
    afficherMat2d(W,"W");
    printf("b:%f\n",b);
    afficherMat2d(Ypredict,"Ypredict");
    predict(&A,&Z,&Ypredict,X,W,b);
    DEBUG_S("   fin prédiction\n");
    printf("score:%f\n",acurencyScore(Y,Ypredict));
    DEBUG_S("   début  liberation\n");
    libererMat2d(&W);
    libererMat2d(&X);
    libererMat2d(&Y);
    libererMat2d(&Z);
    libererMat2d(&A);
    libererMat2d(&dW);
    libererMat2d(&Ypredict);
    DEBUG_S("   fin  liberation\n");
    DEBUG_S("fin du programme\n");
    getchar();
    //system("echo ;ps -eo size,comm | grep -e 'DeepLearning$' -e 'COMMAND$'");
    return 1;
}
void genererDataset(DATATYPEMAT2D** X,_Bool *Y,_Bool*fct(DATATYPEMAT2D**,int)){
    srand((unsigned int)time(NULL));
    for(int j = 0; j < NBDATA; j++)
    {
         for(int i = 0; i < NBPARAM; i++)
        {
            X[i][j]=(DATATYPEMAT2D)rand()/((DATATYPEMAT2D)RAND_MAX/BORNEMAX);
        }
        Y[j]=(*fct)(X,j);
    }
}

_Bool modelReel(DATATYPEMAT2D** X,int i){
    if(X[1][i]>X[0][i]*2-1)return 1;
    return 0;
}
void initialisation(mat2D_t *W, DATATYPEMAT2D *b,mat2D_t X){
    initRdmMat2d(W,1,NBPARAM);
    *b=(DATATYPEMAT2D)rand()/((DATATYPEMAT2D)RAND_MAX/BORNEMAX);
}
void model(mat2D_t * A,mat2D_t*Z,mat2D_t X,mat2D_t W, DATATYPEMAT2D b){
    //Z=X*W+b
    productMat2d(Z,X,W);
    //DEBUG_C(afficherMat2d(*Z,"Z"););
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
        res+= -Y.mat[0][i]*log(A.mat[0][i]+EPSILLONE)-(1-Y.mat[0][i])*log(1-A.mat[0][i]+EPSILLONE);
    }
    return res*1/(DATATYPEMAT2D)Y.y;
}

void gradiants(mat2D_t*aux1,mat2D_t*dW,DATATYPEMAT2D*db, mat2D_t A,mat2D_t X,mat2D_t Y){
    subMat2d(aux1,A,Y);
    //DEBUG_C(afficherMat2d(aux1,"aux1"););
    //DEBUG_C(afficherMat2d(X,"X"););
    //DEBUG_C(afficherMat2d(*dW,"dw"););
    producTranspoMat2d(dW,X,*aux1);
    //DEBUG_C(afficherMat2d(*dW,"dW"););
    *db=sommeMat2D(*aux1)*(1/(DATATYPEMAT2D)Y.y);
    //printf("db:%f\n",*db);
    //printf("1/%d=%f\n",Y.y,1/(DATATYPEMAT2D)Y.y);
    productConstMat2d(dW,*dW,1/(DATATYPEMAT2D)Y.y);
    //DEBUG_C(afficherMat2d(*dW,"dW"););
}

void update(mat2D_t* aux2,mat2D_t *W,DATATYPEMAT2D *b,mat2D_t dW,DATATYPEMAT2D db,DATATYPEMAT2D learning_rate){
    productConstMat2d(aux2,dW,learning_rate);
    subMat2d(W,*W,*aux2);
    *b=*b-learning_rate*db;
}

void artificial_neurone(mat2D_t* A,mat2D_t *Z,mat2D_t*dW ,DATATYPEMAT2D *LossList,mat2D_t *W,DATATYPEMAT2D *b,mat2D_t X,mat2D_t Y,DATATYPEMAT2D learning_rate,int n_iter){
    DEBUG_S("       début initialisation\n");
    initialisation(W,b,X);
    mat2D_t aux1;
    mat2D_t aux2;
    initNullMat2d(&aux1,1,NBDATA);
    initNullMat2d(&aux2,1,NBPARAM);
    /**b=0.5;
    W->mat[0][0]=0.5;
    W->mat[0][1]=0.25;*/
    DEBUG_C(afficherMat2d(*W,"W"););
    DEBUG_C(printf("b:%f\n",*b););
    DEBUG_S("       fin initialisation\n");
    DATATYPEMAT2D db;

    for(int i=0;i<n_iter;i++){
        //DEBUG_S1("           début modèle iteration:%d\n",i+1);
        model(A,Z,X,*W,*b);
        //DEBUG_S1("           fin modèle iteration:%d\n",i+1);
        //DEBUG_S1("           début logloss iteration:%d\n",i+1);
        LossList[i]=log_loss(*A,Y);
        if(i%100==0)printf("logloss[%d]=%f\n",i,LossList[i]);
        //DEBUG_S1("           fin logloss iteration:%d\n",i+1);
        //DEBUG_S1("           début gradiant iteration:%d\n",i+1);
        gradiants(&aux1,dW,&db,*A,X,Y);
        //DEBUG_S1("           fin gradiant iteration:%d\n",i+1);
        //DEBUG_S1("           début update iteration:%d\n",i+1);
        update(&aux2,W,b,*dW,db,learning_rate);
        //DEBUG_C(afficherMat2d(*W,"W");)
        //DEBUG_C(printf("b:%f\n",*b);)
        //DEBUG_S1("           fin update iteration:%d\n",i+1);
    }
    afficherMat2d(*W,"W");
    printf("b:%f\n",*b);
    libererMat2d(&aux1);
    libererMat2d(&aux2);
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