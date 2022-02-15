#include "neurone.h"

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
        printf("score:%f\n",acurencyScore(Y,Ypredict));
    DEBUG_S("fin du programme\n");
    //system("echo ;ps -eo size,comm | grep -e 'DeepLearning$' -e 'COMMAND$'");
    return 1;
}