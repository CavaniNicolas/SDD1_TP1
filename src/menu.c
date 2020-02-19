
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "commun.h"
#include "menu.h"

int menu(library_t ** library, borrowings_t ** borrowings) {
	int choice = -1;
	char filename[255];

	printf ("\t\t\tMENU\n");
	printf("|           Afficher la bibliothèque            : 1|\n");
	printf("|        Afficher la liste des emprunts         : 2|\n");
	printf("|         Lire le fichier des emprunts          : 3|\n");
	printf("|         Lire le fichier des retours           : 4|\n");
	printf("|   Afficher les emprunts a rendre avant le...  : 5|\n");
	printf("|    Sauvegarder les emprunts dans un fichier   : 6|\n");
	printf("|                    Quitter                    : 0|\n");
	printf("\t\t: \n");
	scanf("%d", &choice);

	switch (choice){
		case 0:
			printf("On quitte\n");
			break;
		case 1:
			displayLibrary(library);
			break;
		case 2:
			displayBorrowings(borrowings);
			break;
		case 3:
			scanf("%s", filename);
			borrowBook(filename, library, &borrowings);
			break;
		case 4:
			scanf("%s", filename);
			broughtBackBook(filename, &library, &borrowings);
			break;
		case 5:
			printf("5\n");
			break;
		case 6:
			printf("6\n");
			break;
		default:
			printf("Selectionner une option\n");
			break;

	}
	return choice;
}