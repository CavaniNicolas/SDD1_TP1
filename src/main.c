/* --------------------------------------------------------------------------- */
/*  main.c                                                                     */
/*                     Contient le programme principal                         */
/*                                                                             */
/* --------------------------------------------------------------------------- */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "common.h"
#include "borrow.h"
#include "lists.h"
#include "menu.h"


int main(int argc, char ** argv) {
	if (argc<2) {
		printf("Entrez un nom de fichier à lire\n");

	} else {
		library_t    * library    = NULL; /*Bibliothèque*/
		borrowings_t * borrowings = NULL; /*Liste emprunts*/

		int            isStarted  = 0;    /*On lance le programme ou non*/

		char           filename[22];      /*Nom du fichier à appeler*/
		char           filePath[40];      /*Chemin vers le fichier à appeler*/

		printf("\n\033[33m   | \033[36mCréer la liste Bibliothèque et actualiser les livres empruntés ?\033[33m |\n" \
			   "\t\033[32mOui  :1\n\t\033[31mNon  :0\033[00m\n\t\t-: ");
		scanf("%d",&isStarted);

		/*Le programme se lance*/
		if (isStarted == 1) {
			/*Création de la bibliothèque depuis le fichier passé en paramètre lors de l'execution*/
			createLibrary(argv[1], &library);

			printf("   Création de la bibliothèque depuis : \033[32m%s\033[00m\n", argv[1]);

			if (library != NULL) {
				/*Cherche s'il existe un fichier des emprunts dans le dossier borrowings*/
				/*et sélectionne le plus récent*/
				findFilenameMax(filename);

				/*Créer le bon filePath à partir de filename*/
				if (strcmp(filename, "0000-00-00_00h00'00''")) {
					snprintf(filePath, 40, "./borrowings/%s", filename);
				} else {
					strcpy(filePath, "text_files/borrowings.txt");
				}

				/*Création de la liste des emprunts à partir de filePath*/
				borrowBook(filePath, library, &borrowings);
				printf("   Actualisation des livres empruntés depuis : \033[32m%s\033[00m\n", filePath);
				
				strcpy(filePath, "text_files/brought_back.txt");
				/*Actualise les emprunts en fonction des retours à partir de filePath*/
				broughtBackBook(filePath, library, &borrowings);
				printf("   Actualisation des livres rendus depuis : \033[32m%s\033[00m\n", filePath);

				/*Lancement du menu*/
				menu(&library, &borrowings);

			} else {
				printf("\033[31m   Bibliothèque vide\033[00m\n\n");
			}

			/*Libération de la mémoire*/
			freeLibrary(&library);
			freeBorrowings(&borrowings);

		} else {
			printf("\033[31m   Quitter\n\n\033[00m");
		}
	}
	return 0;
}