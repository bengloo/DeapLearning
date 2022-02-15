#include <math.h>
#include <stdio.h>
#include "debug.h"
#include <time.h>
#include <stdlib.h>
#include <float.h>
#include "setting.h"

typedef DATATYPE X_t[NBPARAM][NBDATA];

void genererDataset(X_t X,_Bool*Y);

void initialisation(DATATYPE *W, DATATYPE *b);

void model(DATATYPE * A,X_t X,DATATYPE* W, DATATYPE b);

DATATYPE log_loss(DATATYPE* A,_Bool* Y);

void gradiants(DATATYPE*dW,DATATYPE*db, DATATYPE* A,X_t X,_Bool* Y);

void update(DATATYPE *W,DATATYPE *b,DATATYPE* dW,DATATYPE db,DATATYPE learning_rate);

void artificial_neurone(DATATYPE *LossList,DATATYPE*W,DATATYPE *b,X_t X,_Bool* Y,DATATYPE learning_rate,int n_iter);

void predict(_Bool *Y,X_t X,DATATYPE* W,DATATYPE b);

DATATYPE acurencyScore(_Bool* Y,_Bool* Ypredict);