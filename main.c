#include "main.h"
#include <math.h>

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
void model(mat2D_t * A,mat2D_t*Z,mat2D_t X,mat2D_t W, DATATYPEMAT2D b){
    //Z=X*W+b
    productMat2d(Z,W,X);
    addConstMat2d(Z,*Z,b);
    //A=sigmoïde(Z)
    sigmoidMat2d(A,*Z);
}

DATATYPEMAT2D log_loss(mat2D_t A,mat2D_t Y){
    if(A.x!=0||Y.x!=0||A.y!=Y.y){
        DEBUG_S("dimenssion incompatible log_loss\n");
        return 0;
    };

    DATATYPEMAT2D res=0;
    for(int i=0;i<Y.y;i++){
        res+= -Y.mat[0][i]*log(A.mat[0][i])-(1-Y.mat[0][i])*log(1-A.mat[0][i]);
    }
    return res*1/Y.y;
}

void gradiant(DATATYPEMAT2D*dW,DATATYPEMAT2D*db, mat2D_t A,mat2D_t X,mat2D_t Y){
    mat2D_t aux1;
    mat2D_t aux2;
    initNullMat2d(&aux1);
    initNullMat2d(&aux2);
    
}