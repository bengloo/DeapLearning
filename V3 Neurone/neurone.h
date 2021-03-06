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
 * @brief initialise de manierre aleatoire les parametre du modéle W et b
 * 
 * @param W 
 * @param b 
 */
void initialisation(DATATYPE *W, DATATYPE *b);

/**
 * @brief calcule la réponse A au modéle(W b) à partire du dataset X
 * 
 * @param A 
 * @param X 
 * @param W 
 * @param b 
 */
void model(DATATYPE * A,const X_t X,const DATATYPE* W,const DATATYPE b);

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
void gradiants(DATATYPE*dW,DATATYPE*db,const DATATYPE* A,const X_t X,const _Bool* Y);

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
void artificial_neurone(DATATYPE *LossList,DATATYPE*W,DATATYPE *b,const X_t X,const _Bool* Y,const DATATYPE learning_rate,const int n_iter);

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