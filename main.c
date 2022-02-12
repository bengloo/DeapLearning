#include "main.h"

mat2D_t X;//data utilisé
mat2D_t Y;//état analysé
mat2D_t W;//parametre deaplearning
mat2D_t Z;//modelle neurone
mat2D_t A;//fonction d'activation
DATATYPEMAT2D b;
int main(/*int argc, char const *argv[]*/)
{
    return 0;
}

void initialisation(mat2D_t *W, DATATYPEMAT2D *b,mat2D_t X){
    initRdmMat2d(W,1,X.x);
    *b=(float)rand();
}