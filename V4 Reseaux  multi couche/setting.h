
#define SETINGVERSION 1
//0:settings les plus minimaliste possible
//1:settings minimaliste mais testant quelque couches intermediaires avec un nombre de neurone croissant et décroissant afin de voir si le modéle est stable
//autre:settings complet nombreuse couche,  data et iterations

#if SETINGVERSION==0
    #define DEBUG //à definir si on veux printf les message de debug attention à la saturation du shell
    #define DATASETTYPE float //tipe du data set originel avant normalisation
    #define BORNEMAX 100 //borne min du dataset generé
    #define BORNEMIN 10 //borne max du dataset generé
    #define DATATYPE float //type de donné traité aprés normalisation float ou double
    #define EPSILLONE FLT_MIN //Borne min du type de donée traité
    #define LEARNINGRATE 0.01 //pas d'aprentissage
    #define FONCTION(x1) (x1) //équoition du modéle suposé inconus (frontierre de décision)
    #define CRITERE(x1,x2) (x2>FONCTION(x1)) //critére de teste
    #define NBPARAM 2 //nombre de parametre d'entrée du modéle ici x1 et x2
    #define NBDATA 1 //nombre de donné traité 
    #define NBITER 2 //nombre d'iteration
    #define NBCOUCHE 2 //nombre de couche du reseaux (2 minimum sinon utiliser la V3)
    #define NBENTREE {NBPARAM,1,1} //nombre de neurone par couche / nombre d'entré par neurone nbentre[C+1]=nbneurone[C]
    #define FCTACTIVATION {sigmoide,sigmoide} //fonction d'activation par couche
#elif SETINGVERSION==1
    #define DEBUG //à definir si on veux printf les message de debug attention à la saturation du shell
    #define DATASETTYPE float //tipe du data set originel avant normalisation
    #define BORNEMAX 100 //borne min du dataset generé
    #define BORNEMIN 10 //borne max du dataset generé
    #define DATATYPE float //type de donné traité aprés normalisation float ou double
    #define EPSILLONE FLT_MIN //Borne min du type de donée traité
    #define LEARNINGRATE 0.01 //pas d'aprentissage
    #define FONCTION(x1) (x1) //équoition du modéle suposé inconus (frontierre de décision)
    #define CRITERE(x1,x2) (x2>FONCTION(x1)) //critére de teste
    #define NBPARAM 2 //nombre de parametre d'entrée du modéle ici x1 et x2
    #define NBDATA 3 //nombre de donné traité 
    #define NBITER 4 //nombre d'iteration
    #define NBCOUCHE 4 //nombre de couche du reseaux (2 minimum sinon utiliser la V3)
    #define NBENTREE {NBPARAM,3,2,3,1} //nombre de neurone par couche / nombre d'entré par neurone nbentre[C+1]=nbneurone[C]
    #define FCTACTIVATION {sigmoide,sigmoide,sigmoide,sigmoide} //fonction d'activation par couche
#else
    //#define DEBUG //à definir si on veux printf les message de debug attention à la saturation du shell
    #define DATASETTYPE float //tipe du data set originel avant normalisation
    #define BORNEMAX 100 //borne min du dataset generé
    #define BORNEMIN 10 //borne max du dataset generé
    #define DATATYPE float //type de donné traité aprés normalisation float ou double
    #define EPSILLONE FLT_MIN //Borne min du type de donée traité
    #define LEARNINGRATE 0.01 //pas d'aprentissage
    #define FONCTION(x1) (2*x1+10) //équoition du modéle suposé inconus (frontierre de décision)
    #define CRITERE(x1,x2) (x2>FONCTION(x1)) //critére de teste
    #define NBPARAM 2 //nombre de parametre d'entrée du modéle ici x1 et x2
    #define NBDATA 3000 //nombre de donné traité 
    #define NBITER 10000 //nombre d'iteration
    #define NBCOUCHE 4 //nombre de couche du reseaux (2 minimum sinon utiliser la V3)
    #define NBENTREE {NBPARAM,3,2,3,1} //nombre de neurone par couche / nombre d'entré par neurone nbentre[C+1]=nbneurone[C]
    #define FCTACTIVATION {sigmoide,sigmoide,sigmoide,sigmoide} //fonction d'activation par couche
#endif