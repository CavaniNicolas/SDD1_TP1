
#include <stdio.h>
#include <stdlib.h>
#include "commun.h"
#include "emprunts.h"
#include "listes.h"
#include "menu.h"


int main(int argc, char ** argv) {
	if (argc<2) {
		printf("Entrez un nom de fichier à lire\n");

	} else {
		library_t * library = NULL;
		borrowings_t * borrowings = NULL;

		int isStarted = 0;

		printf("\nCréer la liste Bibliothèque et actualiser les livres empruntés ?\n\t1: Oui\n\t0: Non\n\t\t- ");
		scanf("%d",&isStarted);

		if (isStarted == 1) {
			createLibrary(argv[1], &library);
			
			if (library != NULL) {
				borrowBook("Emprunts.txt", library, &borrowings);
				broughtBackBook("Rendus.txt", &library, &borrowings);

			}

			int inMenu = 1;
			while (inMenu != 0) {
				inMenu = menu(&library, &borrowings);
			}

			// displayBorrowings(borrowings);
			// displayLibrary(library);

			freeAllLists(&library, &borrowings);

		} else {
			printf("Quitter\n");
		}
	}
	return 0;
}