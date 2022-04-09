#include "neurone.h"
//int i;int j;

void alouerNeurone(Neurone_T *ptrN,int nbE){
    ptrN->W = malloc(sizeof(DATATYPE)*nbE);
    if(ptrN->W==NULL)exit(0);
    for(int j = 0; j < nbE; j++)
        ptrN->W[j]=(DATATYPE)rand()/((DATATYPE)RAND_MAX/BORNEMAX);
    ptrN->b=(DATATYPE)rand()/((DATATYPE)RAND_MAX/BORNEMAX);
}
void alouerCouche(Couche_T *ptrC,int couche){
    ptrC[couche].Neurones= malloc(sizeof(DATATYPE)*nbEntree[couche]);
    if(ptrC[couche].Neurones==NULL)exit(0);
    for (int i = 0; i < nbEntree[couche+1]; i++)
    {
        alouerNeurone(&(ptrC->Neurones[i]),nbEntree[couche]); 
    }
}


void libererNeurone(Neurone_T *ptrN){
        free(ptrN);
}
void libererCouche(Couche_T *ptrC,int nbN){
    for (int i = 0; i < nbN; i++)
    {   
        libererNeurone(&(ptrC->Neurones[i]));
        free(&(ptrC[i]));
    }
}

void printParam(Couche_T *couche){
    for (size_t i = 0; i < NBCOUCHE; i++)//on parcour les couches du modéle
    {
        printf("couche:%ld ",i);
        for (size_t j = 0; j < nbEntree[i+1]; j++)//on parcour les neurone de chaque couche
        {
            printf("neurone:%ld b:%f w:{",j,couche[i].Neurones[j].b);
            for (size_t k = 0; i < nbEntree[i]; i++)//on parcour les parametre d'entré de chque neurone
            {
                printf("%f,",couche[i].Neurones[j].W[k]);
            }
            printf("}\n");
        }
    }
}
void initialisation(Couche_T *couche){
    for (int i = 0; i < NBCOUCHE; i++)
    {
       alouerCouche(&(couche[i]),i);
    }
}
void model(DATATYPE * A,const X_t X,const DATATYPE* W,const DATATYPE b){
    //Z=X*W+b
    //A=sigmoid(Z);
    for(int j = 0; j < NBDATA; j++)
    {
        A[j]=b;
        for(int k = 0; k < NBPARAM; k++) A[j] += X[k][j] * W[k];
        A[j]=1/(1+exp(-A[j]));
    }
}

DATATYPE log_loss(const DATATYPE* A,const _Bool* Y){
    DATATYPE res=0;
    for(int i=0;i<NBDATA;i++){
        res+= -Y[i]*log(A[i]+EPSILLONE)-(1-Y[i])*log(1-A[i]+EPSILLONE);
    }
    return res/(DATATYPE)NBDATA;
}

void gradiants(DATATYPE*dW,DATATYPE*db,const DATATYPE* A,const X_t X,const _Bool* Y){
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

void update(DATATYPE *W,DATATYPE *b,const DATATYPE* dW,const DATATYPE db,const DATATYPE learning_rate){
    for(int i=0;i<NBPARAM;i++){
        W[i]=W[i]-dW[i]*learning_rate;
    }
    *b=*b-learning_rate*db;
}

void artificial_neurone(DATATYPE *LossList,Couche_T*couche,const X_t X,const _Bool* Y,const DATATYPE learning_rate,const int n_iter){
    DATATYPE Z[NBDATA];//modelle neurone
    DATATYPE A[NBDATA];//resulat fonction d'activation
    DATATYPE dW[NBPARAM];//gardiant
    DATATYPE db;

    DEBUG_S("       début initialisation\n");
    initialisation(couche);
    printParam(couche);
    DEBUG_S("       fin initialisation\n");
    /*for(int i=0;i<n_iter;i++){
        //DEBUG_S1("           début modèle iteration:%d\n",i+1);
        model(A,X,W,*b);
        //DEBUG_S1("           fin modèle iteration:%d\n",i+1);
        //DEBUG_S1("           début logloss iteration:%d\n",i+1);
        //LossList[i]=log_loss(A,Y);
        if(i%(n_iter/100)==0)printf("logloss[%d]=%f\n",i,log_loss(A,Y));
        //DEBUG_S1("           fin logloss iteration:%d\n",i+1);
        //DEBUG_S1("           début gradiant iteration:%d\n",i+1);
        gradiants(dW,&db,A,X,Y);
        //DEBUG_S1("           fin gradiant iteration:%d\n",i+1);
        //DEBUG_S1("           début update iteration:%d\n",i+1);
        update(W,b,dW,db,learning_rate);
        //DEBUG_C(afficherMat2d(*W,"W");)
        //DEBUG_C(printf("b:%f\n",*b);)
        //DEBUG_S1("           fin update iteration:%d\n",i+1);
    }*/
}
void predict(_Bool *Y,const X_t X,const DATATYPE* W,const DATATYPE b){
    DATATYPE A[NBDATA];//resulat fonction d'activation
    //printf("test1");
    model(A,X,W,b);
    //printf("test2");
    for(int i=0;i<NBDATA;i++){
        //printf("test3");
        Y[i]=A[i]>0.5;
    }
};

DATATYPE acurencyScore(const _Bool* Y,const _Bool* Ypredict){
    DATATYPE res=0;
    for(int j=0;j<NBDATA;j++){
        res+=(Y[j]==Ypredict[j]);
    }   
    return res/(DATATYPE)NBDATA;
};