#include <stdlib.h>
typedef struct 
{
    int x;
    int y;
    float **mat;
}mat2D_t;

int productMat2d(mat2D_t * matDest,mat2D_t matFrst,mat2D_t matScd);
void initMat2D(mat2D_t* mat);

