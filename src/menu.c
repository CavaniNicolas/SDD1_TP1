
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "commun.h"
#include "menu.h"
#include "emprunts.h"
#include "listes.h"

int menu(library_t ** library, borrowings_t ** borrowings) {
	int  choice = -1;
	char filename[255];
	int  argNb = 0;
	int  typeFilename = 1;

	printf("\033[33m\n\n" \
"----------------------------------------------------\n" \
"|\033[35m                     MENU                         \033[33m|\n" \
"|\033[36m           Afficher la bibliothèque            : 1\033[33m|\n" \
"|\033[36m        Afficher la liste des emprunts         : 2\033[33m|\n" \
"|\033[36m         Lire le fichier des retours           : 3\033[33m|\n" \
"|\033[36m   Afficher les emprunts a rendre avant le...  : 4\033[33m|\n" \
"|\033[36m    Sauvegarder les emprunts dans un fichier   : 5\033[33m|\n" \
"|\033[36m                    Quitter                    : 0\033[33m|\n" \
"----------------------------------------------------\n\033[00m" \
"		-: ");
	
	argNb = scanf("%n%d", &argNb, &choice);
	// On vide le buffer dans le cas où autre chose qu'un int a été entré
	while (getchar () != '\n');

	if (argNb == 1) {

		switch (choice){

			case 0:
				printf("\n\033[31m   On quitte\033[00m\n\n");
				break;

			case 1:
				displayLibrary(*library);
				break;

			case 2:
				displayBorrowings(*borrowings);
				break;

			case 3:
				printf("\n   Nom du fichier des rendus :\n" \
					     "      \"Rendus.txt\"         : 1\n" \
					     "      Autre nom à entrer   : 0\n" \
					     "         -: ");
				scanf("%d",&typeFilename);

				if (typeFilename == 0) {
					printf("\n   Entrer le nom du fichier des retours\n" \
						     "         -: ");
					scanf("%s", filename);
				} else if (typeFilename == 1){
					strcpy(filename, "Rendus.txt");
				}

				broughtBackBook(filename, library, borrowings);
				break;

			case 4:
				printf("\n   4\n");
				break;

			case 5:
				printf("\n   5\n");
				break;

			default:
				printf("\n\033[33m   Selectionner une option\n");
				break;

		}

	} else {
		printf("\n\033[31m   Choix Invalide\033[00m\n");
	}

	return choice;
}