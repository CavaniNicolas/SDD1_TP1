
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
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

		int  isStarted = 0;
		int  inMenu = 1;

		char filename[22];
		char filePath[40];

		printf("\n\033[33m   | \033[36mCréer la liste Bibliothèque et actualiser les livres empruntés ?\033[33m |\n\t\033[32mOui  :1\n\t\033[31mNon  :0\033[00m\n\t\t-: ");
		scanf("%d",&isStarted);

		if (isStarted == 1) {
			createLibrary(argv[1], &library);
			printf("   Création de la bibliothèque depuis : \033[32m%s\033[00m\n", argv[1]);

			if (library != NULL) {
				findFilenameMax(filename);

				if (strcmp(filename, "0000-00-00_00h00'00''")) {
					snprintf(filePath, 40, "./borrowings/%s", filename);
				} else {
					strcpy(filePath, "text_files/borrowings.txt");
				}

				borrowBook(filePath, library, &borrowings);
				broughtBackBook("text_files/brought_back.txt", library, &borrowings);
				printf("   Actualisation des livres empruntés depuis : \033[32m%s\033[00m\n", filePath);

				while (inMenu != 0) {
					inMenu = menu(&library, &borrowings);
				}

			} else {
				printf("\033[31m   Bibliothèque vide\033[00m\n\n");
			}

			freeAllLists(&library, &borrowings);

		} else {
			printf("\033[31m   Quitter\n\n\033[00m");
		}
	}
	return 0;
}