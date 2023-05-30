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
    fichier=fopen(fileName,"r"); //Ouvre le fichier en mode lecture ("r")
    int nbRacine = 0;

    if(fichier){

        fscanf(fichier,"%d ",&nbRacine); //Lit la valeur de la racine à partir du fichier

        while(!feof(fichier)){ //Continue la boucle jusqu'à la fin du fichier

            fscanf(fichier,"%c %d ",&tabEltsPref[*nbEltsPref].val,&tabEltsPref[*nbEltsPref].nbFils); //Lit les valeurs de la structure eltPrefPostFixee_t à partir du fichier
            //et les stocke dans le tableau tabEltsPref
            (*nbEltsPref)+=1; //Incrémente le nombre d'éléments de la representation après chaque lecture
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

    for (i = 0; i < nbEltsPref; i++) //On boucle sur le nombre d'éléments
    {
        //On affiche de la bonne manière les éléments
        if(i != nbEltsPref-1){

            fprintf(file,"(%c,%d) ",tabEltPref[i].val,tabEltPref[i].nbFils);
        }
        else{

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

    cell_lvlh_t *newPoint = (cell_lvlh_t*)malloc(sizeof(cell_lvlh_t)); //Alloue de la mémoire pour une nouvelle structure cell_lvlh_t

    if (newPoint == NULL) {

        printf("Erreur : allocation de memoire impossible.\n");
        exit(1);
    }
    
    // Initialise les champs de la structure avec la valeur spécifiée ou par NULL :
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
    cell_lvlh_t * nouv;
    eltPrefPostFixee_t * cour=tabEltPref;
    cell_lvlh_t ** prec=&tete;
    int nbFof=nbRacines;
    int i=0, code;
    eltPile elem;

    while(nbFof>0 || !estVidePile(pile)) //Continue la boucle tant que nbFof est supérieur à 0 ou la pile n'est pas vide
    {
        if(nbFof>0){ 

            nouv = allocPoint(cour[i].val); //Alloue une nouvelle structure cell_lvlh_t avec la valeur courante de tabEltPref
            *prec=nouv; //Affecte la nouvelle structure à l'adresse pointée par prec
            elem.nbFils_ou_Freres=nbFof-1; //Initialise les champs nbFils_ou_Freres et adrPrec de la structure eltPile
            elem.adrPrec=&nouv->lh; 
            empiler(pile, &elem, &code); //On empile ces informations
            prec=&nouv->lv; //Met à jour prec pour pointer vers le champ du fils de la nouvelle structure
            nbFof=cour[i].nbFils;  //Met à jour nbFof avec le nombre de fils de la valeur courante de tabEltPref
            i++;

        } else {  //Si nbFof est égal à 0 et la pile n'est pas vide
            if (!estVidePile(pile)){

                depiler(pile, &elem,&code);
                prec=elem.adrPrec; //Met à jour prec avec la valeur de adrPrec de la structure défilée
                nbFof=elem.nbFils_ou_Freres; //Met à jour nbFof avec la valeur de nbFils_ou_Freres de la structure défilée
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

    cell_lvlh_t * cour = *adrPtRacine; //Initialise un pointeur cour avec la valeur de la racine
    cell_lvlh_t * prec;
    pile_t * pile = initPile(20);
    eltPile elem;
    int code;

    while(cour != NULL){ //Continue la boucle tant que cour n'est pas NULL

        elem.adrCell=cour->lh; //Affecte la valeur de cour au champ adrCell de la structure elem
        empiler(pile, &elem, &code); //On empile cette information
        prec=cour; //Affecte la valeur de cour à prec
        cour=cour->lv; //On avance vers le fils
        

        while(cour == NULL && !estVidePile(pile)){ //Continue la boucle tant que cour est NULL et la pile n'est pas vide
            depiler(pile, &elem,&code);
            cour=elem.adrCell; //Met à jour cour avec la valeur de adrCell de la structure défilée            
        }
        free(prec);

        
    }
    libererPile(&pile); //Libère la mémoire allouée pour la pile



    
}