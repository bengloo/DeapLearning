#include "activation.h"
#include <math.h>

DATATYPE sigmoide(DATATYPE x){
    return 1/(1+exp(-x));
}

DATATYPE heavyside(DATATYPE x){
    if(x>0)
        return 1;
    else
        return 0;
}

DATATYPE identité(DATATYPE x){
    return x;
}

DATATYPE tanh(DATATYPE x){
    return tanh(x);
}

DATATYPE arctan(DATATYPE x){
    return atan(x);
}

DATATYPE signeDoux(DATATYPE x){
    return x/(1+abs(x));
}

DATATYPE RELu(DATATYPE x){
    if(x>0)
        return x;
    else
        return 0;
}

DATATYPE PRELu(DATATYPE x, DATATYPE param){
    if(x>=0)
        return x;
    else
        return param*x;
}

DATATYPE ELU(DATATYPE x, DATATYPE param){
    if(x>=0)
        return x;
    else
        return param*(exp(x)-1);
}

DATATYPE softplus(DATATYPE x){
    return log(1+exp(x));
}

DATATYPE identitéCourbée(DATATYPE x){
    return (sqrt(1+x*x)-1)/2+x;
}

DATATYPE softExp(DATATYPE x, DATATYPE param){
    if (x<0)
        return -log(1-param*(x+param))/param;      
    else if (x=0)
        return x;
    else 
        return (exp(param*x)-1)/param;
}

DATATYPE sinusoide(DATATYPE x){
    return sin(x);
}

DATATYPE sinusoideH(DATATYPE x){
    if(x=0)
        return 1;
    else
        return sin(x)/x;
} 

DATATYPE gaussienne(DATATYPE x){
    return exp(-x*x);
}
