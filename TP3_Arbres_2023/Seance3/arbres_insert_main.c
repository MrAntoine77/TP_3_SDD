/**
 * program for general linked list testing
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../pile.h"
#include "../eltsArbre.h"
#include "../Seance1/arbres_construct.h"
#include "../Seance2/arbres_parcours.h"
#include "arbres_insert.h"
#include "../teZZt.h"


BEGIN_TEST_GROUP(ARBRE_INSERT)

TEST(nouvCell) {
	cell_lvlh_t *new;

	new = allocPoint('A');
	REQUIRE( NULL != new ); 
	CHECK( 'A' == new->val );
	CHECK( NULL == new->lv );
	CHECK( NULL == new->lh );

	free(new);
}


TEST(rechercher_v) {
	int nbRacines = 0;
	int nbEltsPref = 0;
	eltPrefPostFixee_t tabEltPref[NB_ELTPREF_MAX];
	cell_lvlh_t *racine = NULL;
	cell_lvlh_t *pere = NULL;

	printf("\033[35m\nrechercher_v :");
	printf("\033[0m\n");

	nbRacines = lirePref_fromFileName("../pref_exTP.txt", tabEltPref, &nbEltsPref);
	racine = pref2lvlh(tabEltPref, nbRacines);

	pere = rechercher_v(racine, 'X');   // valeur inexistante
	CHECK( NULL == pere );

	pere = rechercher_v(racine, 'A');   // valeur a la racine
	REQUIRE( NULL != pere );
	CHECK( 'A' == pere->val );

// autres tests a ajouter

	libererArbre(&racine);
}

TEST(rechercherPrecFilsTries) {
	int nbRacines = 0;
	int nbEltsPref = 0;
	eltPrefPostFixee_t tabEltPref[NB_ELTPREF_MAX];
	cell_lvlh_t *racine = NULL;
	cell_lvlh_t *pere = NULL;
	cell_lvlh_t **pprec = NULL;

	printf("\033[34m\nrechercherPrecFilsTries :");
	printf("\033[0m\n");
	nbRacines = lirePref_fromFileName("../pref_exTP.txt", tabEltPref, &nbEltsPref);
	racine = pref2lvlh(tabEltPref, nbRacines);

	pere = rechercher_v(racine, 'F');
	REQUIRE( NULL != pere );
	CHECK( 'F' == pere->val );


	pprec = rechercherPrecFilsTries(pere, 'A');
	REQUIRE( NULL != *pprec );
	CHECK( 'K' == (*pprec)->val );

// autres tests a ajouter

	pprec = rechercherPrecFilsTries(pere, 'S');
	REQUIRE( NULL != *pprec );
	CHECK( 'M' == (*pprec)->val );
	printf("VAL : %c\n",(*pprec)->val);


	pprec = rechercherPrecFilsTries(pere, 'Z');
	REQUIRE( NULL != *pprec );
	CHECK( 'T' == (*pprec)->val );
	libererArbre(&racine);
}

TEST(insererTrie) {
	int nbRacines = 0;
	int nbEltsPref = 0;
	eltPrefPostFixee_t tabEltPref[NB_ELTPREF_MAX];
	cell_lvlh_t *racine = NULL;

	printf("\033[34m\nrechercherPrecFilsTries :");
	printf("\033[0m\n");
	nbRacines = lirePref_fromFileName("../pref_exTP.txt", tabEltPref, &nbEltsPref);
	racine = pref2lvlh(tabEltPref, nbRacines);

	int code = insererTrie(racine, 'C', 'Z');
	printf("Code : %d\n",code);

	libererArbre(&racine);
}

END_TEST_GROUP(ARBRE_INSERT)

int main(void) {
	RUN_TEST_GROUP(ARBRE_INSERT);
	return EXIT_SUCCESS;
}
