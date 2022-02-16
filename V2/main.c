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
            artificial_neurone(loss,W,&b,X,Y,LEARNINGRATE,NBITER);
        DEBUG_S("   fin artificial neurone\n");
        DEBUG_S("   début prédiction\n");
            predict(Ypredict,X,W,b);
        DEBUG_S("   fin prédiction\n");
        printf("W:[");
        for(int i=0;i<NBPARAM;i++){
            printf("%f\t",W[i]);
        }
        printf("]\nb=%f\n",b);
        if(NBPARAM==2)printf("Modéle aproché:\ny=-(W[0]*x+b)/W[1]=%fx+%f\n",-W[0]/W[1],-b/W[1]);
        printf("score:%f %% des predition valide \n",acurencyScore(Y,Ypredict)*100);

    DEBUG_S("fin du programme\n");
    return 1;
}
void genererDataset(X_t X,_Bool*Y){
    for(int i=0;i<NBDATA;i++){
        for(int j=0;j<NBPARAM;j++){
            X[j][i]=(DATATYPE)rand()/((DATATYPE)RAND_MAX/BORNEMAX);
        }
        Y[i]=CRITERE;
    }
};
void normaliserDataset(X_t X){

};