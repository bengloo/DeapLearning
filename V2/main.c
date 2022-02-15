#include "main.h"

int main(/*int argc, char const *argv[]*/)
{
    X_t X;//data utilisé
    _Bool Y[NBDATA];//état analysé
    _Bool Ypredict[NBDATA];//état analysé
    DATATYPE W[NBPARAM];//parametre deaplearning
    DATATYPE loss[NBITER];
    DATATYPE b;

    DEBUG_S("début du programme\n");
        genererDataset(X,Y);
        DEBUG_S("   début artificial neurone\n");
            artificial_neurone(loss,W,b,X,Y,LEARNINGRATE,NBITER);
        DEBUG_S("   fin artificial neurone\n");
        DEBUG_S("   début prédiction\n");
            predict(&A,&Z,&Ypredict,X,W,b);
        DEBUG_S("   fin prédiction\n");
        printf("score:%f\n",acurencyScore(Y,Ypredict));
    DEBUG_S("fin du programme\n");
    //system("echo ;ps -eo size,comm | grep -e 'DeepLearning$' -e 'COMMAND$'");
    return 1;
}
void genererDataset(X_t X,DATATYPE*Y){
    for(int i=0;i<NBDATA;i++){
        for(int j=0;j<NBPARAM;j++){
            X[j][i]=(DATATYPE)rand()/((DATATYPE)RAND_MAX/BORNEMAX);
        }
        Y[i]=(X[1][i]>X[0][i]*2-1);
    }
};

void initialisation(DATATYPE *W, DATATYPE *b){
    for(int j = 0; j < NBPARAM; j++) W[j]=(DATATYPE)rand()/((DATATYPE)RAND_MAX/BORNEMAX);
    *b=(DATATYPE)rand()/((DATATYPE)RAND_MAX/BORNEMAX);
}
void model(DATATYPE * A,X_t X,DATATYPE* W, DATATYPE b){
    //Z=X*W+b
    //A=sigmoid(Z);
    for(int j = 0; j < NBDATA; j++)
    {
        A[j]=b;
        for(int k = 0; k < NBPARAM; k++) A[j] += X[k][j] * W[k];
        A[j]=1/(1+exp(-A[j]));
    }
}

DATATYPE log_loss(DATATYPE* A,DATATYPE* Y){
    DATATYPE res=0;
    for(int i=0;i<NBDATA;i++){
        res+= -Y[i]*log(A[i]+EPSILLONE)-(1-Y[i])*log(1-A[i]+EPSILLONE);
    }
    return res/(DATATYPE)NBDATA;
}

void gradiants(DATATYPE*dW,DATATYPE*db, DATATYPE* A,X_t X,_Bool* Y){
    for(int j = 0; j < NBPARAM; j++)
    {
        dW[j]=0;
        for(int k = 0; k < NBDATA; k++) dW[j] += X[j][k]*(A[k]-Y[k]);
        dW[j]=dW[j]/(DATATYPE)NBDATA;
    }
    *db=0;
    for(int k = 0; k < NBDATA; k++) *db+=A[k]-Y[k];
    *db=*db/(DATATYPE)NBDATA;
}

void update(mat2D_t* aux2,mat2D_t *W,DATATYPEMAT2D *b,mat2D_t dW,DATATYPEMAT2D db,DATATYPEMAT2D learning_rate){
    productConstMat2d(aux2,dW,learning_rate);
    subMat2d(W,*W,*aux2);
    *b=*b-learning_rate*db;
}

void artificial_neurone(DATATYPE *LossList,DATATYPE*W,DATATYPE *b,X_t X,_Bool* Y,DATATYPE learning_rate,int n_iter){
    DATATYPE Z[NBDATA];//modelle neurone
    DATATYPE A[NBDATA];//resulat fonction d'activation
    DATATYPE dW[NBPARAM];//gardiant
    DATATYPE db;

    DEBUG_S("       début initialisation\n");
    initialisation(W,b);
    DEBUG_S("       fin initialisation\n");
    for(int i=0;i<n_iter;i++){
        //DEBUG_S1("           début modèle iteration:%d\n",i+1);
        model(A,X,W,*b);
        //DEBUG_S1("           fin modèle iteration:%d\n",i+1);
        //DEBUG_S1("           début logloss iteration:%d\n",i+1);
        LossList[i]=log_loss(A,Y);
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