#include <math.h>
#include <stdio.h>
#include "debug.h"
#include <time.h>
#include <stdlib.h>
#include <float.h>
#include "setting.h"

/**
 * @brief matrice contenant le data  normalisé  
 * 
 */
typedef DATATYPE X_t[NBPARAM][NBDATA];

/**
 * @brief matrice contenant le data  originel  
 * 
 */
typedef DATASETTYPE dataSet_t[NBPARAM][NBDATA];

/**
 * @brief 
 * 
 */
typedef struct 
{
    DATATYPE *W;
    DATATYPE *dW;
    DATATYPE b;
    DATATYPE db;
    DATATYPE A[NBDATA];
} Neurone_T;

/**
 * @brief 
 * 
 */
typedef struct
{
    Neurone_T * Neurones;
} Couche_T;

/**
 * @brief 
 * 
 * @param ptrN 
 * @param nbE 
 */
void alouerNeurone(Neurone_T *ptrN,int nbE);

/**
 * @brief 
 * 
 * @param ptrC 
 * @param couche 
 */
void alouerCouche(Couche_T *ptrC,int couche);

/**
 * @brief 
 * 
 * @param ptrN 
 */
void libererNeurone(Neurone_T *ptrN);

/**
 * @brief 
 * 
 * @param ptrC 
 * @param nbN 
 */
void libererCouche(Couche_T *ptrC,int nbN);

/**
 * @brief initialise de manierre aleatoire les parametre du modéle W et b
 * 
 * @param W 
 * @param b 
 */
void initialisation(Couche_T*couche);


void forward_propagation(const X_t X,Couche_T*couche);

/**
 * @brief calcule le cout du modéle en comparent A et Y telque: somme(A>0.5==Y)/NBDATA
 * 
 * @param A 
 * @param Y 
 * @return DATATYPE 
 */
DATATYPE log_loss(const DATATYPE* A,const _Bool* Y);
/**
 * @brief calcule des gradiant celons les ecart entre A et Y
 * 
 * @param dW 
 * @param db 
 * @param A 
 * @param X 
 * @param Y 
 */
void back_propagation(Couche_T* couche,const X_t X,const _Bool* Y);

/**
 * @brief mets à jour les parametre en les incrementant par leur gardiant*pas d'aprentissage
 * 
 * @param W 
 * @param b 
 * @param dW 
 * @param db 
 * @param learning_rate 
 */
void update(DATATYPE *W,DATATYPE *b,const DATATYPE* dW,const DATATYPE db,const DATATYPE learning_rate);

/**
 * @brief détermine le modéle d'une neuone(W b) via les data X et etat y retourne  l'evolution du cout dans LoosList
 * 
 * @param LossList 
 * @param W 
 * @param b 
 * @param X 
 * @param Y 
 * @param learning_rate 
 * @param n_iter 
 */
void artificial_neurone(DATATYPE *LossList,Couche_T*couche,const X_t X,const _Bool* Y,const DATATYPE learning_rate,const int n_iter);

/**
 * @brief prédit l'etat en reponse à un modéle pour un data set inconus
 * 
 * @param Y 
 * @param X 
 * @param W 
 * @param b 
 */
void predict(_Bool *Y,const X_t X,const DATATYPE* W,const DATATYPE b);

/**
 * @brief retourne le ratio de similitude entre les etat predit et reel d'un dataset
 * 
 * @param Y 
 * @param Ypredict 
 * @return DATATYPE 
 */
DATATYPE acurencyScore(const _Bool* Y,const _Bool* Ypredict);