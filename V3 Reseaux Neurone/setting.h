//#define DEBUG //à definir si on veux printf les message de debug attention à la saturation du shell
#define NBPARAM 2 //nombre de parametre ici x et y
#define NBDATA 100 //nombre de donné traité 
#define LEARNINGRATE 0.01 //pas d'aprentissage
#define NBITER 1000000 //nombre d'iteration
#define DATASETTYPE double //tupe d u data set originel avant normalisation
#define BORNEMAX 100 //borne min du dataset generé
#define BORNEMIN 10 //borne max du dataset generé
#define DATATYPE double //type de donné traité aprés normalisation float ou double
#define EPSILLONE DBL_MIN //Borne min du type de donée traité
#define CRITERE (D[1][i]>D[0][i]*2) //critére de teste ici si y>2*x-1 équoition du modéle suposé inconus