/**
 * @file pile.c
 * @brief fichier d'implementation pour la gestion de pile
 */
 
#include <stdlib.h>
#include "pile.h"

/** TO DO
 * @brief Initialiser une pile du type pile_t
 *   - allocation de memoire pour une structure pile_t et un tableau de taille elements
 * @param [in] taille taille de la pile
 * @return l'adresse de la structure
 */
pile_t * initPile(int taille)
{
    pile_t * retour = NULL;
   
    if(taille){
         
        retour = (pile_t *)malloc(sizeof(pile_t));
        
        if(retour){
            
            retour->base = (eltPile *)malloc(taille*sizeof(eltPile));
            if(retour->base){
                retour->taille=taille;
                retour->sommet=-1;
            } else {
                retour = NULL;
            }
        }
    }
    
    return retour;
}


/** TO DO
 * @brief Liberer les memoires occupees par la pile
 * @param [in, out] adrPtPile l'adresse du pointeur de la structure pile_t
 */
void libererPile(pile_t ** adrPtPile)
{
    if(*adrPtPile){
        free((*adrPtPile)->base);
        free(*adrPtPile);
        *adrPtPile = NULL;
    }    
}


/** TO DO
 * @brief Verifier si la pile est vide (aucun element dans la "base")
 * @param [in] ptPile l'adresse de la structure pile_t
 * @return 1 - vide, ou 0 - non vide
 */
int estVidePile(pile_t * ptPile)
{
    return (ptPile->sommet==-1);
}


/** TO DO
 * @brief Entrer un element dans la pile
 * @param [in, out] ptPile l'adresse de la structure pile_t
 * @param [in] ptVal l'adresse de la valeur a empiler
 * @param [in, out] code : l'adresse du code de sortie
 *                     *code = 0 si reussi
 *                           = 1 si echec
 */
void empiler(pile_t * ptPile, eltPile * ptVal, int * code)
{
    *code = 1;
    
    if(ptPile->sommet<ptPile->taille-1){
        ptPile->sommet+=1;
        ptPile->base[ptPile->sommet]=*ptVal;
        *code=0;
    }
}


/** TO DO
 * @brief Sortir un element de la pile
 * @param [in, out] ptPile l'adresse de la structure pile_t
 * @param [out] ptRes l'adresse de l'element sorti
 * @param [in, out] code : l'adresse du code de sortie
 *                     *code = 0 si reussi
 *                           = 1 si echec
 */
void depiler(pile_t * ptPile, eltPile * ptRes, int * code)
{
    *code = 1;
    if(!estVidePile(ptPile)){
        *ptRes=ptPile->base[ptPile->sommet];
        ptPile->sommet-=1;
        *code=0;
    }
}