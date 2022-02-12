#include "math.h"
#include <stdio.h>
/**
 * @brief initialise les parametre w et b de manierre random celons les dimennsion de X
 * 
 * @param W //perceptron coef
 * @param b //perceptron offset
 * @param X data
 */
void initialisation(mat2D_t *W, DATATYPEMAT2D *b, mat2D_t X);

/**
 * @brief Z=X*W+b A=1/(1+e^-z)
 * 
 * @param A % de sortie estimé par sigmoïde
 * @param Z reponse au stimulis cumulé
 * @param X data
 * @param W perceptron coef
 * @param b perceptron offset
 */
void model(mat2D_t * A,mat2D_t*Z,mat2D_t X,mat2D_t W, DATATYPEMAT2D b);
void cost(mat2D_t A,mat2D_t Y);
void gradiant(mat2D_t A,mat2D_t X,mat2D_t Y);
void update(mat2D_t *W,DATATYPEMAT2D *b,mat2D_t dW,DATATYPEMAT2D db); 
