#include "neurone.h"
size_t c,n,p,d;//variable globale d'iteration couche c,neurone n,parametre p,d data
int nbEntree[NBCOUCHE+1]=NBENTREE;//nombre d'entré par couche et donc nombre de neurone de la couche précedente
DATATYPE *fctActivation[NBCOUCHE]=FCTACTIVATION;//fonction d'activation utilisé a chaque couche

void alouerNeuroneW(W_T *ptrN,int nbE){
    ptrN->W = (DATATYPE *)malloc(sizeof(DATATYPE)*(nbE+1));
    if(ptrN->W==NULL)exit(0);
    for(p = 0; p < nbE+1; p++)ptrN->W[p]=(DATATYPE)rand()/((DATATYPE)RAND_MAX/BORNEMAX);
}

void alouerNeuroneG(G_T *ptrN,int nbE){
    ptrN->dW = (DATATYPE *)malloc(sizeof(DATATYPE)*(nbE+1));
    if(ptrN->dW==NULL)exit(0);
}

void alouerCoucheW(layerW_T *ptrC,int couche){
    ptrC->NW= (W_T *) malloc(sizeof(W_T)*nbEntree[couche+1]);
    if(ptrC->NW==NULL)exit(0);
    for (n = 0; n < nbEntree[couche+1]; n++)alouerNeurone(&(ptrC->NW[n]),nbEntree[couche]); 
}

void alouerCoucheA(layerA_T *ptrC,int couche){
    ptrC->NA= (A_T *) malloc(sizeof(A_T)*nbEntree[couche+1]);
    if(ptrC->NA==NULL)exit(0);
}

void initialisation(layerW_T *Wcouche,layerA_T*Acouche,layerG_T*Gcouche){
    for (c = 0; c < NBCOUCHE; c++){
        alouerCoucheW(&(Wcouche[c]),c);
        alouerCoucheA(&(Acouche[c]),c);
        alouerCoucheG(&(Gcouche[c]),c);
        Acouche->pfActivation= fctActivation[c];
    }
}
void printParam(layerW_T *couche){
    for (c = 0; c < NBCOUCHE; c++)//on parcour les couches du modéle
    {
        printf("couche:%ld avec %d neurones\n",c+1,nbEntree[c+1]);
        for (n = 0; n < nbEntree[c+1]; n++)//on parcour les neurone de chaque couche
        {
            printf("\tneurone:%ld avec %d entrees \n",n+1,nbEntree[c]);
            printf("\t\tb:%f w:{",couche[c].NW[n].W[nbEntree[c]]);
            for (p = 0; p < nbEntree[c]; p++)//on parcour les parametre d'entrée de chaque neurone
                printf("%f,",couche[c].NW[n].W[p]);
            printf("}\n");
}   }   }  

void libererNeuroneW(W_T *ptrN){
        //printf("neurone %p liberer\n",ptrN);
        free(ptrN->W);
}

void libererNeuroneG(G_T *ptrN){
        //printf("neurone %p liberer\n",ptrN);
        free(ptrN->dW);
}

void libererCoucheW(layerW_T *ptrC){
    for (c = 0; c < NBCOUCHE; c++){
        for (n = 0; n< nbEntree[c+1]; n++)
            libererNeuroneW(&(ptrC[c].NW[n]));
        free(ptrC[c].NW);
    }
}

void libererNeuroneG(G_T *ptrN){
        //printf("neurone %p liberer\n",ptrN);
        free(ptrN->dW);
}

void liberarCoucheA(layerA_T *ptrC){
    for (c = 0; c < NBCOUCHE; c++){
        for (n = 0; n < nbEntree[c+1]; n++)
            libererNeuroneA(&(ptrC[c].NA[n]));
        free(ptrC[c].NA);
    }
}

//liberer l'ensemble du modéle sur toute ces couches
void libererModele(layerW_T *Wcouche,layerA_T*Acouche,layerG_T*Gcouche){
    for (c = 0; c < NBCOUCHE; c++){
        libererCoucheW(&(Wcouche[c]));
        libererCoucheA(&(Acouche[c]));
        libererCoucheG(&(Gcouche[c]));
    }
}

void forward_propagation(const X_t X,layerW_T *Wcouche,layerA_T *Acouche){
    
    //pour la couche 0 on prend le dataset en entrée
    //A(0)=sigmoid(X*W(0)+b(0);
    for (n = 0; n < nbEntree[1]; n++)//pour chque neurone
    {    
        //printf("test2\n");
        for(d = 0; d < NBDATA; d++)//pour chaque donée
        {
            //printf("test3 %f;%ld;%ld\n",Wcouche[0].NW[l].b,l,j);
            Acouche[0].NA[n].A[d]=Wcouche[0].NW[n].W[NBPARAM];//bias=W[nbentree[0]]=W[nbentree]
            //printf("test4\n");
            for(p = 0; p < NBPARAM; p++){
                //printf("test4\n");
                Acouche[0].NA[n].A[d] += X[p][d] * Wcouche[0].NW[n].W[p];
                //printf("test5\n");
            }
            Acouche[0].NA[n].A[d]=Acouche[0].pfActivation(Acouche[0].NA[n].A[d]);
            //printf("test6\n");
        }
    }
    //DEBUG_S("test1");
    //pour la couche > on prend l'activation de la couche precedente en entrée
     //A(i)=sigmoid(A(i-1)*W(i)+b(i);   
    for (c = 1; c < NBCOUCHE; c++)//on vas de la cauche la plus basse vers la couche la plus haute
    {    
        for (n = 0; n < nbEntree[c+1]; n++)
        {    
            for(d = 0; d < NBDATA; d++)
            {
                Acouche[c].NA[n].A[d]=Wcouche[c].NW[n].W[nbEntree[d]];//biase
                for(p = 0; p < nbEntree[c]; p++) Acouche[c].NA[n].A[d] += Acouche[c-1].NA[p].A[d] * Wcouche[c].NW[n].W[p];
                Acouche[c].NA[n].A[d]=1/(1+exp(-Acouche[c].NA[n].A[d]));
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

void back_propagation(layerW_T* Wcouche,layerA_T* Acouche,layerG_T*Gcouche,const X_t X,const _Bool* Y){
    
    //pour la dernierre couche              // C=NBCOUCHE-1
        //dZ(i)=A(i)-Y                      //dz[C][N]=A[C][N]-Y[C][N]
        //dW(i)=1/nbdata*dZ(i)*A(i-1)^T     //dw[C][N]=1/((Nbentree[C])*dz[C][N]*A[C-1][N]^T)
        //db(i)=1/nbdata*somme(dZ(i))       //db[C][N]=1/((Nbentree[C])*somme(dz[C][N])
    for (n = 0; n < nbEntree[NBCOUCHE]; n++){ 
        for(p = 0; p < nbEntree[NBCOUCHE-1]; p++){
            Gcouche[NBCOUCHE-1].NG[n].dW[p]=0;//dw=0
            for(d = 0; d < NBDATA; d++){ 
                Gcouche[NBCOUCHE-1].NG[n].dz[d]=Acouche[NBCOUCHE-1].NA[n].A[d]-Y[d];
                Gcouche[NBCOUCHE-1].NG[n].dW[p] += Acouche[NBCOUCHE-2].NA[p].A[d]*Gcouche[NBCOUCHE-1].NG[n].dz[d];
            }
            Gcouche[NBCOUCHE-1].NG[n].dW[p]=Gcouche[NBCOUCHE-1].NG[n].dW[p]/(DATATYPE)nbEntree[NBCOUCHE-1];
        }
        Gcouche[NBCOUCHE-1].NG[n].dW[nbEntree[NBCOUCHE-1]]=0;
        for(d = 0; d < NBDATA; d++) 
            Gcouche[NBCOUCHE-1].NG[n].dW[nbEntree[NBCOUCHE-1]]+=Gcouche[NBCOUCHE-1].NG[n].dz[d];
        Gcouche[NBCOUCHE-1].NG[n].dW[nbEntree[NBCOUCHE-1]]=Gcouche[NBCOUCHE-1].NG[n].dW[nbEntree[NBCOUCHE-1]]/(DATATYPE)nbEntree[NBCOUCHE-1];
    }
    //de l'avant dernierre couche à la deuxiemme    // C=NBCOUCHE-2-->>1
        //dZ(i)=W(i+1)^T*dZ(i+1)*A(i)*(1-A(i))      //dz[C][N]=W[C+1][N]^T*dz[C+1][N]*A[C][N]*(1-A[C][N])
        //dW(i)=1/nbdata*dZ(i)*A(i-1)^T             //dw[C][N]=1/((Nbentree[C])*dz[C][N]*A[C-1][N]^T)
        //db(i)=1/nbdata*somme(dZ(i))               //db[C][N]=1/((Nbentree[C])*somme(dz[C][N])
    for (c = NBCOUCHE-2; c > 0; c--){
        for (n = 0; n < nbEntree[c+1]; n++){ 
            for(p = 0; p < nbEntree[c]; p++){
                Gcouche[c].NG[n].dW[p]=0;//dw=0
                for(d = 0; d < NBDATA; d++){ 
                    Gcouche[c].NG[n].dz[d]=;//TODO
                    Gcouche[c].NG[n].dW[p] += Acouche[c-1].NA[p].A[d]*Gcouche[c].NG[n].dz[d];
                }
                Gcouche[c].NG[n].dW[p]=Gcouche[c].NG[n].dW[p]/(DATATYPE)nbEntree[c];
            }
            Gcouche[c].NG[n].dW[nbEntree[c]]=0;
            for(d = 0; d < NBDATA; d++) 
                Gcouche[c].NG[n].dW[nbEntree[c]]+=Gcouche[c].NG[n].dz[d];
            Gcouche[c].NG[n].dW[nbEntree[c]]=Gcouche[c].NG[n].dW[nbEntree[c]]/(DATATYPE)nbEntree[c];
        }
    }

    //pour la premierre                                 // C=0    
        //dZ(i)=W(i+1)^T*dZ(i+1)*A(i)*(1-A(i))          //dz[C][N]=W[C+1][N]^T*dz[C+1][N]*A[C][N]*(1-A[C][N])
        //dW(i)=1/nbdata*dZ(i)*X^T                      //dw[C][N]=1/((Nbentree[C])*dz[C][N]*X^T)
        //db(i)=1/nbdata*somme(dZ(i))                   //db[C][N]=1/((Nbentree[C])*somme(dz[C][N])
    for (n = 0; n < nbEntree[1]; n++){ 
        for(p = 0; p < nbEntree[0]; p++){
            Gcouche[0].NG[n].dW[p]=0;//dw=0
            for(d = 0; d < NBDATA; d++){ 
                Gcouche[0].NG[n].dz[d]=;//TODO
                Gcouche[0].NG[n].dW[p] += X[p][d]*Gcouche[0].NG[n].dz[d];
            }
            Gcouche[0].NG[n].dW[p]=Gcouche[0].NG[n].dW[p]/(DATATYPE)nbEntree[0];
        }
        Gcouche[0].NG[n].dW[NBPARAM]=0;
        for(d = 0; d < NBDATA; d++) 
            Gcouche[0].NG[n].dW[NBPARAM]+=Gcouche[0].NG[n].dz[d];
        Gcouche[0].NG[n].dW[NBPARAM]=Gcouche[0].NG[n].dW[NBPARAM]/(DATATYPE)nbEntree[0];
    }
}

void update(layerW_T*Wcouche,layerG_T*Gcouche,const DATATYPE learning_rate){
    for (c = NBCOUCHE-2; c > 0; c--){
        for (n = 0; n < nbEntree[c+1]; n++){ 
            for(p = 0; p < nbEntree[c]; p++){
                Wcouche[c].NW[n].W[p]-=Gcouche[c].NG[n].dW[p]*learning_rate;
            }
            Wcouche[c].NW[n].W[nbEntree[c]]-=Gcouche[c].NG[n].dW[nbEntree[c]]*learning_rate;
        }
    }
}

void artificial_neurone(DATATYPE *LossList,layerW_T*Wcouche,layerA_T*Acouche,layerG_T*Gcouche, const X_t X,const _Bool* Y,const DATATYPE learning_rate,const int n_iter){
    DEBUG_S("       début initialisation");
    initialisation(Wcouche,Acouche,Gcouche);
    DEBUG_S("       fin initialisation");
    printParam(Wcouche);
    for(int i=0;i<n_iter;i++){
        DEBUG_S1("début forward_propagation iteration:%d\n",i+1);
        forward_propagation(X,Wcouche,Acouche);
        DEBUG_S1("           fin forward_propagation iteration:%d\n",i+1);
        //DEBUG_S1("           début logloss iteration:%d\n",i+1);
        //LossList[i]=log_loss(A,Y);
        //if(i%(n_iter/100)==0)printf("logloss[%d]=%f\n",i,log_loss(A,Y));
        //DEBUG_S1("           fin logloss iteration:%d\n",i+1);
        //DEBUG_S1("           début gradiant iteration:%d\n",i+1);
        back_propagation(Wcouche,Acouche,Gcouche,X,Y);
        //DEBUG_S1("           fin gradiant iteration:%d\n",i+1);
        //DEBUG_S1("           début update iteration:%d\n",i+1);
        update(Wcouche,Gcouche,learning_rate);
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