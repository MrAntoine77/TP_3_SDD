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
         
        retour = (pile_t *)malloc(sizeof(pile_t)); //alloue la mémoire pour la structure
        
        if(retour){
            
            retour->base = (eltPile *)malloc(taille*sizeof(eltPile));
            if(retour->base){
                retour->taille=taille; //initialise la taille de la pilee
                retour->sommet=-1; //initialise le sommet à -1 : pile vide
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
    return (ptPile->sommet==-1); //verifie si le sommet est defini ou pas
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
    
    if(ptPile->sommet<ptPile->taille-1){ //verifie si de l'espace est disponible
        ptPile->sommet+=1; //incremente la valeur du sommet pour indiquer a position de la valeur empilee
        ptPile->base[ptPile->sommet]=*ptVal; //place la valeur pointée par ptVal dans le tableau d'éléments de la pile à la position du sommet
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
    if(!estVidePile(ptPile)){ //si la pile n'est pas vide
        *ptRes=ptPile->base[ptPile->sommet]; //place la valeur en haut de la pile dans l'adresse pointée par ptRes
        ptPile->sommet-=1; //decremente la valeur du sommet pour indiquer la position de la derniere valeur empilee
        *code=0;
    }
}