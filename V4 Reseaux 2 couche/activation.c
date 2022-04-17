#include "neurone.h"
DATATYPE sigmoide(DATATYPE x){
    return 1/(1+exp(-x));
}