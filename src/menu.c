
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

	char date[9];

	printf("\033[33m\n\n" \
" -----------------------------------------------------\n" \
" |\033[35m                     MENU                          \033[33m|\n" \
" |\033[36m           Afficher la bibliothèque            : 1 \033[33m|\n" \
" |\033[36m        Afficher la liste des emprunts         : 2 \033[33m|\n" \
" |\033[36m         Lire le fichier des retours           : 3 \033[33m|\n" \
" |\033[36m   Afficher les emprunts a rendre avant le...  : 4 \033[33m|\n" \
" |\033[36m    Sauvegarder les emprunts dans un fichier   : 5 \033[33m|\n" \
" |\033[36m                    Quitter                    : 0 \033[33m|\n" \
" -----------------------------------------------------\n\033[00m" \
"         -: ");
	
	argNb = scanf("%n%d", &argNb, &choice);
	// On vide le buffer dans le cas où autre chose qu'un int a été entré
	emptyBuffer();

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
				printf("\n" \
				        "\033[32m   |\033[36m Nom du fichier des rendus : \033[32m|\n" \
					            "   |\033[36m    \"Rendus.txt\"         : 1 \033[32m|\n" \
					            "   |\033[36m    Autre nom à entrer   : 0 \033[32m|\033[00m\n" \
					    "         -: ");
				scanf("%d",&typeFilename);

				if (typeFilename == 0) {
					printf("\n\033[32m   |\033[36m Entrer le nom du fichier des retours : \033[32m|\033[00m\n" \
						    "         -: ");
					scanf("%s", filename);
					broughtBackBook(filename, library, borrowings);

				} else if (typeFilename == 1) {
					strcpy(filename, "Rendus.txt");
					broughtBackBook(filename, library, borrowings);
				
				} else {
					printf("\n\033[31m   Choix Invalide\033[00m\n");
				}

				break;

			case 4:
				printf("\n" \
					    "\033[32m   |\033[36m Selectionner une date AAAAMMJJ : \033[32m|\n" \
					    "\033[00m         -: ");
				scanf("%s", date);
				emptyBuffer();
				if (isDateInputCorrect(date)) {
					displayBorrowingsBeforeDate(*borrowings, date);

				} else {
					printf("\n\033[31m   Date Invalide\033[00m\n");
				}

				break;

			case 5:
				saveBorrowingsInFile("emprunts/yoloAsupprimer.txt", *library, *borrowings);
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


int isDateInputCorrect(char date[9]) {
	int error = 1;
	int i = 0;

	while (date[i] != '\0' && error == 1) {
		if (date[i] < 48 || date[i] > 57) {
			error = 0;
		}
		i++;
	}
	if (i != 8) {
		date[8] = '\0';
		error = 0;
	}
	return error;
}



void emptyBuffer() {
	while (getchar () != '\n');
}