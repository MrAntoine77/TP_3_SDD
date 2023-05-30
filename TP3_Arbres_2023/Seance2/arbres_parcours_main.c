/**
 * program for general linked list testing
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../pile.h"
#include "../eltsArbre.h"
#include "../Seance1/arbres_construct.h"
#include "arbres_parcours.h"
#include "../teZZt.h"


BEGIN_TEST_GROUP(ARBRE_PARCOURS)

TEST(nouvCell) {
	cell_lvlh_t *new;

	new = allocPoint('A');
	REQUIRE( NULL != new ); 
	CHECK( 'A' == new->val );
	CHECK( NULL == new->lv );
	CHECK( NULL == new->lh );

	free(new);
}


TEST(getNbFils_ou_Freres) { //Test pour un arbre "classique"
	int nbRacines = 0;
	int nbEltsPref = 0;
	eltPrefPostFixee_t tabEltPref[NB_ELTPREF_MAX];
	cell_lvlh_t *racine = NULL;
	char buffer[1024];
	FILE * file = fmemopen(buffer, 1024, "w");

	REQUIRE ( NULL != file);

	printf("\033[35m\ngetNbFils_ou_Freres :");
	printf("\033[0m\n");

	nbRacines = lirePref_fromFileName("../pref_exTP.txt", tabEltPref, &nbEltsPref);
	racine = pref2lvlh(tabEltPref, nbRacines);

	//Ces test verifient les nombres de frere ou de fils dans toute notre arborescence
	REQUIRE( NULL != racine );
	CHECK( 2 == getNbFils_ou_Freres(racine) );     // 2 freres y compris lui-meme
	CHECK( 3 == getNbFils_ou_Freres(racine->lv) ); // 3 fils

	REQUIRE( NULL != racine->lv );
	CHECK( 3 == getNbFils_ou_Freres(racine->lv) );     // 3 freres y compris lui-meme
	CHECK( 2 == getNbFils_ou_Freres(racine->lv->lv) ); // 2 fils

	REQUIRE( NULL != racine->lv->lh );
	CHECK( 0 == getNbFils_ou_Freres(racine->lv->lh->lv) ); // 0 fils

	REQUIRE( NULL != racine->lv->lh->lh );
	CHECK( 1 == getNbFils_ou_Freres(racine->lv->lh->lh->lv) ); // 1 fils

	fclose(file);
	libererArbre(&racine);
}

TEST(getNbFils_ou_Freres_racineSeule) { //Arbre avec une seule racine sans fils ou frere
    cell_lvlh_t *racine = allocPoint('A');

    printf("\033[35m\ngetNbFils_ou_Freres_racineSeule :");
    printf("\033[0m\n");

    REQUIRE(NULL != racine);

    CHECK(1 == getNbFils_ou_Freres(racine)); // Le nombre de frères ou de fils est égal à un (racine elle-même)

    free(racine);
}

TEST(getNbFils_ou_Freres_arborescenceAvecFreres) { //Test avec une seule racine avec des frères
    cell_lvlh_t *racine = allocPoint('A');
    cell_lvlh_t *frere1 = allocPoint('B');
    cell_lvlh_t *frere2 = allocPoint('C');

    printf("\033[35m\ngetNbFils_ou_Freres_arborescenceAvecFreres :");
    printf("\033[0m\n");

    REQUIRE(NULL != racine);
    REQUIRE(NULL != frere1);
    REQUIRE(NULL != frere2);

    racine->lh = frere1;
    frere1->lh = frere2;

    CHECK(3 == getNbFils_ou_Freres(racine)); // Le nombre de frères ou de fils est égal à 3 (racine, frere1, frere2)

    free(racine);
	free(frere1);
	free(frere2);
}

TEST(printPostfixee) { //Test avec un fichier existant
	int nbRacines = 0;
	int nbEltsPref = 0;
	eltPrefPostFixee_t tabEltPref[NB_ELTPREF_MAX];
	cell_lvlh_t *racine = NULL;
	
	char buffer[1024];
	FILE * file = fmemopen(buffer, 1024, "w");
	REQUIRE ( NULL != file);

	printf("\033[35m\nprintPostFixee :");
	printf("\033[0m\n");

	nbRacines = lirePref_fromFileName("../pref_exTP.txt", tabEltPref, &nbEltsPref);
	racine = pref2lvlh(tabEltPref, nbRacines);

	printPostfixee(stdout, racine);
	printPostfixee(file, racine);
	fclose(file);
	CHECK( 0 == strcmp(buffer,"(E,0) (J,0) (B,2) (D,0) (G,0) (H,1) (A,3) (K,0) (M,0) (T,0) (F,3) (I,0) (C,2) 2\n") );
	
	libererArbre(&racine);
}

TEST(printPostfixeeFichierVide) { //Test avec un fichier inexistant
	int nbRacines = 0;
	int nbEltsPref = 0;
	eltPrefPostFixee_t tabEltPref[NB_ELTPREF_MAX];
	cell_lvlh_t *racine = NULL;
	
	char buffer[1024];
	FILE * file = fmemopen(buffer, 1024, "w");
	REQUIRE ( NULL != file);

	printf("\033[35m\nprintPostFixeeFichierVide :");
	printf("\033[0m\n");

	nbRacines = lirePref_fromFileName("", tabEltPref, &nbEltsPref);
	racine = pref2lvlh(tabEltPref, nbRacines);

	printPostfixee(stdout, racine);
	printPostfixee(file, racine);
	fclose(file);
	CHECK( 0 == strcmp(buffer,"0\n") ); //Fichier vide donc affiche juste une racine = à 0
	
	libererArbre(&racine);
}


END_TEST_GROUP(ARBRE_PARCOURS)

int main(void) {
	RUN_TEST_GROUP(ARBRE_PARCOURS);
	return EXIT_SUCCESS;
}
