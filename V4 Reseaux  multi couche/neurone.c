#include "neurone.h"
//int i;int j;
int nbEntree[NBCOUCHE+1]=NBENTREE;//nombre d'entré par couche et donc nombre de neurone de la couche précedente
DATATYPE *fctactivation[NBCOUCHE]=FCTACTIVATION;//fonction d'activation utilisé a chaque couche

void alouerNeurone(W_T *ptrN,int nbE){
    printf("on aloue une neurone (%p)de %d entree\n",ptrN,nbE);
    ptrN->W = (DATATYPE *)malloc(sizeof(DATATYPE)*nbE);
    if(ptrN->W==NULL)exit(0);
    ptrN->dW = (DATATYPE *)malloc(sizeof(DATATYPE)*nbE);
    if(ptrN->dW==NULL)exit(0);
    for(int j = 0; j < nbE; j++)ptrN->W[j]=(DATATYPE)rand()/((DATATYPE)RAND_MAX/BORNEMAX);
    ptrN->b=(DATATYPE)rand()/((DATATYPE)RAND_MAX/BORNEMAX);
}

void alouerCoucheW(layerW_T *ptrC,int couche){
    ptrC->NW= (W_T *) malloc(sizeof(W_T)*nbEntree[couche+1]);
    if(ptrC->NW==NULL)exit(0);
    for (int i = 0; i < nbEntree[couche+1]; i++)alouerNeurone(&(ptrC->NW[i]),nbEntree[couche]); 
}

void alouerCoucheA(layerA_T *ptrC,int couche){
    ptrC->NA= (A_T *) malloc(sizeof(A_T)*nbEntree[couche+1]);
    if(ptrC->NA==NULL)exit(0);
}

void initialisation(layerW_T *Wcouche,layerA_T*Acouche){
    for (int i = 0; i < NBCOUCHE; i++){
        alouerCoucheW(&(Wcouche[i]),i);
        alouerCoucheA(&(Acouche[i]),i);
        Acouche->pfActivation= fctactivation[i];
    }
}
void printParam(layerW_T *couche){
    for (size_t i = 0; i < NBCOUCHE; i++)//on parcour les couches du modéle
    {
        printf("couche:%ld avec %d neurones\n",i+1,nbEntree[i+1]);
        for (size_t j = 0; j < nbEntree[i+1]; j++)//on parcour les neurone de chaque couche
        {
            printf("\tneurone:%ld avec %d entrees \n",j+1,nbEntree[i]);
            printf("\t\tb:%f w:{",couche[i].NW[j].b);
            for (size_t k = 0; k < nbEntree[i]; k++)//on parcour les parametre d'entrée de chaque neurone
                printf("%f,",couche[i].NW[j].W[k]);
            printf("}\n");
}   }   }  

void libererNeurone(W_T *ptrN){
        //printf("neurone %p liberer\n",ptrN);
        free(ptrN->W);
        free(ptrN->dW);
}
void libererCouche(layerW_T *ptrC){
    for (size_t j = 0; j < NBCOUCHE; j++){
        for (int i = 0; i < nbEntree[i+1]; i++)
            libererNeurone(&(ptrC[j].NW[i]));
        free(ptrC[j].NW);
    }
}
void forward_propagation(const X_t X,layerW_T *Wcouche,layerA_T *Acouche){
    
    //pour la couche 0 on prend le dataset en entrée
    //A(0)=sigmoid(X*W(0)+b(0);
    for (size_t l = 0; l < nbEntree[1]; l++)//pour chque neurone
    {    
        //printf("test2\n");
        for(size_t j = 0; j < NBDATA; j++)//pour chaque donée
        {
            //printf("test3 %f;%ld;%ld\n",Wcouche[0].NW[l].b,l,j);
            Acouche[0].NA[l].A[j]=Wcouche[0].NW[l].b;
            //printf("test4\n");
            for(size_t k = 0; k < NBPARAM; k++){
                //printf("test4\n");
                Acouche[0].NA[l].A[j] += X[k][j] * Wcouche[0].NW[l].W[k];
                //printf("test5\n");
            }
            Acouche[0].NA[l].A[j]=Acouche[0].pfActivation(Acouche[0].NA[l].A[j]);
            //printf("test6\n");
        }
    }
    //DEBUG_S("test1");
    //pour la couche > on prend l'activation de la couche precedente en entrée
     //A(i)=sigmoid(A(i-1)*W(i)+b(i);   
    for (size_t i = 1; i < NBCOUCHE; i++)//on vas de la cauche la plus basse vers la couche la plus haute
    {    
        for (size_t l = 0; l < nbEntree[i+1]; l++)
        {    
            for(size_t j = 0; j < NBDATA; j++)
            {
                Acouche[i].NA[l].A[j]=Wcouche[i].NW[l].b;
                for(size_t k = 0; k < nbEntree[i]; k++) Acouche[i].NA[l].A[j] += Acouche[i-1].NA[k].A[j] * Wcouche[i].NW[l].W[k];
                Acouche[i].NA[l].A[j]=1/(1+exp(-Acouche[i].NA[l].A[j]));
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

void back_propagation(layerW_T* Wcouche,layerA_T* Acouche,const X_t X,const _Bool* Y){
    
    //pour la dernierre couche
        //dZ(i)=A(i)-Y
        //dW(i)=1/nbdata*dZ(3)*A(i-1)^T
        //db(i)=1/nbdata*somme(dZ(i))
    for (size_t l = 0; l < nbEntree[1]; l++)
    { 
        for(size_t j = 0; j < nbEntree[0]; j++)
        {
            Wcouche[0].NW[l].dW[j]=0;
            for(int k = 0; k < NBDATA; k++) 
                Wcouche[0].NW[l].dW[j] += X[j][k]*(Acouche[0].NA[l].A[k]-Y[k]);
            Wcouche[0].NW[l].dW[j]=Wcouche[0].NW[l].dW[j]/(DATATYPE)NBDATA;
        }
        Wcouche[0].NW[l].db=0;
        for(int k = 0; k < NBDATA; k++) 
            Wcouche[0].NW[l].db+=Acouche[0].NA[l].A[k]-Y[k];
        Wcouche[0].NW[l].db=Wcouche[0].NW[l].db/(DATATYPE)NBDATA;
    }
    //de l'avant dernierre couche à la deuxiemme
        //dZ(i)=W(i+1)^T*dZ(i+1)*A(i)*(1-A(i))
        //dW(i)=1/nbdata*dZ(i)*A(i-1)^T
        //db(i)=1/nbdata*somme(dZ(i))
    for (size_t i = NBCOUCHE-2; i > 0; i--)
    {
        for (size_t l = 0; l < nbEntree[i+1]; l++)
        { 
            for(size_t j = 0; j < nbEntree[i]; j++)
            {
                Wcouche[i].NW[l].dW[j]=0;
                for(int k = 0; k < NBDATA; k++) 
                    Wcouche[i].NW[l].dW[j] += X[j][k]*(Acouche[i].NA[l].A[k]-Y[k]);
                Wcouche[i].NW[l].dW[j]=Wcouche[i].NW[l].dW[j]/(DATATYPE)NBDATA;
            }
            Wcouche[i].NW[l].db=0;
            for(int k = 0; k < NBDATA; k++) 
                Wcouche[i].NW[l].db+=Acouche[i].NA[l].A[k]-Y[k];
            Wcouche[i].NW[l].db=Wcouche[i].NW[l].db/(DATATYPE)NBDATA;
        }  
    }

    //pour la premierre
        //de l'avant dernierre couche à la deuxiemme
        //dZ(i)=W(i+1)^T*dZ(i+1)*A(i)*(1-A(i))
        //dW(i)=1/nbdata*dZ(i)*X^T
        //db(i)=1/nbdata*somme(dZ(i))
    for (size_t l = 0; l < nbEntree[1]; l++)
    { 
        for(size_t j = 0; j < nbEntree[0]; j++)
        {
            Wcouche[0].NW[l].dW[j]=0;
            for(int k = 0; k < NBDATA; k++) 
                Wcouche[0].NW[l].dW[j] += X[j][k]*(Acouche[0].NA[l].A[k]-Y[k]);
            Wcouche[0].NW[l].dW[j]=Wcouche[0].NW[l].dW[j]/(DATATYPE)NBDATA;
        }
        Wcouche[0].NW[l].db=0;
        for(int k = 0; k < NBDATA; k++) 
            Wcouche[0].NW[l].db+=Acouche[0].NA[l].A[k]-Y[k];
        Wcouche[0].NW[l].db=Wcouche[0].NW[l].db/(DATATYPE)NBDATA;
    }
}

void update(DATATYPE *W,DATATYPE *b,const DATATYPE* dW,const DATATYPE db,const DATATYPE learning_rate){
    for(int i=0;i<NBPARAM;i++){
        W[i]=W[i]-dW[i]*learning_rate;
    }
    *b=*b-learning_rate*db;
}

void artificial_neurone(DATATYPE *LossList,layerW_T*Wcouche,layerA_T*Acouche,const X_t X,const _Bool* Y,const DATATYPE learning_rate,const int n_iter){
    DEBUG_S("       début initialisation");
    initialisation(Wcouche,Acouche);
    DEBUG_S("       fin initialisation");
    printParam(Wcouche);
    for(int i=0;i<n_iter;i++){
        DEBUG_S1("début forward_propagation iteration:%d\n",i+1);
        forward_propagation(X,Wcouche,Acouche);
        DEBUG_S1("           fin forward_propagation iteration:%d\n",i+1);
    /*    //DEBUG_S1("           début logloss iteration:%d\n",i+1);
        //LossList[i]=log_loss(A,Y);
        //if(i%(n_iter/100)==0)printf("logloss[%d]=%f\n",i,log_loss(A,Y));
        //DEBUG_S1("           fin logloss iteration:%d\n",i+1);
        //DEBUG_S1("           début gradiant iteration:%d\n",i+1);
        back_propagation(Wcouche,X,Y);
        //DEBUG_S1("           fin gradiant iteration:%d\n",i+1);
        //DEBUG_S1("           début update iteration:%d\n",i+1);
        update(W,b,dW,db,learning_rate);
        //DEBUG_C(afficherMat2d(*W,"W");)
        //DEBUG_C(printf("b:%f\n",*b);)
        //DEBUG_S1("           fin update iteration:%d\n",i+1);*/
    }
}
void predict(_Bool *Y,const X_t X,const DATATYPE* W,const DATATYPE b){
    DATATYPE A[NBDATA];//resulat fonction d'activation
    //printf("test1");
    //forward_propagation(A,X,W,b);
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