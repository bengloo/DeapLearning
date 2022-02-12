#include <stdlib.h>
#include <string.h>
#include <stdio.h>

#define DATA_NB   10
#define DATA_DIM    2
double X[DATA_NB][DATA_DIM]=
{{0,1},
{1,2},
{2,3},
{3,4},
{4,5},
{5,4},
{4,3},
{3,2},
{2,1},
{1,0}
};

double drand ( double low, double high )
{
    return ( (double)rand() * ( high - low ) ) / (double)RAND_MAX + low;
}

void initialisation(double *w,double *b){
    for(int i=0;i<DATA_NB;i++){
        w[i]=drand(0.0,100.0);
    }
    *b=drand(0.0,100.0);
}
double* model(double* X,double*W,double b){
 //Z=x*w+b
 //A=1/(1+e^-z)
 //return A

}
double log_loss(double* A,double*y){
    //return 1/DATA_NB*sommme(-y*log(A)-(1-y)*log(1-A));
}
double* gradiants(double* A,double *X,double*Y){
    //double* dw=1/DATA_NB*(transpose(x)*(A-y));
    //double db=1/DATA_NB*(A-y);
}

void update(double* dw,double db,double * w, double *b,double learning_rate){
//w=w-learning_rate*dw
//*b=*b-learning_rate*db    
}
void artificial_neuron(double*x,double*y,double learning_rate,int n_iter){
    double w[DATA_DIM];
    double b;
    double Y[DATA_NB];
    initialisation(w,&b);

    for(int i=0;i<n_iter;i++){
        //
    }
}
int main(/*int argc, char const *argv[]*/)
{

    
}
