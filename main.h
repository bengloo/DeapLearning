#include "math.h"
#include <stdio.h>

void initialisation(mat2D_t *W, DATATYPEMAT2D *b, mat2D_t X);
void cost(mat2D_t A,mat2D_t Y);
void gradiant(mat2D_t A,mat2D_t X,mat2D_t Y);
void update(mat2D_t *W,DATATYPEMAT2D *b,mat2D_t dW,DATATYPEMAT2D db); 
