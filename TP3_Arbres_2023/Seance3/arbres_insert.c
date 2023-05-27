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
    while(cour != NULL && cour->val != v){
        elem.adrCell=cour;
        empiler(pile, &elem, &code);
        cour=cour->lv;
        while(cour == NULL && !estVidePile(pile)){
            depiler(pile, &elem,&code);
            cour=elem.adrCell;
            cour=cour->lh;
        }
    }
    libererPile(&pile);
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
    cell_lvlh_t ** pprec = &adrPere->lv;
    while((*pprec)->lh!=NULL && (*pprec)->lh->val<w){
        *pprec=(*pprec)->lh;
    }
    return pprec;
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
    printPostfixee(stdout,racine);
    printf("v : %c, w : %c\n",v,w);
    int retour = 0;
    cell_lvlh_t * pere = rechercher_v(racine, v);
    cell_lvlh_t ** pprec;

    if (pere != NULL) {
        pprec = rechercherPrecFilsTries(pere, w);
        printf("TEST : %c\n",(*pprec)->val);

        cell_lvlh_t * nouv = (cell_lvlh_t*)malloc(sizeof(cell_lvlh_t));
        if (nouv != NULL) {
            nouv->val = w;
            nouv->lv = NULL;
            nouv->lh = (*pprec)->lh;
            (*pprec)->lh = nouv;
            retour = 1;
        }
    }
    printPostfixee(stdout,racine);
    return retour;
}
