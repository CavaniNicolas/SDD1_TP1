
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "commun.h"
#include "menu.h"
#include "emprunts.h"
#include "listes.h"

int menu(library_t ** library, borrowings_t ** borrowings) {
	int choice = -1;
	char filename[255];

	printf( \
"                      MENU\n" \
"|           Afficher la bibliothèque            : 1|\n" \
"|        Afficher la liste des emprunts         : 2|\n" \
"|         Lire le fichier des retours           : 3|\n" \
"|   Afficher les emprunts a rendre avant le...  : 4|\n" \
"|    Sauvegarder les emprunts dans un fichier   : 5|\n" \
"|                    Quitter                    : 0|\n" \
"			: ");
	scanf("%d", &choice);

	switch (choice){
		case 0:
			printf("On quitte\n");
			break;
		case 1:
			displayLibrary(*library);
			break;
		case 2:
			displayBorrowings(*borrowings);
			break;
		case 3:
			scanf("%s", filename);
			broughtBackBook(filename, library, borrowings);
			break;
		case 4:
			printf("5\n");
			break;
		case 5:
			printf("6\n");
			break;
		default:
			printf("Selectionner une option\n");
			break;

	}
	return choice;
}