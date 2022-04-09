//#define DEBUG //à definir si on veux printf les message de debug attention à la saturation du shell


#define NBPARAM 2 //nombre de parametre ici x et y
#define NBDATA 3 //nombre de donné traité 
#define LEARNINGRATE 2 //pas d'aprentissage
#define NBITER 10000 //nombre d'iteration
#define DATASETTYPE float //tipe du data set originel avant normalisation
#define BORNEMAX 100 //borne min du dataset generé
#define BORNEMIN 10 //borne max du dataset generé
#define DATATYPE float //type de donné traité aprés normalisation float ou double
#define EPSILLONE FLT_MIN //Borne min du type de donée traité
#define FONCTION(x) (2*x+10) //équoition du modéle suposé inconus
#define CRITERE(x,y) (y>FONCTION(x)) //critére de teste
#define NBCOUCHE 2 //nombre de couche du reseaux
#ifndef NBENTREE
    #define NBENTREE
    extern int nbEntree[NBCOUCHE+1]={NBPARAM,3,1}; //nombre d'entré par couche et donc nombre de neurone de la couche précedente
#endif