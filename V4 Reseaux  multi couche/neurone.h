#include <math.h>
#include <stdio.h>
#include "debug.h"
#include <time.h>
#include <stdlib.h>
#include <float.h>
#include "setting.h"
#include "activation.h"

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
 * @brief  matrice contenant les poids de chaque entrée pour une neurone W[nbentree] est biase
 * 
 */

typedef struct 
{
    DATATYPE *W;
} W_T;

/**
 * @brief matice contenant l'activation calculé pour chaque data pour une neurone
 * 
 */
typedef struct 
{
    DATATYPE A[NBDATA];
} A_T;

/**
 * @brief matice contenant les gradient d'une neurone
 */
typedef struct 
{
    DATATYPE dz[NBDATA];
    DATATYPE *dW;
} G_T;

/**
 * @brief parametre des neurones d'une couche
 * 
 */
typedef struct
{
    W_T * NW;
} layerW_T;

/**
 * @brief activations des neurones d'une couche et fonction d'activation associé
 * 
 */
typedef struct
{
    A_T *NA;
    DATATYPE (*pfActivation)(DATATYPE);

} layerA_T;

/**
 * @brief gradiants des neurones d'une couche
 * 
 */
typedef struct
{
    G_T *NG;
} layerG_T;

/**
 * @brief  alocation dynamique des parametres  d'une neurone
 * 
 * @param ptrN 
 * @param nbE 
 */
void alouerNeuroneW(W_T *ptrN,int nbE);

/**
 * @brief alocation dynamique des activations  d'une couche
 * 
 * @param ptrC 
 * @param couche 
 */
void alouerCoucheA(layerA_T *ptrC,int couche);

/**
 * @brief alocation dynamique des parametres  d'une couche
 * 
 * @param ptrC 
 * @param couche 
 */
void alouerCoucheW(layerW_T *ptrC,int couche);

/**
 * @brief alocation dynamique des gradiants  d'une couche
 * 
 * @param ptrC 
 * @param couche 
 */
void alouerCoucheG(layerG_T *ptrC,int couche);

/**
 * @brief libération dynamique des parametres  d'une neurone
 * 
 * @param ptrN 
 */
void libererNeuroneW(W_T *ptrN);

/**
 * @brief libération dynamique des activations  d'une couche
 * 
 * @param ptrC 
 */
void libererCoucheA(layerA_T *ptrC);

/**
 * @brief libération dynamique des activations d'une couche
 * 
 * @param ptrC 
 */
void libererNeuroneA(layerA_T *ptrC);

/**
 * @brief libération dynamique des gradiants  d'une neurone
 * 
 * @param ptrN 
 */
void libererNeuroneG(G_T *ptrN);


/**
 * @brief libération dynamique des parametres  d'une couche
 * 
 * @param ptrC 
 * @param nbN 
 */
void libererCoucheW(layerW_T *ptrC);

/**
 * @brief libération dynamique des parametres  d'une couche
 * 
 * @param ptrC 
 * @param nbN 
 */
void libererCoucheG(layerG_T *ptrC);

/**
 * @brief libération dynamique du modéle complet
 * 
 * @param Wcouche 
 * @param Acouche 
 * @param Gcouche 
 */
void libererModele(layerW_T *Wcouche,layerA_T*Acouche,layerG_T*Gcouche);

/**
 * @brief calule recursivment la réponse du modéle à un data
 * 
 * @param nA 
 * @param cA 
 * @param Acouche 
 * @param Wcouche 
 * @param X 
 * @param dA 
 * @return DATATYPE 
 */
DATATYPE activation(size_t nA,size_t cA,const layerA_T *Acouche,const layerW_T *Wcouche,const X_t X,size_t dA);

/**
 * @brief initialise de manierre aleatoire les parametre du modéle W et b
 * 
 * @param W 
 * @param A
 */
void initialisation(layerW_T*Wcouche,layerA_T*Acouche,layerG_T*Gcouche);

/**
 * @brief affiche les parametre du modéle 
 * 
 * @param couche 
 */
void printParam(layerW_T *couche);

/**
 * @brief affiche les gradiant du modéle
 * 
 * @param couche 
 */
void printGradiant(layerG_T *couche);

/**
 * @brief 
 * 
 * @param X 
 * @param couche 
 * @param Acouche 
 */
void forward_propagation(const X_t X,layerW_T*couche,layerA_T *Acouche);

/**
 * @brief calcule le cout du modéle en comparent l'activation de la dernierre couche et Y telque: somme(A>0.5==Y)/NBDATA
 * 
 * @param coucheA 
 * @param Y 
 * @return DATATYPE 
 */
DATATYPE log_loss(const layerA_T* coucheA,const _Bool* Y);

/**
 * @brief calcule des gradiant celons les ecart entre A et Y
 * 
 * @param dW 
 * @param db 
 * @param A 
 * @param X 
 * @param Y 
 */
void back_propagation(layerW_T* Wcouche,layerA_T* Acouche,layerG_T* Gcouche,const X_t X,const _Bool* Y);

/**
 * @brief mets à jour les parametre en les incrementant par leur gardiant*pas d'aprentissage
 * 
 * @param W 
 * @param b 
 * @param dW 
 * @param db 
 * @param learning_rate 
 */
void update(layerW_T*Wcouche,layerG_T*Gcouche,const DATATYPE learning_rate);

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
void artificial_neurone(DATATYPE *LossList,layerW_T*Wcouche,layerA_T*Acouche,layerG_T*Gcouche,const X_t X,const _Bool* Y,const DATATYPE learning_rate,const int n_iter);

/**
 * @brief prédit l'etat en reponse à un modéle pour un data set inconus
 * 
 * @param Y 
 * @param X 
 * @param W 
 * @param b 
 */
void predict(_Bool *Y,const X_t X,layerA_T *coucheA,layerW_T *coucheW);

/**
 * @brief retourne le ratio de similitude entre les etat predit et reel d'un dataset
 * 
 * @param Y 
 * @param Ypredict 
 * @return DATATYPE 
 */
DATATYPE acurencyScore(const _Bool* Y,const _Bool* Ypredict);

