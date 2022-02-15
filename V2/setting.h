//#define DEBUG //à definir si on veux printf les message de debug attention à la saturation du shell
#define NBPARAM 2 //nombre de parametre ici x et y
#define NBDATA 1000 //nombre de donné traité 
#define LEARNINGRATE 0.001 //pas d'aprentissage
#define NBITER 1000000 //nombre d'iteration
#define DATATYPE double //type de donné traité
#define EPSILLONE DBL_MIN //Borne min du type de donée trété
#define BORNEMAX 1 //borne min du dataset generé
#define BORNEMIN 10 //borne max du dataset generé
#define CRITERE (X[1][i]>X[0][i]*2-1) //critére de teste ici si y>2*x-1 équoition du modéle suposé inconus