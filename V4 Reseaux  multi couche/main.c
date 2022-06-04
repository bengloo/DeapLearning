#include "main.h"
int main(/*int argc, char const *argv[]*/)
{
    dataSet_t dataSet;//data set originel
    X_t X;//data normalisé 
    _Bool Y[NBDATA];//état analysé
    _Bool Ypredict[NBDATA];//état analysé
    DATATYPE loss[NBITER];
    layerW_T Wcouche[NBCOUCHE];
    layerA_T Acouche[NBCOUCHE];
    layerG_T Gcouche[NBCOUCHE];
    #ifdef INITRDM
        srand( time( NULL ) );
    #endif
    integriteeSettings();
    DEBUG_S("début du programme\n");
        genererDataset(dataSet,Y);
        normaliserDataset(X,dataSet);
        #if NBDATA <100000
            afficherDataset(X,dataSet,Y);
        #endif
        DEBUG_S("début artificial neurone\n");
            artificial_neurone(loss,Wcouche,Acouche,Gcouche,X,Y,LEARNINGRATE,NBITER);
        DEBUG_S("fin artificial neurone\n");
        DEBUG_S("début prédiction\n");
            predict(Ypredict,X,Acouche,Wcouche);
        DEBUG_S("fin prédiction\n");
        printf("score:%f %% des predition valide \n",acurencyScore(Y,Ypredict)*100);
        DEBUG_S("\tDebut liberation memoire\n");
            libererModele(Wcouche,Acouche,Gcouche);
        DEBUG_S("\tfin liberation memoire\n");
    DEBUG_S("fin du programme\n");
    return 1;
}
void genererDataset(dataSet_t D,_Bool*Y){
    #ifdef INITRDM 
        for(int d=0;d<NBDATA;d++){
            for(int j=0;j<NBPARAM;j++){
                D[j][d]=(DATASETTYPE)rand()/((DATASETTYPE)RAND_MAX/((DATASETTYPE)BORNEMAX+(DATASETTYPE)BORNEMIN))-(DATASETTYPE)BORNEMIN;
            }
            Y[d]=CRITERE(D[0][d],D[1][d]);
        }
    #else
        int rac =(int)sqrt(NBDATA);//il est preferable de prendre un NBDATA à racine entierre
        printf("rac:%d\n",rac);
        for(int d=0;d<NBDATA;d++){
            D[0][d]=(((DATASETTYPE)(d%rac))/(DATASETTYPE)rac)*(BORNEMAX+BORNEMIN)-BORNEMIN;
            D[1][d]=((DATASETTYPE)(((d/rac))%rac)/(DATASETTYPE)rac)*(BORNEMAX+BORNEMIN)-BORNEMIN;
            Y[d]=CRITERE(D[0][d],D[1][d]);
        }
    #endif 
}
void normaliserDataset(X_t X,dataSet_t D){
    for(int j=0;j<NBPARAM;j++){
        /*DATATYPE bornMin=D[j][0];
        DATATYPE bornMax=D[j][0];
        for(int i=1;i<NBDATA;i++){
           if(D[j][i]>bornMax)bornMax=D[j][i];
           if(D[j][i]<bornMin)bornMin=D[j][i];
        }
        printf("max %f,min %f\n",bornMax,bornMin);*/
        for(int i=0;i<NBDATA;i++){
            X[j][i]=(DATATYPE)(D[j][i]+BORNEMIN)/(DATATYPE)( BORNEMAX+BORNEMIN);
        }
        /*DATATYPE bornMin=X[j][0];
        DATATYPE bornMax=X[j][0];
        for(int i=1;i<NBDATA;i++){
           if(X[j][i]>bornMax)bornMax=X[j][i];
           if(X[j][i]<bornMin)bornMin=X[j][i];
        }
        printf("max %f,min %f\n",bornMax,bornMin);*/
    }
}

void afficherDataset(const X_t X, const dataSet_t dataSet,const _Bool* Y){
    //aficher dataset
        printf("dataset:\n");
        for(int i=0;i<NBPARAM;i++){
            for(int j=0;j<NBDATA;j++){
                printf("%.6f ",dataSet[i][j]);
            }
            printf("\n");
        }
        //aficher X
        printf("X:\n");
        for(int i=0;i<NBPARAM;i++){
            for(int j=0;j<NBDATA;j++){
                printf("%.6f ",X[i][j]);
            }
            printf("\n");
        }
        //aficher Y
        printf("Y:\n");
        for(int i=0;i<NBDATA;i++){
            printf("%d ",Y[i]);
        }
        printf("\n");
}