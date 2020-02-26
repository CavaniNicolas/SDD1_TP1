
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
		int inMenu = 1;

		printf("\n\033[36mCréer la liste Bibliothèque et actualiser les livres empruntés ?\n\t\033[32mOui  :1\n\t\033[31mNon  :0\033[00m\n\t\t-: ");
		scanf("%d",&isStarted);

		if (isStarted == 1) {
			createLibrary(argv[1], &library);
			
			if (library != NULL) {
				borrowBook("Emprunts.txt", library, &borrowings);
				broughtBackBook("Rendus.txt", library, &borrowings);
			}

			while (inMenu != 0) {
				inMenu = menu(&library, &borrowings);
			}

			freeAllLists(&library, &borrowings);

		} else {
			printf("\033[31m   Quitter\n\n\033[00m");
		}
	}
	return 0;
}