#include <stdio.h>
#include <stdlib.h>
#include "commun.h"
#include "emprunts.h"
#include "listes.h"


int main(int argc, char ** argv){
	if (argc<2){
		printf("Entrez un nom de fichier à lire\n");
	}
	else{
		biblio_t * trCat = NULL;
		emprunts_t * trEmp = NULL;

		lireFichier_creerListes(argv[1], &trCat);
		afficher(trCat);

		emprunterLivre("Emprunts.txt", trCat, &trEmp);

		afficherEmprunts(trEmp);

		libererlistes(&trCat, &trEmp);
	}
	return 0;
}