#include "main.h"
int main(/*int argc, char const *argv[]*/)
{
    dataSet_t dataSet;//data set originel
    X_t X;//data normalisé 
    _Bool Y[NBDATA];//état analysé
    _Bool Ypredict[NBDATA];//état analysé
    DATATYPE loss[NBITER];
    Couche_T couche[NBCOUCHE];
    DEBUG_S("début du programme\n");
        genererDataset(dataSet,Y);
        normaliserDataset(X,dataSet);
        DEBUG_S("   début artificial neurone\n");
            artificial_neurone(loss,couche,X,Y,LEARNINGRATE,NBITER);
        DEBUG_S("   fin artificial neurone\n");
        /*DEBUG_S("   début prédiction\n");
            predict(Ypredict,X,W,b);
        DEBUG_S("   fin prédiction\n");
        printf("W:[");
        for(int i=0;i<NBPARAM;i++){
            printf("%f  ",W[i]);
        }
        printf("]\nb=%f\n",b);
        if(NBPARAM==2)printf("Modéle aproché:\ny=%fx+%f\n",-W[0]/W[1],-(b/W[1])*(BORNEMAX+BORNEMIN)-BORNEMIN*(1+W[0]/W[1]));
        printf("score:%f %% des predition valide \n",acurencyScore(Y,Ypredict)*100);
        */
       //libererCouche(&couche[0],3);
       //libererCouche(&couche[1],1);
    DEBUG_S("fin du programme\n");
    return 1;
}
void genererDataset(dataSet_t D,_Bool*Y){
    for(int i=0;i<NBDATA;i++){
        for(int j=0;j<NBPARAM;j++){
            D[j][i]=(DATASETTYPE)rand()/((DATASETTYPE)RAND_MAX/((DATASETTYPE)BORNEMAX+(DATASETTYPE)BORNEMIN))-(DATASETTYPE)BORNEMIN;
        }
        Y[i]=CRITERE(D[0][i],D[1][i]);
    }
};
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
            //X[j][i]=(DATATYPE)(D[j][i]-bornMin)/(DATATYPE)(bornMax+bornMin);
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
};