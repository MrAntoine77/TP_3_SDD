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

    while(ptCell!=NULL){ // Continue la boucle tant que ptCell n'est pas NULL

        ptCell=ptCell->lh; // On avance vers le frere
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
    int code;
    eltPile elem;

    while (fin == 0) //Continue la boucle tant que fin est égal à 0
    {
        while (ai != NULL) //Continue la boucle tant que ai n'est pas NULL
        {
            elem.adrCell=ai; //Affecte la valeur de ai au champ adrCell de la structure elem
            empiler(pile, &elem, &code); //On empile ces informations
            ai = ai->lv; //On passe au fils
        }

        if (!estVidePile(pile)) //Si la pile n'est pas vide
        {
            depiler(pile, &elem, &code); //On dépile
            ai=elem.adrCell; //Met à jour ai avec la valeur de adrCell de la structure défilée
            fprintf(file, "(%c,%d) ", ai->val, getNbFils_ou_Freres(ai->lv)); // Écrit dans le flux la valeur et le nombre de frères ou fils de la cellule courante
            ai = ai->lh; //On passe au frère
        }
        else
        {
            fin = 1; //Met fin à 1 pour terminer la boucle
        }
    }

    fprintf(file, "%d\n",getNbFils_ou_Freres(racine)); //Écrit dans le fichier le nombre total de frères ou fils de la racine
    libererPile(&pile); //Libère la mémoire allouée pour la pile
}
