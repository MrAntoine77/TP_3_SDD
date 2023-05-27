/**
 * @file arbres_construct.c
 * @brief fichier d'implementation du programme pour la construction d'une arborescence
 */
#include <stdio.h>
#include <stdlib.h>

#include "../pile.h"
#include "../eltsArbre.h"
#include "arbres_construct.h"

/**
 * @brief lire le fichier contenant la representation prefixee de l'arborescence
 * @param [in] fileName le nom du fichier contenant la representation prefixee
 * @param [in, out] tabEltPref tableau des elements de la representation prefixee
 * @param [in, out] nbEltsPref l'adresse memoire contenant le nombre des elements du tabEltPref
 * @return le nombre de racines
 */
int lirePref_fromFileName(char *fileName, eltPrefPostFixee_t *tabEltsPref, int *nbEltsPref){
    FILE * fichier;
    fichier=fopen(fileName,"r");
    int nbRacine;

    if(fichier){
        fscanf(fichier,"%d ",&nbRacine);
        while(!feof(fichier)){
            
            fscanf(fichier,"%c %d ",&tabEltsPref[*nbEltsPref].val,&tabEltsPref[*nbEltsPref].nbFils);
            (*nbEltsPref)+=1;
        }
        
        fclose(fichier);
    }
    return nbRacine;
}

/** TO DO
 * @brief afficher les elements de la representation prefixee sur un flux de sortie
 * @param file : le flux de sortie
 * @param [in, out] tabEltPref tableau des elements de la representation prefixee
 * @param [in, out] nbEltsPref le nombre des elements du tabEltPref
 */
void printTabEltPref(FILE * file, eltPrefPostFixee_t * tabEltPref, int nbEltsPref){
    int i;
    for (i = 0; i < nbEltsPref; i++)
    {
        if(i!=nbEltsPref-1){
            fprintf(file,"(%c,%d) ",tabEltPref[i].val,tabEltPref[i].nbFils);
        }else{
            fprintf(file,"(%c,%d)",tabEltPref[i].val,tabEltPref[i].nbFils);
        }
    }
    fprintf(file,"\n");
}


/** TO DO
 * @brief creer et initialiser un nouveau point de l'arborescence
 * @param [in] val la valeur du point
 * @return l'adresse du nouveau point 
 */
 
cell_lvlh_t *allocPoint(char val) {

    cell_lvlh_t *newPoint = (cell_lvlh_t*)malloc(sizeof(cell_lvlh_t));
    if (newPoint == NULL) {
        printf("Erreur : allocation de memoire impossible.\n");
        exit(1);
    }
    
    newPoint->val = val;
    newPoint->lv = NULL;
    newPoint->lh = NULL;

    return newPoint;
}

/** TO DO
 * @brief construire un arbre avec lvlh a partir de representation prefixee
 * @param [in] tabEltPref tableau des elements de la representation prefixee
 * @param [in] nbRacines nombre de racines de l'arborescence
 * @return : 
 *     - NULL si l'arbre resultatnt est vide
 *     - l'adresse de la racine de l'arbre sinon
*/
cell_lvlh_t *pref2lvlh(eltPrefPostFixee_t * tabEltPref, int nbRacines) {
    pile_t * pile = initPile(20);
    cell_lvlh_t * tete = NULL;
    eltPrefPostFixee_t * cour=tabEltPref;
    cell_lvlh_t ** prec=&tete;
    int nbFof=nbRacines;
    int i=0;
    while(nbFof>0 || !estVidePile(pile))
    {
        int code;
        eltPile elem;
        if(nbFof>0){ 
            cell_lvlh_t * nouv = allocPoint(cour[i].val);
            *prec=nouv;
            elem.nbFils_ou_Freres=nbFof-1;
            elem.adrPrec=&nouv->lh;
            empiler(pile, &elem, &code);
            
            prec=&nouv->lv;
            nbFof=cour[i].nbFils;

            i++;
        } else {
            if (!estVidePile(pile)){
                depiler(pile, &elem,&code);
                prec=elem.adrPrec;
                nbFof=elem.nbFils_ou_Freres;
            }
        }   
    } 
    libererPile(&pile);
    return tete;
}


/** TO DO
 * @brief liberer les blocs memoire d'un arbre
 * @param [in] adrPtRacine l'adresse du pointeur de la racine d'un arbre
 */
void libererArbre(cell_lvlh_t ** adrPtRacine)
{

    cell_lvlh_t * cour = *adrPtRacine;
    cell_lvlh_t * prec;
    pile_t * pile = initPile(20);
    eltPile elem;
    int code;
    while(cour != NULL){
        elem.adrCell=cour;
        empiler(pile, &elem, &code);
        prec=cour;
        cour=cour->lv;
        free(prec);
        while(cour == NULL && !estVidePile(pile)){
            depiler(pile, &elem,&code);
            cour=elem.adrCell;
            cour=cour->lh;
        }
    }
    libererPile(&pile);
}