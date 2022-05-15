
#define SETINGVERSION 1
//0:settings reseaux 1 couche 1 neurone regression d'un systéme lineaire 
    //https://playground.tensorflow.org/#activation=sigmoid&batchSize=30&dataset=circle&regDataset=reg-plane&learningRate=0.1&regularizationRate=0&noise=0&networkShape=1&seed=0.12746&showTestData=false&discretize=false&percTrainData=90&x=true&y=true&xTimesY=false&xSquared=false&ySquared=false&cosX=false&sinX=false&cosY=false&sinY=false&collectStats=false&problem=regression&initZero=false&hideText=false
//autre:settings reseaux 2 couche 1 neurone regression d'un systéme lineaire 
    //https://playground.tensorflow.org/#activation=sigmoid&batchSize=30&dataset=circle&regDataset=reg-plane&learningRate=0.1&regularizationRate=0&noise=0&networkShape=1,1&seed=0.12746&showTestData=false&discretize=false&percTrainData=90&x=true&y=true&xTimesY=false&xSquared=false&ySquared=false&cosX=false&sinX=false&cosY=false&sinY=false&collectStats=false&problem=regression&initZero=false&hideText=false

#if SETINGVERSION==0
    //#define DEBUG //à definir si on veux printf les message de debug attention à la saturation du shell
    #define INITRDM  //la generation du dataset et des parametre sont soit aleatoir soit uniforme (pour NBPARAM=2)
    #define DATASETTYPE float //tipe du data set originel avant normalisation
    #define BORNEMAX    100 //borne min du dataset generé
    #define BORNEMIN    10//borne max du dataset generé
    #define DATATYPE    float //type de donné traité aprés normalisation float ou double
    #define EPSILLONE   FLT_MIN //Borne min du type de donée traité
    #define LEARNINGRATE 0.1 //pas d'aprentissage
    #define FONCTION(x1) (x1) //équoition du modéle suposé inconus (frontierre de décision)
    #define CRITERE(x1,x2) (x2>FONCTION(x1)) //critére de teste
    #define NBPARAM 2 //nombre de parametre d'entrée du modéle ici x1 et x2
    #define NBDATA  3000 //nombre de donné traité 
    #define NBITER  1000 //nombre d'iteration
    #define NBCOUCHE 1 //nombre de couche du reseaux (2 minimum sinon utiliser la V3)
    #define NBENTREE {NBPARAM,1} //nombre de neurone par couche / nombre d'entré par neurone nbentre[C+1]=nbneurone[C]
    #define FCTACTIVATION {sigmoide} //fonction d'activation par couche
    #define PrintGradParam 0
#else
    #define DEBUG //à definir si on veux printf les message de debug attention à la saturation du shell
    //#define INITRDM  //la generation du dataset et des parametre sont soit aleatoir soit uniforme (pour NBPARAM=2)
    #define DATASETTYPE float //tipe du data set originel avant normalisation
    #define BORNEMAX    100 //borne min du dataset generé
    #define BORNEMIN    10//borne max du dataset generé
    #define DATATYPE    float //type de donné traité aprés normalisation float ou double
    #define EPSILLONE   FLT_MIN //Borne min du type de donée traité
    #define LEARNINGRATE 0.1 //pas d'aprentissage
    #define FONCTION(x1) (x1) //équoition du modéle suposé inconus (frontierre de décision)
    #define CRITERE(x1,x2) (x2>FONCTION(x1)) //critére de teste
    #define NBPARAM 2 //nombre de parametre d'entrée du modéle ici x1 et x2
    #define NBDATA  9 //nombre de donné traité 
    #define NBITER  3 //nombre d'iteration
    #define NBCOUCHE 2 //nombre de couche du reseaux (2 minimum sinon utiliser la V3)
    #define NBENTREE {NBPARAM,1,1} //nombre de neurone par couche / nombre d'entré par neurone nbentre[C+1]=nbneurone[C]
    #define FCTACTIVATION {sigmoide,sigmoide} //fonction d'activation par couche
    #define PrintGradParam 1
#endif