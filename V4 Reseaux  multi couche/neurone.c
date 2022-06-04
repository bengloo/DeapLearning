#include "neurone.h"
size_t c,n,p,d;//variable globale d'iteration couche c,neurone n,parametre p,d data
size_t nbEntree[NBCOUCHE+1]=NBENTREE;//nombre d'entré par couche et donc nombre de neurone de la couche précedente
size_t * nbNeurone =&(nbEntree[1]);
DATATYPE (*fctActivation[NBCOUCHE])(DATATYPE)=FCTACTIVATION;//fonction d'activation utilisé a chaque couche
size_t nbentreeMax=0;//nombre d'entré max d'une couche

void integriteeSettings(){
    DEBUG_S1("size(nbentree):%ld\n",sizeof(nbEntree)/sizeof(nbEntree[0]));
    DEBUG_S1("size(fctActivation):%ld\n",sizeof(fctActivation)/sizeof(fctActivation[0]));
    if(sizeof(nbEntree)/sizeof(nbEntree[0])<NBCOUCHE+1){
        printf("%s",ANSI_RED);
        printf("la definition du nombre entrees/neurones par couche est invalide dans les settings\n");
        exit(1);
    }
    if(sizeof(fctActivation)/sizeof(fctActivation[0])<NBCOUCHE){
        printf("%s",ANSI_RED);
        printf("la definition des fonction d'activation par couche est invalide dans les settings\n");
        exit(1);
    }
    printf("%s",ANSI_RESET);
};

void alouerNeuroneW(W_T *ptrN,int nbE){
    ptrN->W = (DATATYPE *)malloc(sizeof(DATATYPE)*(nbE+1));
    if(ptrN->W==NULL)exit(0);
    #ifdef INITRDM
        for(p = 0; p < nbE+1; p++)ptrN->W[p]=(DATATYPE)rand()/((DATATYPE)RAND_MAX/BORNEMAX);
    #else
        for(p = 0; p < nbE+1; p++)ptrN->W[p]=p/(DATATYPE)nbE;
    #endif
};

void alouerNeuroneG(G_T *ptrN,int nbE){
    ptrN->dW = (DATATYPE *)malloc(sizeof(DATATYPE)*(nbE+1));
    if(ptrN->dW==NULL)exit(0);
    for(d=0;d<NBDATA;d++)ptrN->dz[d]=0;
    for(p=0;p<nbE+1;p++)ptrN->dW[p]=0;
};

void alouerCoucheW(layerW_T *ptrC,int couche){
    ptrC->NW= (W_T *) malloc(sizeof(W_T)*nbNeurone[couche]);
    if(ptrC->NW==NULL)exit(0);
    for (n = 0; n < nbNeurone[couche]; n++)alouerNeuroneW(&(ptrC->NW[n]),nbEntree[couche]); 
};

void alouerCoucheG(layerG_T *ptrC,int couche){
    ptrC->NG= (G_T *) malloc(sizeof(G_T)*nbNeurone[couche]);
    if(ptrC->NG==NULL)exit(0);
    for (n = 0; n < nbNeurone[couche]; n++)alouerNeuroneG(&(ptrC->NG[n]),nbEntree[couche]); 
};

void alouerCoucheA(layerA_T *ptrC,int couche){
    ptrC->NA= (A_T *) malloc(sizeof(A_T)*nbNeurone[couche]);
    if(ptrC->NA==NULL)exit(0);
    ptrC->pfActivation= fctActivation[c];
    for (n = 0; n < nbNeurone[couche]; n++){
        for(d=0;d<NBDATA;d++)ptrC->NA[n].A[d]=0;
    }
};

void initialisation(layerW_T *Wcouche,layerA_T*Acouche,layerG_T*Gcouche){
    for(c=0;c<NBCOUCHE;c++){
        nbentreeMax=(nbentreeMax>nbEntree[c])?nbentreeMax:nbEntree[c];  
    }
    for (c = 0; c < NBCOUCHE; c++){
        alouerCoucheW(&(Wcouche[c]),c);
        alouerCoucheA(&(Acouche[c]),c);
        alouerCoucheG(&(Gcouche[c]),c);
    }
};

void printAll(layerW_T *Wcouche,_Bool Wflag,layerA_T*Acouche,_Bool Aflag,layerG_T*Gcouche,_Bool Gflag,_Bool Gflag2){
    for(c=0;c<NBCOUCHE;c++){
        //printf("couche:%ld\n",c);
        for(n=0;n<nbNeurone[c];n++){
            //printf("\tneurone:%ld\n",n);
            printf("\033[%ldm C:%ld \033[%ldm N:%ld",30+c%8,c,30+n%8,n);
            if(Aflag){
                printf("%s",ANSI_CYAN);
                printf(" A={");
                printf("%*.*f",PRINT_LENGTH,PRINT_PRECISION,Acouche[c].NA[n].A[0]);
                for(d=1;d<NBDATA;d++){
                    printf(",%*.*f",PRINT_LENGTH,PRINT_PRECISION,Acouche[c].NA[n].A[d]);
                }
                printf("}");
            }
            if(Wflag){
                printf("%s",ANSI_BLUE);
                printf(" b=%*.*f W:{",PRINT_LENGTH,PRINT_PRECISION,Wcouche[c].NW[n].W[nbEntree[c]]);
                printf("%*.*f",PRINT_LENGTH,PRINT_PRECISION,Wcouche[c].NW[n].W[0]);
                for(p=1;p<nbentreeMax;p++){
                    if(p<nbEntree[c])
                        printf(",%*.*f",PRINT_LENGTH,PRINT_PRECISION,Wcouche[c].NW[n].W[p]);
                    else
                        printf("%*s",PRINT_LENGTH+1,"");
                }
                printf("}");
            }
            if(Gflag){
                printf("%s",ANSI_PURPLE);
                printf(" dz={");
                printf("%*.*f",PRINT_LENGTH,PRINT_PRECISION,Gcouche[c].NG[n].dz[0]);
                for(d=1;d<NBDATA;d++){
                    printf(",%*.*f",PRINT_LENGTH,PRINT_PRECISION,Gcouche[c].NG[n].dz[d]);
                }
                printf("}");
            }
            if(Gflag2){ 
                printf(" db=%*.*f dW:{",PRINT_LENGTH,PRINT_PRECISION,Gcouche[c].NG[n].dW[nbEntree[c]]);
                printf("%*.*f",PRINT_LENGTH,PRINT_PRECISION,Gcouche[c].NG[n].dW[0]);
                for(p=1;p<nbentreeMax;p++){
                    if(p<nbEntree[c])
                        printf(",%*.*f",PRINT_LENGTH,PRINT_PRECISION,Gcouche[c].NG[n].dW[p]);
                    else
                        printf("%*s",PRINT_LENGTH+1,"");
                }
                printf("}");
            }
            printf("\n%s",ANSI_RESET);
        }
    }
    printf("\n");
};

void libererNeuroneW(W_T *ptrN){
        free(ptrN->W);
};

void libererNeuroneG(G_T *ptrN){
        free(ptrN->dW);
};

void libererCoucheW(layerW_T *ptrC){
    for (c = 0; c < NBCOUCHE; c++){
        for (n = 0; n< nbNeurone[c]; n++){
            libererNeuroneW(&(ptrC[c].NW[n]));
            //printf("\tWcouche %ld Wneurone %ld liberer\n",c,n);
        }
        free(ptrC[c].NW);
        //printf("Wcouche %ld liberer\n",c);
    }
};

void libererCoucheG(layerG_T *ptrC){
    for (c = 0; c < NBCOUCHE; c++){
        for (n = 0; n< nbNeurone[c]; n++){
            libererNeuroneG(&(ptrC[c].NG[n]));
            //printf("\tGcouche %ld Gneurone %ld liberer\n",c,n);
        }
        free(ptrC[c].NG);
        //printf("Gcouche %ld liberer\n",c);
    }
};

void libererCoucheA(layerA_T *ptrC){
    for (c = 0; c < NBCOUCHE; c++){
        free(ptrC[c].NA);
        //printf("Acouche %ld liberer\n",c);
    }
};

void libererModele(layerW_T *Wcouche,layerA_T*Acouche,layerG_T*Gcouche){
    libererCoucheW(Wcouche);
    libererCoucheA(Acouche);
    libererCoucheG(Gcouche); 
};



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
    
    #if NBCOUCHE != 1
        //pour la couche 0 on prend le dataset en entrée
        //A(0)=sigmoid(X*W(0)+b(0);
        //printf("couche 0\n");
        for (n = 0; n < nbNeurone[0]; n++)//pour chque neurone
        {    
            //printf("\tneurone:%ld avec %ld entrees \n",n,nbEntree[0]);
            for(d = 0; d < NBDATA; d++)//pour chaque donée
            {
                //printf("\t\tdata:%ld\n",d);
                Acouche[0].NA[n].A[d]=Wcouche[0].NW[n].W[NBPARAM];//bias=W[nbentree[0]]=W[nbparam]
                for(p = 0; p < NBPARAM; p++){
                    //printf("\t\t\tparam:%ld\n",p);
                    Acouche[0].NA[n].A[d] += Wcouche[0].NW[n].W[p]*X[p][d] ;
                    //DEBUG_S("test1");
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
            for (n = 0; n < nbNeurone[c]; n++)
            {   
                //printf("\tneurone:%ld avec %d entrees \n",n,nbEntree[c]);
                for(d = 0; d < NBDATA; d++)
                {
                    //printf("\t\tdata:%ld\n",d);
                    Acouche[c].NA[n].A[d]=Wcouche[c].NW[n].W[nbEntree[c]];//biase
                    for(p = 0; p < nbEntree[c]; p++){
                        //printf("\t\t\tparam:%ld\n",p);
                        Acouche[c].NA[n].A[d] += Wcouche[c].NW[n].W[p]*Acouche[c-1].NA[p].A[d] ;
                    }
                    //printf("c:%ld n:%ld d:%ld %f\n",c,n,d,Acouche[c].NA[n].A[d]);
                    Acouche[c].NA[n].A[d]=Acouche[c].pfActivation(Acouche[c].NA[n].A[d]);
                }
            }
        }
    #else
        for (n = 0; n < nbNeurone[0]; n++)//pour chque neurone
        {    
            for(d = 0; d < NBDATA; d++)//pour chaque donée
            {
                Acouche[0].NA[n].A[d]=Wcouche[0].NW[n].W[NBPARAM];//bias=W[nbentree[0]]=W[nbparam]
                for(p = 0; p < NBPARAM; p++){
                    Acouche[0].NA[n].A[d] += Wcouche[0].NW[n].W[p]*X[p][d] ;
                }
                Acouche[0].NA[n].A[d]=Acouche[0].pfActivation(Acouche[0].NA[n].A[d]);
            }
        }
    #endif
};

DATATYPE log_loss(const layerA_T* coucheA,const _Bool* Y){
    DATATYPE res=0;
    for(d=0;d<NBDATA;d++){
        res+= -Y[d]*log(coucheA[NBCOUCHE-1].NA[0].A[d] +EPSILLONE)-(1-Y[d])*log(1-coucheA[NBCOUCHE-1].NA[0].A[d]+EPSILLONE);
    }
    return res/(DATATYPE)NBDATA;
};

void back_propagation(layerW_T* Wcouche,layerA_T* Acouche,layerG_T*Gcouche,const X_t X,const _Bool* Y){
    
    #if NBCOUCHE != 1
        //pour la dernierre couche              // C=NBCOUCHE-1
            //dZ(i)=A(i)-Y                      //dz[C][N]=A[C][N]-Y[C][N]
            //dW(i)=1/nbdata*dZ(i)*A(i-1)^T     //dw[C][N]=1/((Nbentree[C])*dz[C][N]*A[C-1][N]^T)
            //db(i)=1/nbdata*somme(dZ(i))       //db[C][N]=1/((Nbentree[C])*somme(dz[C][N])
        c=NBCOUCHE-1;
        for (n = 0; n < nbNeurone[c]; n++){
            for(d = 0; d < NBDATA; d++){
                Gcouche[c].NG[n].dz[d]=Acouche[c].NA[n].A[d]-Y[d];
            }
        }
        for (n = 0; n < nbNeurone[c]; n++){ 
            for(p = 0; p < nbEntree[c]; p++){
                Gcouche[c].NG[n].dW[p]=0;//dw=0
                for(d = 0; d < NBDATA; d++){ 
                    Gcouche[c].NG[n].dW[p] +=Gcouche[c].NG[n].dz[d]*Acouche[c-1].NA[p].A[d];
                }
                Gcouche[c].NG[n].dW[p]=Gcouche[c].NG[n].dW[p]/(DATATYPE)NBDATA;
            }
            Gcouche[c].NG[n].dW[nbEntree[c]]=0;//db est stoqué à la fin de dw ...
            for(d = 0; d < NBDATA; d++) 
                Gcouche[c].NG[n].dW[nbEntree[c]]+=Gcouche[c].NG[n].dz[d];
            Gcouche[c].NG[n].dW[nbEntree[c]]=Gcouche[c].NG[n].dW[nbEntree[c]]/(DATATYPE)NBDATA;
        }
        
        //DEBUG_S("fin derniere couche");
        //de l'avant dernierre couche à la deuxiemme    // C=NBCOUCHE-2-->>1
            //dZ(i)=W(i+1)^T*dZ(i+1)*A(i)*(1-A(i))      //dz[C][N]=W[C+1][N]^T*dz[C+1][N]*A[C][N]*(1-A[C][N])
            //dW(i)=1/nbdata*dZ(i)*A(i-1)^T             //dw[C][N]=1/((Nbentree[C])*dz[C][N]*A[C-1][N]^T)
            //db(i)=1/nbdata*somme(dZ(i))               //db[C][N]=1/((Nbentree[C])*somme(dz[C][N])
        for (c = NBCOUCHE-2; c > 0; c--){
            //printf("couche %ld\n",c);
            for (n = 0; n < nbNeurone[c]; n++){ 
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
            }
            for (n = 0; n < nbNeurone[c]; n++){ 
                for(p = 0; p < nbEntree[c]; p++){
                    //printf("    parametre %ld\n",p);
                    Gcouche[c].NG[n].dW[p]=0;
                    for(d = 0; d < NBDATA; d++){ 
                        //printf("        data %ld\n",d);
                        Gcouche[c].NG[n].dW[p] += Acouche[c-1].NA[p].A[d]*Gcouche[c].NG[n].dz[d];
                    }
                    Gcouche[c].NG[n].dW[p]/=(DATATYPE)NBDATA;
                }
                Gcouche[c].NG[n].dW[nbEntree[c]]=0;
                for(d = 0; d < NBDATA; d++){ 
                    //printf("    data %ld\n",d);
                    Gcouche[c].NG[n].dW[nbEntree[c]]+=Gcouche[c].NG[n].dz[d];
                }
                Gcouche[c].NG[n].dW[nbEntree[c]]=Gcouche[c].NG[n].dW[nbEntree[c]]/(DATATYPE)NBDATA;
            }
        }
        //DEBUG_S("debut premiere couche");
        //printf("couche 0\n");
        //pour la premierre                                 // C=0    
            //dZ(i)=W(i+1)^T*dZ(i+1)*A(i)*(1-A(i))          //dz[C][N]=W[C+1][N]^T*dz[C+1][N]*A[C][N]*(1-A[C][N])
            //dW(i)=1/nbdata*dZ(i)*X^T                      //dw[C][N]=1/((Nbentree[C])*dz[C][N]*X^T)
            //db(i)=1/nbdata*somme(dZ(i))                   //db[C][N]=1/((Nbentree[C])*somme(dz[C][N])
        c=0;
        for (n = 0; n < nbNeurone[c]; n++){ 
            //printf("    neurone %ld\n",n);
            for(d = 0; d < NBDATA; d++){
                //printf("        data %ld\n",d);
                Gcouche[c].NG[n].dz[d]=0;
                for(p = 0; p < nbNeurone[c+1]; p++){ 
                    //printf("            parametre %ld\n",p);
                    Gcouche[c].NG[n].dz[d] += Wcouche[c+1].NW[p].W[n]*Gcouche[c+1].NG[p].dz[d];
                }
                Gcouche[c].NG[n].dz[d]*=Acouche[c].NA[n].A[d]*(1-Acouche[0].NA[n].A[d]);
            }
            for(p = 0; p < NBPARAM; p++){
                //printf("    parametre %ld\n",p);
                Gcouche[c].NG[n].dW[p]=0;
                for(d = 0; d < NBDATA; d++){ 
                    //printf("        data %ld\n",d);
                    Gcouche[c].NG[n].dW[p] += X[p][d]*Gcouche[c].NG[n].dz[d];
                }
                Gcouche[c].NG[n].dW[p]=Gcouche[c].NG[n].dW[p]/(DATATYPE)NBDATA;
            }
            Gcouche[0].NG[n].dW[NBPARAM]=0;
            for(d = 0; d < NBDATA; d++){ 
                //printf("    data %ld\n",d);
                Gcouche[0].NG[n].dW[NBPARAM]+=Gcouche[0].NG[n].dz[d];
            }
            Gcouche[0].NG[n].dW[NBPARAM]=Gcouche[0].NG[n].dW[NBPARAM]/(DATATYPE)NBDATA;
        }
    #else
        //pour la seule et unique couche
            //dZ(i)=A(i)-Y                      //dz[C][N]=A[C][N]-Y[C][N]
            //dW(i)=1/nbdata*dZ(i)*X^T          //dw[C][N]=1/((Nbentree[C])*dz[C][N]*X^T)
            //db(i)=1/nbdata*somme(dZ(i))       //db[C][N]=1/((Nbentree[C])*somme(dz[C][N])
        for (n = 0; n < nbEntree[1]; n++){
            for(d = 0; d < NBDATA; d++){
                Gcouche[0].NG[n].dz[d]=Acouche[0].NA[n].A[d]-Y[d];
            } 
            for(p = 0; p < NBPARAM; p++){
                //printf("    parametre %ld\n",p);
                Gcouche[0].NG[n].dW[p]=0;
                for(d = 0; d < NBDATA; d++){ 
                    //printf("        data %ld\n",d);
                    Gcouche[0].NG[n].dW[p] += X[p][d]*Gcouche[0].NG[n].dz[d];
                }
                Gcouche[0].NG[n].dW[p]/=(DATATYPE)NBDATA;
            }
            Gcouche[0].NG[n].dW[NBPARAM]=0;
            for(d = 0; d < NBDATA; d++) 
                Gcouche[0].NG[n].dW[NBPARAM]+=Gcouche[0].NG[n].dz[d];
            Gcouche[0].NG[n].dW[NBPARAM]/=(DATATYPE)NBDATA;
        }
    #endif
};

void update(layerW_T*Wcouche,layerG_T*Gcouche,const DATATYPE learning_rate){
    for (c = 0; c <NBCOUCHE; c++){
        for (n = 0; n < nbNeurone[c]; n++){ 
            for(p = 0; p < nbEntree[c]; p++){
                Wcouche[c].NW[n].W[p]-=Gcouche[c].NG[n].dW[p]*learning_rate;
            }
            Wcouche[c].NW[n].W[nbEntree[c]]-=Gcouche[c].NG[n].dW[nbEntree[c]]*learning_rate;
        }
    }
};

void artificial_neurone(DATATYPE *LossList,layerW_T*Wcouche,layerA_T*Acouche,layerG_T*Gcouche, const X_t X,const _Bool* Y,const DATATYPE learning_rate,const int n_iter){
    DEBUG_S("début initialisation");
    initialisation(Wcouche,Acouche,Gcouche);
    DEBUG_S("fin initialisation");
    printAll(Wcouche,1,Acouche,PrintGradParam,Gcouche,PrintGradParam,1);
    for(size_t i=0;i<n_iter;i++){
        DEBUG_S1("début forward_propagation iteration:%ld\n",i);
        DEBUG_S1("fin forward_propagation iteration:%ld\n",i);
        forward_propagation(X,Wcouche,Acouche);
        DEBUG_S1("début logloss iteration:%ld\n",i);
        //LossList[i]=log_loss(A,Y);
        if(i%((n_iter/100>0)?n_iter/100:1)==0){
            printf("logloss[%ld]=%f\n",i,log_loss(Acouche,Y));
            printAll(Wcouche,1,Acouche,PrintGradParam,Gcouche,PrintGradParam,1);
        }
        DEBUG_S1("fin logloss iteration:%ld\n",i);
        DEBUG_S1("début back_propagation iteration:%ld\n",i);
        back_propagation(Wcouche,Acouche,Gcouche,X,Y);
        DEBUG_S1("fin back_propagation iteration:%ld\n",i);
        #ifdef DEBUG
            printAll(Wcouche,1,Acouche,PrintGradParam,Gcouche,PrintGradParam,1);
        #endif
        DEBUG_S1("début update iteration:%ld\n",i);
        update(Wcouche,Gcouche,learning_rate);
        DEBUG_S1("fin update iteration:%ld\n",i);
        #ifdef DEBUG
            printAll(Wcouche,1,Acouche,PrintGradParam,Gcouche,PrintGradParam,1);
        #endif
    }
    printAll(Wcouche,1,Acouche,PrintGradParam,Gcouche,PrintGradParam,1);
};
void predict(_Bool *Y,const X_t X,layerA_T *coucheA,layerW_T *coucheW){
    forward_propagation(X,coucheW,coucheA);
    for( d=0;d<NBDATA;d++){
        Y[d]=(coucheA[NBCOUCHE-1].NA[0].A[d]>0.5)?1:0;
    }
};

DATATYPE acurencyScore(const _Bool* Y,const _Bool* Ypredict){
    DATATYPE res=0;
    for(int j=0;j<NBDATA;j++){
        res+=(Y[j]==Ypredict[j]);
    }   
    return res/(DATATYPE)NBDATA;
};