#include "math.h"
#include <math.h>
#include <stdio.h>
#include "debug.h"
#include <time.h>
#define NBPARAM 2
#define NBDATA 1000
#define LEARNINGRATE 0.01
#define NBITER 10000

/**
 * @brief initialise les parametre w et b de manierre random celons les dimennsion de X
 * 
 * @param W //perceptron coef
 * @param b //perceptron offset
 * @param X data
 */
void initialisation(mat2D_t *W, DATATYPEMAT2D *b, mat2D_t X);

/**
 * @brief Z=X*W+b A=1/(1+e^-z) aplique le modéle sur les data et desuit un etat de sortie
 * 
 * @param A % de sortie estimé par sigmoïde
 * @param Z reponse au stimulis cumulé
 * @param X data
 * @param W perceptron coef
 * @param b perceptron offset
 */
void model(mat2D_t * A,mat2D_t*Z,mat2D_t X,mat2D_t W, DATATYPEMAT2D b);

/**
 * @brief évalus la viabilité du modéle.
 * 
 * @param A 
 * @param Y 
 * @return DATATYPEMAT2D 
 */
DATATYPEMAT2D log_loss(mat2D_t A,mat2D_t Y);

/**
 * @brief calcule les ecarts sur chaque parametre
 * 
 * @param dW 
 * @param db 
 * @param A 
 * @param X 
 * @param Y 
 */
void gradiants(mat2D_t*aux1,mat2D_t*dW,DATATYPEMAT2D*db, mat2D_t A,mat2D_t X,mat2D_t Y);

/**
 * @brief met à jour les parametre celons les écarts
 * 
 * @param W 
 * @param b 
 * @param dW 
 * @param db 
 * @param learning_rate pas d'aprentissage entre l'encien et le nouveaux parametre
 */
void update(mat2D_t* aux2,mat2D_t *W,DATATYPEMAT2D *b,mat2D_t dW,DATATYPEMAT2D db,DATATYPEMAT2D learning_rate); 

void artificial_neurone(mat2D_t* A,mat2D_t *Z,mat2D_t*dW ,DATATYPEMAT2D *LossList,mat2D_t *W,DATATYPEMAT2D *b,mat2D_t X,mat2D_t Y,DATATYPEMAT2D learning_rate,int n_iter);
void predict(mat2D_t *A,mat2D_t *Z,mat2D_t *Y,mat2D_t X,mat2D_t W,DATATYPEMAT2D b);
DATATYPEMAT2D acurencyScore(mat2D_t Y,mat2D_t Ypredict);