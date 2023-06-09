/**
 * @file eltPile.c
 * @brief fichier d'implementation pour la gestion du type des elements de pile
 */
#include <stdio.h>

#include "eltPile.h"

/** TO DO
 * @brief Copier la valeur d'un element dans un autre emplacement
 * @param [in] src l'adresse de l'element a copier
 * @param [in] dest l'adresse de la destination
 */
void copyElt(eltPile * src, eltPile * dest)
{
    dest->adrCell=src->adrCell; //Copie la valeur de l'adresse de cellule de src vers dest
    dest->adrPrec=src->adrPrec; //Copie la valeur de l'adresse précédente de src vers dest
    dest->nbFils_ou_Freres=src->nbFils_ou_Freres; //Copie la valeur du nombre de fils ou frères de src vers dest
}

