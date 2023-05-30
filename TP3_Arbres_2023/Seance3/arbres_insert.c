/**
 * @file arbres_insert.c
 * @brief fichier d'implementation du module pour l'insertion de valeur dans une arborescence
 */
#include <stdio.h>
#include <stdlib.h>

#include "../pile.h"
#include "../eltsArbre.h"
#include "arbres_insert.h"
#include "../Seance1/arbres_construct.h"

#include "../Seance2/arbres_parcours.h"


/**
 * @brief rechercher un point de valeur v
 * @param [in] racine pointeur vers la racine de l'arborescence 
 * @return 
 *   - l'adresse du point contenant v si v existe dans l'arborescence
 *   - NULL, sinon
 */
cell_lvlh_t * rechercher_v(cell_lvlh_t * racine, char v)
{
    cell_lvlh_t * cour = racine;
    pile_t * pile = initPile(20);
    eltPile elem;
    int code;

    while(cour != NULL && cour->val != v){ //Continue la boucle tant que cour n'est pas NULL et la valeur de cour est différente de v

        elem.adrCell=cour; //Affecte la valeur de cour au champ adrCell de la structure elem
        empiler(pile, &elem, &code); //On empile ces informations
        cour=cour->lv; //On passe au fils

        while(cour == NULL && !estVidePile(pile)){

            depiler(pile, &elem,&code); //On depile une information
            cour=elem.adrCell; //Met à jour cour avec la valeur de adrCell de la structure défilée
            cour=cour->lh; //On passe au frère
        }
    }

    libererPile(&pile);  //Libère la mémoire allouée pour la pile
    return cour;
}

/**
 * @brief rechercher le double prec de w dans une liste de fils
 * @param [in] adrPere l'adresse du pere
 * @param [in] w la valeur a inserer
 * @return l'adresse du pointeur prec apres lequel w doit etre inseree
 */
cell_lvlh_t ** rechercherPrecFilsTries(cell_lvlh_t * adrPere, char w)
{
    cell_lvlh_t ** pprec;// = (cell_lvlh_t**)malloc(sizeof(cell_lvlh_t*)); //Alloue de la mémoire pour un pointeur de pointeur pprec

    pprec = &(adrPere->lv); // Affecte le pointeur lv du père à la valeur du pointeur de pointeur
    while((*pprec) != NULL && (*pprec)->val < w){ //Continue la boucle tant que la cellule suivante frère n'est pas NULL et la valeur de cette cellule est inférieure à w
        pprec=&((*pprec)->lh); //On passe au frère suivant
    }
   
    return pprec; //Retourne le pointeur de pointeur vers la cellule précédente du fils trié
}

/** TO DO
 * @brief inserer une valeur w dans les fils d'un point de valeur v
 * @param [in] racine la racine de l'arborescence
 * @param [in] v la valeur d'un point auquel on va inserer la valeur w en fils
 * @param [in] w la valeur a inserer
 * @return 1 - insertion realisee; 0 - insertion n'a pas ete realisee
 */
int insererTrie(cell_lvlh_t * racine, char v, char w)
{
    int retour = 0;
    cell_lvlh_t * pere = rechercher_v(racine, v); // Recherche le pointeur vers le père correspondant à la valeur v en utilisant la fonction rechercher_v
    cell_lvlh_t ** pprec;
    cell_lvlh_t * nouv;

    if (pere != NULL) { // Vérifie si le père a été trouvé

        pprec = rechercherPrecFilsTries(pere, w); // Recherche la position d'insertion triée pour la nouvelle cellule en utilisant la fonction rechercherPrecFilsTries
        nouv = (cell_lvlh_t*)malloc(sizeof(cell_lvlh_t)); // Alloue de la mémoire pour une nouvelle cellule

        if (nouv != NULL) { // Vérifie si l'allocation de mémoire a réussi

            nouv->val = w;  // Affecte la valeur w à la nouvelle cellule
            nouv->lv = NULL;
            nouv->lh = (*pprec); // Initialise le champ lh de la nouvelle cellule avec la cellule suivante frère de la position d'insertion
            (*pprec) = nouv; //Met à jour le champ lh de la cellule précédente pour pointer vers la nouvelle cellule
            retour = 1;
        }
    }

    return retour;
}
