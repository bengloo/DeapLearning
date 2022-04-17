#include "neurone.h"
//int i;int j;
int nbEntree[NBCOUCHE+1]=NBENTREE; //nombre d'entré par couche et donc nombre de neurone de la couche précedente

void alouerNeurone(W_T *ptrN,int nbE){
    printf("on aloue une neurone (%p)de %d entree\n",ptrN,nbE);
    ptrN->W = (DATATYPE *)malloc(sizeof(DATATYPE)*nbE);
    if(ptrN->W==NULL)exit(0);
    ptrN->dW = (DATATYPE *)malloc(sizeof(DATATYPE)*nbE);
    if(ptrN->dW==NULL)exit(0);
    for(int j = 0; j < nbE; j++)ptrN->W[j]=(DATATYPE)rand()/((DATATYPE)RAND_MAX/BORNEMAX);
    ptrN->b=(DATATYPE)rand()/((DATATYPE)RAND_MAX/BORNEMAX);
}
void alouerCouche(layerW_T *ptrC,int couche){
    ptrC->W= (W_T *) malloc(sizeof(W_T)*nbEntree[couche+1]);
    if(ptrC->W==NULL)exit(0);
    for (int i = 0; i < nbEntree[couche+1]; i++)alouerNeurone(&(ptrC->W[i]),nbEntree[couche]); 
}


void initialisation(layerW_T *Wcouche,layerA_T*Acouche){
    for (int i = 0; i < NBCOUCHE; i++){
        alouerCouche(&(Wcouche[i]),i);
        Acouche->pfActivation= FCTACTIVATION;
    }
}
void printParam(layerW_T *couche){
    for (size_t i = 0; i < NBCOUCHE; i++)//on parcour les couches du modéle
    {
        printf("couche:%ld avec %d neurones\n",i+1,nbEntree[i+1]);
        for (size_t j = 0; j < nbEntree[i+1]; j++)//on parcour les neurone de chaque couche
        {
            printf("\tneurone:%ld avec %d entrees \n",j+1,nbEntree[i]);
            printf("\t\tb:%f w:{",couche[i].W[j].b);
            for (size_t k = 0; k < nbEntree[i]; k++)//on parcour les parametre d'entrée de chaque neurone
                printf("%f,",couche[i].W[j].W[k]);
            printf("}\n");
}   }   }  

void libererNeurone(W_T *ptrN){
        //printf("neurone %p liberer\n",ptrN);
        free(ptrN->W);
        free(ptrN->dW);
}
void libererCouche(layerW_T *ptrC,int nbN){
    for (int i = 0; i < nbN; i++)
        libererNeurone(&(ptrC->W[i]));
    free(ptrC->W);
}
void forward_propagation(const X_t X,layerW_T *Wcouche,layerA_T *Acouche){
    //Z=X*W+b
    //A=sigmoid(Z);
    //pour la couche 0 on prend le dataset en entrée
    for (size_t l = 0; l < nbEntree[1]; l++)
    {    
        for(size_t j = 0; j < NBDATA; j++)
        {
            Acouche[0].A[l].A[j]=Wcouche[0].W[l].b;
            for(size_t k = 0; k < NBPARAM; k++) Acouche[0].A[l].A[j] += X[k][j] * Wcouche[0].W[l].W[k];
            Acouche[0].A[l].A[j]=1/(1+exp(-Acouche[0].A[l].A[j]));
        }
    }
    //pour la couche > on prend l'activation de la couche precedente en entrée   
    for (size_t i = 1; i < NBCOUCHE; i++)//on vas de la cauche la plus basse vers la couche la plus haute
    {    
        for (size_t l = 0; l < nbEntree[i+1]; l++)
        {    
            for(size_t j = 0; j < NBDATA; j++)
            {
                Acouche[i].A[l].A[j]=Wcouche[i].W[l].b;
                for(size_t k = 0; k < nbEntree[i]; k++) Acouche[i].A[l].A[j] += Acouche[i-1].A[k].A[j] * Wcouche[i].W[l].W[k];
                Acouche[i].A[l].A[j]=1/(1+exp(-Acouche[i].A[l].A[j]));
            }
        }
    }
}

DATATYPE log_loss(const DATATYPE* A,const _Bool* Y){
    DATATYPE res=0;
    for(int i=0;i<NBDATA;i++){
        res+= -Y[i]*log(A[i]+EPSILLONE)-(1-Y[i])*log(1-A[i]+EPSILLONE);
    }
    return res/(DATATYPE)NBDATA;
}

void back_propagation(layerW_T* couche,const X_t X,const _Bool* Y){
    for (size_t i = NBCOUCHE-1; i > 0; i--)
    {
        for (size_t l = 0; l < nbEntree[i+1]; l++)
        { 
            for(size_t j = 0; j < nbEntree[i]; j++)
            {
                couche[i].W[l].dW[j]=0;
                for(int k = 0; k < NBDATA; k++) 
                    couche[i].W[l].dW[j] += X[j][k]*(couche[i].W[l].A[k]-Y[k]);
                couche[i].W[l].dW[j]=couche[i].W[l].dW[j]/(DATATYPE)NBDATA;
            }
            couche[i].W[l].db=0;
            for(int k = 0; k < NBDATA; k++) 
                couche[i].W[l].db+=couche[i].W[l].A[k]-Y[k];
            couche[i].W[l].db=couche[i].W[l].db/(DATATYPE)NBDATA;
        }  
    }
    for (size_t l = 0; l < nbEntree[1]; l++)
    { 
        for(size_t j = 0; j < nbEntree[0]; j++)
        {
            couche[0].W[l].dW[j]=0;
            for(int k = 0; k < NBDATA; k++) 
                couche[0].W[l].dW[j] += X[j][k]*(couche[0].W[l].A[k]-Y[k]);
            couche[0].W[l].dW[j]=couche[0].W[l].dW[j]/(DATATYPE)NBDATA;
        }
        couche[0].W[l].db=0;
        for(int k = 0; k < NBDATA; k++) 
            couche[0].W[l].db+=couche[0].W[l].A[k]-Y[k];
        couche[0].W[l].db=couche[0].W[l].db/(DATATYPE)NBDATA;
    }
}

void update(DATATYPE *W,DATATYPE *b,const DATATYPE* dW,const DATATYPE db,const DATATYPE learning_rate){
    for(int i=0;i<NBPARAM;i++){
        W[i]=W[i]-dW[i]*learning_rate;
    }
    *b=*b-learning_rate*db;
}

void artificial_neurone(DATATYPE *LossList,layerW_T*couche,const X_t X,const _Bool* Y,const DATATYPE learning_rate,const int n_iter){
    DEBUG_S("       début initialisation");
    initialisation(couche);
     DEBUG_S("       fin initialisation");
    printParam(couche);
    for(int i=0;i<n_iter;i++){
        //DEBUG_S1("           début modèle iteration:%d\n",i+1);
        forward_propagation(X,couche);
        //DEBUG_S1("           fin modèle iteration:%d\n",i+1);
        //DEBUG_S1("           début logloss iteration:%d\n",i+1);
        //LossList[i]=log_loss(A,Y);
        //if(i%(n_iter/100)==0)printf("logloss[%d]=%f\n",i,log_loss(A,Y));
        //DEBUG_S1("           fin logloss iteration:%d\n",i+1);
        //DEBUG_S1("           début gradiant iteration:%d\n",i+1);
        back_propagation(couche,X,Y);
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