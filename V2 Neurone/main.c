#include "main.h"

int main(/*int argc, char const *argv[]*/)
{
    dataSet_t dataSet;//data set originel
    X_t X;//data normalisé 
    _Bool Y[NBDATA];//état analysé
    _Bool Ypredict[NBDATA];//état analysé
    DATATYPE W[NBPARAM];//parametre deaplearning
    DATATYPE loss[NBITER];
    DATATYPE b;

    DEBUG_S("début du programme\n");
        genererDataset(dataSet,Y);
        normaliserDataset(X,dataSet);
        DEBUG_S("   début artificial neurone\n");
            artificial_neurone(loss,W,&b,X,Y,LEARNINGRATE,NBITER);
        DEBUG_S("   fin artificial neurone\n");
        DEBUG_S("   début prédiction\n");
            predict(Ypredict,X,W,b);
        DEBUG_S("   fin prédiction\n");
        printf("W:[");
        for(int i=0;i<NBPARAM;i++){
            printf("%f  ",W[i]);
        }
        printf("]\nb=%f\n",b);
        if(NBPARAM==2)printf("Modéle aproché:\ny=-(W[0]*x+b)/W[1]=%fx+%f\n",-W[0]/W[1],-b/W[1]);
        printf("score:%f %% des predition valide \n",acurencyScore(Y,Ypredict)*100);

    DEBUG_S("fin du programme\n");
    return 1;
}
void genererDataset(dataSet_t D,_Bool*Y){
    for(int i=0;i<NBDATA;i++){
        for(int j=0;j<NBPARAM;j++){
            D[j][i]=(DATASETTYPE)rand()/((DATASETTYPE)RAND_MAX/((DATASETTYPE)BORNEMAX-(DATASETTYPE)BORNEMIN))-(DATASETTYPE)BORNEMIN;
        }
        Y[i]=CRITERE;
    }
};
void normaliserDataset(X_t X,dataSet_t D){
    for(int i=0;i<NBDATA;i++){
        for(int j=0;j<NBPARAM;j++){
            X[j][i]=(DATATYPE)(D[j][i]-BORNEMIN)/(DATATYPE)(BORNEMAX-BORNEMIN);
        }
    }
};