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
	//Nous avons ajouté : 

    // Test avec une valeur présente dans un sous-arbre
    pere = rechercher_v(racine, 'J');
    REQUIRE(NULL != pere);
    CHECK('J' == pere->val);

    // Test avec une arborescence vide
    cell_lvlh_t *arborescenceVide = NULL;
    pere = rechercher_v(arborescenceVide, 'A');
    CHECK(NULL == pere);

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
	CHECK( 'T' == (*pprec)->val );

	pprec = rechercherPrecFilsTries(pere, 'Z');
	CHECK( NULL == *pprec );
	libererArbre(&racine);

	// Test avec un père ayant un seul fils
    cell_lvlh_t *pereUnique = allocPoint('X');
    pereUnique->lv = allocPoint('Y');

    pprec = rechercherPrecFilsTries(pereUnique, 'Y');
    REQUIRE(NULL != *pprec);
    CHECK('Y' == (*pprec)->val);

	free(pereUnique->lv);
	free(pereUnique);
}

TEST(insererTrie) {
	int nbRacines = 0;
	int nbEltsPref = 0;
	eltPrefPostFixee_t tabEltPref[NB_ELTPREF_MAX];
	cell_lvlh_t *racine = NULL;
	cell_lvlh_t *pere=NULL;

	printf("\033[34m\nrechercherPrecFilsTries :");
	printf("\033[0m\n");
	nbRacines = lirePref_fromFileName("../pref_exTP.txt", tabEltPref, &nbEltsPref);
	racine = pref2lvlh(tabEltPref, nbRacines);

	pere = rechercher_v(racine, 'F');
	REQUIRE( NULL != pere );
	CHECK( 'F' == pere->val );

	int code = insererTrie(racine, 'F', 'B');	//Ajout au debut
	REQUIRE(code==1);
	CHECK('B'==pere->lv->val);
	
	code = insererTrie(racine, 'F', 'L'); 		//Ajout en troisième fils
	REQUIRE(code==1);
	CHECK('L'==pere->lv->lh->lh->val);

	code = insererTrie(racine, 'F', 'Z');		//Ajout en fin
	REQUIRE(code==1);
	CHECK('Z'==pere->lv->lh->lh->lh->lh->lh->val);
	
	pere = rechercher_v(racine, 'I'); 
	REQUIRE( NULL != pere );
	CHECK( 'I' == pere->val );
	
	code = insererTrie(racine, 'I', 'D');		//Ajout de premier fils
	REQUIRE(code==1);
	CHECK('D'==pere->lv->val);

	code = insererTrie(racine, 'W', 'D');		//Ajout à un père inexistant
	CHECK(code==0);


	libererArbre(&racine);
	racine = NULL;
	code = insererTrie(racine, 'W', 'D');		//Ajout à un arbre vide + père inexistant
	CHECK(code==0);



	
}

END_TEST_GROUP(ARBRE_INSERT)

int main(void) {
	RUN_TEST_GROUP(ARBRE_INSERT);
	return EXIT_SUCCESS;
}
