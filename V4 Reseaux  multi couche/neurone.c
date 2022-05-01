#include "neurone.h"
size_t c,n,p,d;//variable globale d'iteration couche c,neurone n,parametre p,d data
int nbEntree[NBCOUCHE+1]=NBENTREE;//nombre d'entré par couche et donc nombre de neurone de la couche précedente
DATATYPE (*fctActivation[NBCOUCHE])(DATATYPE)=FCTACTIVATION;//fonction d'activation utilisé a chaque couche

void alouerNeuroneW(W_T *ptrN,int nbE){
    ptrN->W = (DATATYPE *)malloc(sizeof(DATATYPE)*(nbE+1));
    if(ptrN->W==NULL)exit(0);
    for(p = 0; p < nbE+1; p++)ptrN->W[p]=(DATATYPE)rand()/((DATATYPE)RAND_MAX/BORNEMAX);
}

void alouerNeuroneG(G_T *ptrN,int nbE){
    ptrN->dW = (DATATYPE *)malloc(sizeof(DATATYPE)*(nbE+1));
    if(ptrN->dW==NULL)exit(0);
    for(d=0;d<NBDATA;d++)ptrN->dz[d]=0;
    for(p=0;p<nbE+1;p++)ptrN->dW[p]=0;
}

void alouerCoucheW(layerW_T *ptrC,int couche){
    ptrC->NW= (W_T *) malloc(sizeof(W_T)*nbEntree[couche+1]);
    if(ptrC->NW==NULL)exit(0);
    for (n = 0; n < nbEntree[couche+1]; n++)alouerNeuroneW(&(ptrC->NW[n]),nbEntree[couche]); 
}

void alouerCoucheG(layerG_T *ptrC,int couche){
    ptrC->NG= (G_T *) malloc(sizeof(G_T)*nbEntree[couche+1]);
    if(ptrC->NG==NULL)exit(0);
    for (n = 0; n < nbEntree[couche+1]; n++)alouerNeuroneG(&(ptrC->NG[n]),nbEntree[couche]); 
}

void alouerCoucheA(layerA_T *ptrC,int couche){
    ptrC->NA= (A_T *) malloc(sizeof(A_T)*nbEntree[couche+1]);
    if(ptrC->NA==NULL)exit(0);
    ptrC->pfActivation= fctActivation[c];
    for (n = 0; n < nbEntree[couche+1]; n++){
        for(d=0;d<NBDATA;d++)ptrC->NA[n].A[d]=0;
    }
}

void initialisation(layerW_T *Wcouche,layerA_T*Acouche,layerG_T*Gcouche){
    for (c = 0; c < NBCOUCHE; c++){
        alouerCoucheW(&(Wcouche[c]),c);
        alouerCoucheA(&(Acouche[c]),c);
        alouerCoucheG(&(Gcouche[c]),c);
    }
}
void printParam(layerW_T *couche){
    printf("%s",ANSI_BLUE);
    for (c = 0; c < NBCOUCHE; c++)//on parcour les couches du modéle
    {
        printf("couche:%ld avec %d neurones\n",c,nbEntree[c+1]);
        for (n = 0; n < nbEntree[c+1]; n++)//on parcour les neurone de chaque couche
        {
            printf("\tneurone:%ld avec %d entrees \n",n,nbEntree[c]);
            printf("\t\tb:%f w:{",couche[c].NW[n].W[nbEntree[c]]);
            for (p = 0; p < nbEntree[c]; p++)//on parcour les parametre d'entrée de chaque neurone
                printf("%f,",couche[c].NW[n].W[p]);
            printf("}\n");
    }   }   
    printf("%s",ANSI_RESET);
}  

void printGradiant(layerG_T *couche){
    printf("%s",ANSI_PURPLE);
    for (c = 0; c < NBCOUCHE; c++)//on parcour les couches du modéle
    {
        printf("couche:%ld avec %d neurones\n",c,nbEntree[c+1]);
        for (n = 0; n < nbEntree[c+1]; n++)//on parcour les neurone de chaque couche
        {
            printf("\tneurone:%ld avec %d entrees \n",n,nbEntree[c]);
            printf("\t\tdz:{");
            for (d = 0; d < NBDATA; d++)//on parcour les parametre d'entrée de chaque neurone
                printf("%f,",couche[c].NG[n].dz[d]);
            printf("}\n");
            printf("\t\tdb:%f dw:{",couche[c].NG[n].dW[nbEntree[c]]);
            for (p = 0; p < nbEntree[c]; p++)//on parcour les parametre d'entrée de chaque neurone
                printf("%f,",couche[c].NG[n].dW[p]);
            printf("}\n");
    }   }
    printf("%s",ANSI_RESET); 
}  

void printActivation(layerA_T *couche){
    printf("%s",ANSI_CYAN);
    for (c = 0; c < NBCOUCHE; c++)//on parcour les couches du modéle
    {
        printf("couche:%ld avec %d neurones\n",c,nbEntree[c+1]);
        for (n = 0; n < nbEntree[c+1]; n++)//on parcour les neurone de chaque couche
        {
            printf("\tneurone:%ld ; A:{",n);
            for(d=0;d<NBDATA;d++)printf("%f,",couche[c].NA[n].A[d]);
            printf("}\n");
    }   }
    printf("%s",ANSI_RESET); 
}

void printAll(layerW_T *Wcouche,_Bool Wflag,layerA_T*Acouche,_Bool Aflag,layerG_T*Gcouche,_Bool Gflag){
    for(c=0;c<NBCOUCHE;c++){
        //printf("couche:%ld\n",c);
        for(n=0;n<nbEntree[c+1];n++){
            //printf("\tneurone:%ld\n",n);
            printf("\033[%ldm C:%ld \033[%ldm N:%ld   ",30+c%8,c,30+n%8,n);
            if(Wflag){
                printf("%s",ANSI_BLUE);
                printf("b=%6.3f  W:{",Wcouche[c].NW[n].W[nbEntree[c]]);
                for(p=0;p<nbEntree[c];p++){
                    printf("%6.3f,",Wcouche[c].NW[n].W[p]);
                }
                printf("}");
            }
            if(Aflag){
                printf("%s",ANSI_CYAN);
                printf("\tA={");
                for(d=0;d<NBDATA;d++){
                    printf("%6.3f,",Acouche[c].NA[n].A[d]);
                }
                printf("}");
            }
            if(Gflag){
                printf("%s",ANSI_PURPLE);
                printf("  dz={");
                for(d=0;d<NBDATA;d++){
                    printf("%6.3f,",Gcouche[c].NG[n].dz[d]);
                }
                printf("}"); 
                printf("\tdb=%6.3f  dW:{",Gcouche[c].NG[n].dW[nbEntree[c]]);
                for(p=0;p<nbEntree[c];p++){
                    printf("%2.3f,",Gcouche[c].NG[n].dW[p]);
                }
                printf("}");
                 
            }

            printf("\n%s",ANSI_RESET);
        }
    }
    printf("\n");
}
void libererNeuroneW(W_T *ptrN){
        free(ptrN->W);
}

void libererNeuroneG(G_T *ptrN){
        free(ptrN->dW);
}

void libererCoucheW(layerW_T *ptrC){
    for (c = 0; c < NBCOUCHE; c++){
        for (n = 0; n< nbEntree[c+1]; n++){
            libererNeuroneW(&(ptrC[c].NW[n]));
            //printf("\tWcouche %ld Wneurone %ld liberer\n",c,n);
        }
        free(ptrC[c].NW);
        //printf("Wcouche %ld liberer\n",c);
    }
}

void libererCoucheG(layerG_T *ptrC){
    for (c = 0; c < NBCOUCHE; c++){
        for (n = 0; n< nbEntree[c+1]; n++){
            libererNeuroneG(&(ptrC[c].NG[n]));
            //printf("\tGcouche %ld Gneurone %ld liberer\n",c,n);
        }
        free(ptrC[c].NG);
        //printf("Gcouche %ld liberer\n",c);
    }
}

void libererCoucheA(layerA_T *ptrC){
    for (c = 0; c < NBCOUCHE; c++){
        free(ptrC[c].NA);
        //printf("Acouche %ld liberer\n",c);
    }
}

//liberer l'ensemble du modéle sur toute ces couches
void libererModele(layerW_T *Wcouche,layerA_T*Acouche,layerG_T*Gcouche){
    libererCoucheW(Wcouche);
    libererCoucheA(Acouche);
    libererCoucheG(Gcouche);
    
}



DATATYPE activation(size_t nA,size_t cA,const layerA_T *Acouche,const layerW_T *Wcouche,const X_t X,size_t dA){
    if(cA==-1){
        return X[nA][dA];
    }else{
        DATATYPE z=Wcouche[cA].NW[nA].W[nbEntree[cA]];
        for (p = 0; p < nbEntree[cA]; p++){
            z+=Wcouche[cA].NW[nA].W[p]*activation(p,cA-1,Acouche,Wcouche,X,dA);
        }
        return Acouche[c].pfActivation(z);
    }
};


void forward_propagation(const X_t X,layerW_T *Wcouche,layerA_T *Acouche){
    
    //pour la couche 0 on prend le dataset en entrée
    //A(0)=sigmoid(X*W(0)+b(0);
    //printf("couche 0\n");
    for (n = 0; n < nbEntree[1]; n++)//pour chque neurone
    {    
        //printf("\tneurone:%ld avec %d entrees \n",n,nbEntree[0]);
        for(d = 0; d < NBDATA; d++)//pour chaque donée
        {
            //printf("\t\tdata:%ld\n",d);
            Acouche[0].NA[n].A[d]=Wcouche[0].NW[n].W[NBPARAM];//bias=W[nbentree[0]]=W[nbparam]
            for(p = 0; p < NBPARAM; p++){
                //printf("\t\t\tparam:%ld\n",p);
                Acouche[0].NA[n].A[d] += X[p][d] * Wcouche[0].NW[n].W[p];
            }
            Acouche[0].NA[n].A[d]=Acouche[0].pfActivation(Acouche[0].NA[n].A[d]);
        }
    }
    //DEBUG_S("test1");
    //pour la couche > on prend l'activation de la couche precedente en entrée
     //A(i)=sigmoid(A(i-1)*W(i)+b(i);   
    for (c = 1; c < NBCOUCHE; c++)//on vas de la cauche la plus basse vers la couche la plus haute
    {    
        //printf("couche %ld\n",c);
        for (n = 0; n < nbEntree[c+1]; n++)
        {   
            //printf("\tneurone:%ld avec %d entrees \n",n,nbEntree[c]);
            for(d = 0; d < NBDATA; d++)
            {
                //printf("\t\tdata:%ld\n",d);
                Acouche[c].NA[n].A[d]=Wcouche[c].NW[n].W[nbEntree[c]];//biase
                for(p = 0; p < nbEntree[c]; p++){
                    //printf("\t\t\tparam:%ld\n",p);
                     Acouche[c].NA[n].A[d] += Acouche[c-1].NA[p].A[d] * Wcouche[c].NW[n].W[p];
                }
                Acouche[c].NA[n].A[d]=1/(1+exp(-Acouche[c].NA[n].A[d]));
            }
        }
    }
}

DATATYPE log_loss(const layerA_T* coucheA,const _Bool* Y){
    DATATYPE res=0;
    for(d=0;d<NBDATA;d++){
        res+= -Y[d]*log(coucheA[NBCOUCHE-1].NA[0].A[d] +EPSILLONE)-(1-Y[d])*log(1-coucheA[NBCOUCHE-1].NA[0].A[d]+EPSILLONE);
    }
    return res/(DATATYPE)NBDATA;
}

void back_propagation(layerW_T* Wcouche,layerA_T* Acouche,layerG_T*Gcouche,const X_t X,const _Bool* Y){
    
    //pour la dernierre couche              // C=NBCOUCHE-1
        //dZ(i)=A(i)-Y                      //dz[C][N]=A[C][N]-Y[C][N]
        //dW(i)=1/nbdata*dZ(i)*A(i-1)^T     //dw[C][N]=1/((Nbentree[C])*dz[C][N]*A[C-1][N]^T)
        //db(i)=1/nbdata*somme(dZ(i))       //db[C][N]=1/((Nbentree[C])*somme(dz[C][N])
    for (n = 0; n < nbEntree[NBCOUCHE]; n++){
        for(d = 0; d < NBDATA; d++){
            Gcouche[NBCOUCHE-1].NG[n].dz[d]=Acouche[NBCOUCHE-1].NA[n].A[d]-Y[d];
        } 
        for(p = 0; p < nbEntree[NBCOUCHE-1]; p++){
            Gcouche[NBCOUCHE-1].NG[n].dW[p]=0;//dw=0
            for(d = 0; d < NBDATA; d++){ 
                Gcouche[NBCOUCHE-1].NG[n].dW[p] += Acouche[NBCOUCHE-2].NA[p].A[d]*Gcouche[NBCOUCHE-1].NG[n].dz[d];
            }
            Gcouche[NBCOUCHE-1].NG[n].dW[p]=Gcouche[NBCOUCHE-1].NG[n].dW[p]/(DATATYPE)nbEntree[NBCOUCHE-1];
        }
        Gcouche[NBCOUCHE-1].NG[n].dW[nbEntree[NBCOUCHE-1]]=0;
        for(d = 0; d < NBDATA; d++) 
            Gcouche[NBCOUCHE-1].NG[n].dW[nbEntree[NBCOUCHE-1]]+=Gcouche[NBCOUCHE-1].NG[n].dz[d];
        Gcouche[NBCOUCHE-1].NG[n].dW[nbEntree[NBCOUCHE-1]]/=(DATATYPE)nbEntree[NBCOUCHE-1];
    }
    
    //DEBUG_S("fin derniere couche");
    //de l'avant dernierre couche à la deuxiemme    // C=NBCOUCHE-2-->>1
        //dZ(i)=W(i+1)^T*dZ(i+1)*A(i)*(1-A(i))      //dz[C][N]=W[C+1][N]^T*dz[C+1][N]*A[C][N]*(1-A[C][N])
        //dW(i)=1/nbdata*dZ(i)*A(i-1)^T             //dw[C][N]=1/((Nbentree[C])*dz[C][N]*A[C-1][N]^T)
        //db(i)=1/nbdata*somme(dZ(i))               //db[C][N]=1/((Nbentree[C])*somme(dz[C][N])
    for (c = NBCOUCHE-2; c > 0; c--){
        //printf("couche %ld\n",c);
        for (n = 0; n < nbEntree[c+1]; n++){ 
            //printf("    neurone %ld\n",n);
            for(d = 0; d < NBDATA; d++){
                //printf("        data %ld\n",d);
                Gcouche[c].NG[n].dz[d]=0;
                for(p = 0; p < nbEntree[c+2]; p++){ 
                    //printf("            parametre %ld\n",p);
                    Gcouche[c].NG[n].dz[d] += Wcouche[c+1].NW[p].W[n]*Gcouche[c+1].NG[p].dz[d];
                }
                Gcouche[c].NG[n].dz[d]*=Acouche[c].NA[n].A[d]*(1-Acouche[c].NA[n].A[d]);
            }
            for(p = 0; p < nbEntree[c]; p++){
                //printf("    parametre %ld\n",p);
                Gcouche[c].NG[n].dW[p]=0;
                for(d = 0; d < NBDATA; d++){ 
                    //printf("        data %ld\n",d);
                    Gcouche[c].NG[n].dW[p] += Acouche[c-1].NA[p].A[d]*Gcouche[c].NG[n].dz[d];
                }
                Gcouche[c].NG[n].dW[p]/=(DATATYPE)nbEntree[c];
            }
            Gcouche[c].NG[n].dW[nbEntree[c]]=0;
            for(d = 0; d < NBDATA; d++){ 
                //printf("    data %ld\n",d);
                Gcouche[c].NG[n].dW[nbEntree[c]]+=Gcouche[c].NG[n].dz[d];
            }
            Gcouche[c].NG[n].dW[nbEntree[c]]=Gcouche[c].NG[n].dW[nbEntree[c]]/(DATATYPE)nbEntree[c];
        }
    }
    //DEBUG_S("debut premiere couche");
    //printf("couche 0\n");
    //pour la premierre                                 // C=0    
        //dZ(i)=W(i+1)^T*dZ(i+1)*A(i)*(1-A(i))          //dz[C][N]=W[C+1][N]^T*dz[C+1][N]*A[C][N]*(1-A[C][N])
        //dW(i)=1/nbdata*dZ(i)*X^T                      //dw[C][N]=1/((Nbentree[C])*dz[C][N]*X^T)
        //db(i)=1/nbdata*somme(dZ(i))                   //db[C][N]=1/((Nbentree[C])*somme(dz[C][N])
    for (n = 0; n < nbEntree[1]; n++){ 
        //printf("    neurone %ld\n",n);
        for(d = 0; d < NBDATA; d++){
            //printf("        data %ld\n",d);
            Gcouche[0].NG[n].dz[d]=0;
            for(p = 0; p < nbEntree[2]; p++){ 
                //printf("            parametre %ld\n",p);
                Gcouche[0].NG[n].dz[d] += Wcouche[1].NW[p].W[n]*Gcouche[1].NG[p].dz[d];
            }
            Gcouche[0].NG[n].dz[d]*=Acouche[0].NA[n].A[d]*(1-Acouche[0].NA[n].A[d]);
        }
        for(p = 0; p < NBPARAM; p++){
            //printf("    parametre %ld\n",p);
            Gcouche[0].NG[n].dW[p]=0;
            for(d = 0; d < NBDATA; d++){ 
                //printf("        data %ld\n",d);
                Gcouche[0].NG[n].dW[p] += X[p][d]*Gcouche[0].NG[n].dz[d];
            }
            Gcouche[0].NG[n].dW[p]/=(DATATYPE)NBPARAM;
        }
        Gcouche[0].NG[n].dW[NBPARAM]=0;
        for(d = 0; d < NBDATA; d++){ 
            //printf("    data %ld\n",d);
            Gcouche[0].NG[n].dW[NBPARAM]+=Gcouche[0].NG[n].dz[d];
        }
        Gcouche[0].NG[n].dW[NBPARAM]=Gcouche[0].NG[n].dW[NBPARAM]/(DATATYPE)NBPARAM;
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
    DEBUG_S("début initialisation");
    initialisation(Wcouche,Acouche,Gcouche);
    DEBUG_S("fin initialisation");
    printAll(Wcouche,1,Acouche,1,Gcouche,1);
    for(size_t i=0;i<n_iter;i++){
        DEBUG_S1("début forward_propagation iteration:%ld\n",i+1);
        forward_propagation(X,Wcouche,Acouche);
        DEBUG_S1("fin forward_propagation iteration:%ld\n",i+1);
        DEBUG_S1("           début logloss iteration:%ld\n",i+1);
        //LossList[i]=log_loss(A,Y);
        if(i%(n_iter/10)==0){
            printf("logloss[%ld]=%f\n",i,log_loss(Acouche,Y));
            printAll(Wcouche,1,Acouche,1,Gcouche,1);
        }
        DEBUG_S1("           fin logloss iteration:%ld\n",i+1);
        DEBUG_S1("début gradiant iteration:%ld\n",i+1);
        back_propagation(Wcouche,Acouche,Gcouche,X,Y);
        DEBUG_S1("fin gradiant iteration:%ld\n",i+1);
        DEBUG_S1("début update iteration:%ld\n",i+1);
        update(Wcouche,Gcouche,learning_rate);
        DEBUG_S1("fin update iteration:%ld\n",i+1);
    }
    printAll(Wcouche,1,Acouche,1,Gcouche,1);
}
void predict(_Bool *Y,const X_t X,layerA_T *coucheA,layerW_T *coucheW){
    DATATYPE A[NBDATA];//resulat fonction d'activation
    for( d=0;d<NBDATA;d++){
        //printf("test3");
        Y[d]=(activation(0,NBCOUCHE-1,coucheA,coucheW,X,d)>0.5)?1:0;
    }
};

DATATYPE acurencyScore(const _Bool* Y,const _Bool* Ypredict){
    DATATYPE res=0;
    for(int j=0;j<NBDATA;j++){
        res+=(Y[j]==Ypredict[j]);
    }   
    return res/(DATATYPE)NBDATA;
};