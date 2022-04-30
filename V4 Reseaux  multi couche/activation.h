#include "setting.h"
#include <math.h>

//calcule la fonction d'activation sigmoide
DATATYPE sigmoide(DATATYPE x);

//calcule la fonction d'activation Heavyside
DATATYPE heavyside(DATATYPE x);

//calcule la fonction d'activation identitée 
DATATYPE identitee(DATATYPE x);

//calcule la fonction d'activation tanh
//DATATYPE tanh(DATATYPE x); //existe dejas dans math.h

//calcule la fonction d'activation arctan
DATATYPE arctan(DATATYPE x);

//calcule la fonction d'activation signe doux
//DATATYPE signeDoux(DATATYPE x);

//calcule la fonction d'activation Unité de rectification linéaire
DATATYPE RELu(DATATYPE x);

//calcule la fonction d'activation Unité de rectification linéaire paramétrique
DATATYPE PRELu(DATATYPE x, DATATYPE param);

//calcule la fonction d'activation Unité exponentielle linéaire ELU
DATATYPE ELU(DATATYPE x, DATATYPE param);

//calcule la fonction d'activation Unité de rectification linéaire douce softplus
DATATYPE softplus(DATATYPE x);

//calcule la fonction d'activation identitée courbée
DATATYPE identiteeCourbee(DATATYPE x);

//calcule la fonction d'activation Exponentielle douce paramétrique
DATATYPE softExp(DATATYPE x, DATATYPE param);

//calcule la fonction d'activation sinusoïdale
DATATYPE sinusoide(DATATYPE x);

//calcule la fonction d'activation sinusoïde hyperbolique
DATATYPE sinusoideH(DATATYPE x);

//calcule la fonction d'activation gaussienne
DATATYPE gaussienne(DATATYPE x);