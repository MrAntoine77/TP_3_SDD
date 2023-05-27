/**
 * @file arbres_parcours.c
 * @brief fichier d'implementation du module pour le parcours d'arborescence
 */
#include <stdio.h>
#include <stdlib.h>

#include "../pile.h"
#include "../eltsArbre.h"
#include "arbres_parcours.h"


/** TO DO
 * @brief calculer le nombre de fils ou freres d'un point a partir du pointeur du debut de la liste
 * @param [in] ptCell pointeur vers le 1er frere
 * @return le nombre de fils ou freres
 */
int getNbFils_ou_Freres(cell_lvlh_t * ptCell)
{
    int i = 0;
    while(ptCell!=NULL){
        ptCell=ptCell->lh;
        i++;
    }
    return i;
}


/** TO DO
 * @brief parcours en profondeur postfixee
 * @param [in] file le flux de sortie
 * @param [in] racine la racine de l'arborescence
 */
void printPostfixee(FILE *file, cell_lvlh_t *racine)
{
    cell_lvlh_t *ai = racine;
    pile_t *pile = initPile(20);
    int fin = 0; // 0 = faux, 1 = vrai
    while (fin == 0)
    {
        eltPile elem;
        int code;
        while (ai != NULL)
        {
            elem.adrCell=ai;
            empiler(pile, &elem, &code);
            ai = ai->lv;
        }
        if (!estVidePile(pile))
        {
            depiler(pile, &elem, &code);
            ai=elem.adrCell;
            fprintf(file, "(%c,%d) ", ai->val, getNbFils_ou_Freres(ai->lv));
            ai = ai->lh;
        }
        else
        {
            fin = 1;
        }
    }
    fprintf(file, "%d\n",getNbFils_ou_Freres(racine));
    libererPile(&pile);
}
