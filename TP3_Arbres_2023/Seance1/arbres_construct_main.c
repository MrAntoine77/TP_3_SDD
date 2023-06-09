/**
 * program for general linked list testing
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../pile.h"
#include "../eltsArbre.h"
#include "arbres_construct.h"
#include "../teZZt.h"


BEGIN_TEST_GROUP(ARBRE_CONSTRUCT)

TEST(nouvCell) {
	cell_lvlh_t *new;

	new = allocPoint('A');
	REQUIRE( NULL != new ); 
	CHECK( 'A' == new->val ); //Verifie la valeur
	CHECK( NULL == new->lv ); //Verifie le fils
	CHECK( NULL == new->lh ); //Verifie le frere

	free(new);
}


TEST(lirePref_fromFileName_exTP) { //Cas d'un fichier existant
	int nbRacines = 0;
	int nbEltsPref = 0;
	eltPrefPostFixee_t tabEltPref[NB_ELTPREF_MAX];

	nbRacines = lirePref_fromFileName("../pref_exTP.txt", tabEltPref, &nbEltsPref);

	printf("\033[34m\nlirePref_fromFileName_exTP :");
	printf("\033[0m\n");

	//Ces tests verifient différentes valeurs de la representation préfixée
	CHECK( 2 == nbRacines ); 
	CHECK( 13 == nbEltsPref );
	CHECK( 'A' == tabEltPref[0].val );
	CHECK( 3 == tabEltPref[0].nbFils );

	CHECK( 'B' == tabEltPref[1].val );
	CHECK( 2 == tabEltPref[1].nbFils );

	CHECK( 'C' == tabEltPref[7].val );
	CHECK( 2 == tabEltPref[7].nbFils );
	
	CHECK( 'I' == tabEltPref[nbEltsPref-1].val );
	CHECK( 0 == tabEltPref[nbEltsPref-1].nbFils );
}

TEST(lirePref_fromNothing) { //Cas d'un fichier inexistant
	int nbRacines = 0;
	int nbEltsPref = 0;
	eltPrefPostFixee_t tabEltPref[NB_ELTPREF_MAX];

	nbRacines = lirePref_fromFileName("", tabEltPref, &nbEltsPref);

	printf("\033[34m\nlirePref_fromNothing :");
	printf("\033[0m\n");

	//Ces tests verifient différentes valeurs de la representation préfixée
	CHECK( 0 == nbRacines ); 
	CHECK( 0 == nbEltsPref );
}

TEST(printTabEltPref_exTP) { //Cas avec un fichier existant
	int nbRacines = 0;
	int nbEltsPref = 0;
	eltPrefPostFixee_t tabEltPref[NB_ELTPREF_MAX];
	char buffer[1024];

	printf("\033[34m\nprintPref_exTP :");
	printf("\033[0m\n");

	FILE * file = fmemopen(buffer, 1024, "w");
	REQUIRE ( NULL != file);

	nbRacines = lirePref_fromFileName("../pref_exTP.txt", tabEltPref, &nbEltsPref);
	fprintf(file, "%d ", nbRacines);
	printTabEltPref(file, tabEltPref, nbEltsPref);
	fclose(file);

	//Ce test compare si nous avons mis écris dans le buffer le bon résultat
	CHECK( 0 == strcmp(buffer, "2 (A,3) (B,2) (E,0) (J,0) (D,0) (H,1) (G,0) (C,2) (F,3) (K,0) (M,0) (T,0) (I,0)\n") ); 
}

TEST(printTabEltPrefVide_exTP) { //Cas avec un fichier n'existant pas
	int nbRacines = 0;
	int nbEltsPref = 0;
	eltPrefPostFixee_t tabEltPref[NB_ELTPREF_MAX];
	char buffer[1024];

	printf("\033[34m\nprintPrefVide_exTP :");
	printf("\033[0m\n");

	FILE * file = fmemopen(buffer, 1024, "w");
	REQUIRE ( NULL != file);

	nbRacines = lirePref_fromFileName("", tabEltPref, &nbEltsPref);
	fprintf(file, "%d ", nbRacines);
	printTabEltPref(file, tabEltPref, nbEltsPref);
	fclose(file);

	//Ce test compare si nous avons mis écris dans le buffer le bon résultat
	CHECK( 0 == strcmp(buffer, "0 \n") ); 
}

// 2  (A,3)  (B,2)  (E,0)  (J,0)  (D,0)  (H,1) (G,0)  (C,2)  (F,3)  (K,0)  (M,0)  (T,0)  (I,0)
TEST(pref2lvlh1_exTP) { //Cas avec un fichier existant
	int nbRacines = 0;
	int nbEltsPref = 0;
	eltPrefPostFixee_t tabEltPref[NB_ELTPREF_MAX];
	cell_lvlh_t *racine = NULL;

	printf("\033[35m\npref2lvlh1_exTP :");
	printf("\033[0m\n");

	nbRacines = lirePref_fromFileName("../pref_exTP.txt", tabEltPref, &nbEltsPref);

	printTabEltPref(stdout, tabEltPref, nbEltsPref);

	racine = pref2lvlh(tabEltPref,nbRacines);

	//Ces test verifient les valeurs de notre arborescence
	CHECK('A'==racine->val);
	CHECK('C'==racine->lh->val);
	CHECK('J'==racine->lv->lv->lh->val);

	libererArbre(&racine);
}

TEST(pref2lvlh_fichierVide) { //Cas d'un fichier vide
    int nbRacines = 0;
    int nbEltsPref = 0;
    eltPrefPostFixee_t tabEltPref[NB_ELTPREF_MAX];
    cell_lvlh_t *racine = NULL;
    

    printf("\033[35m\npref2lvlh_fichierVide :");
    printf("\033[0m\n");

    nbRacines = lirePref_fromFileName("", tabEltPref, &nbEltsPref);

	//Ces test verifient les valeurs de notre arborescence qui n'est pas définie
    CHECK(0 == nbRacines);
	CHECK(NULL == racine);
}

END_TEST_GROUP(ARBRE_CONSTRUCT)

int main(void) {
	RUN_TEST_GROUP(ARBRE_CONSTRUCT);
	return EXIT_SUCCESS;
}
