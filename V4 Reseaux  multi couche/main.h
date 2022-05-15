#include "neurone.h"
#include "setting.h"
/**
 * @brief genere un data set celons une lois Y=1/(1+e^-(W1.X1+W2.X2....+b))>0.5 présumé inconue pour 2 parametre soit la forme x1=a.x2+c
 * 
 * @param X 
 * @param Y 
 */
void genererDataset(dataSet_t D,_Bool*Y);

/**
 * @brief ramene le dataset entre 0 et 1 pour minimisé les efect de bord en +inf -inf 0
 * 
 * @param X 
 */
void normaliserDataset(X_t X,dataSet_t D);

/**
 * @brief affiche le data set brute, normalisé et sa réponse binaire
 * 
 * @param X 
 * @param dataSet 
 * @param Y 
 */
void afficherDataset(const X_t X, const dataSet_t dataSet,const _Bool* Y);