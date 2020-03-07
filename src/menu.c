/* --------------------------------------------------------------------------- */
/*  menu.c    Contient les fonctions associées au menu,                        */
/*            interface utilisateur appelant les fonctions des autres fichiers */
/*                                                                             */
/* --------------------------------------------------------------------------- */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <dirent.h>
#include "common.h"
#include "menu.h"
#include "borrow.h"
#include "lists.h"


void menu(library_t ** library, borrowings_t ** borrowings) {
	int  choice = -1;   /*Choix dans le menu*/
	int  argNb  = 0;    /*Evite les bugs liés à une saisie incorecte pour le choix du menu*/
	char filename[255]; /*Pour stocker le nom du fichier à ouvrir*/

	while (choice != 0) {

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

		// Dans un scanf : %n permet de récupérer le nombre de caractères lu par le scanf
		// scanf return le nombre d'arguments qu'elle a rempli (l'argument %n n'est pas pris en compte)
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
					menuChoice3(*library, borrowings);
					break;

				case 4:
					menuChoice4(*borrowings);
					break;

				case 5:
					saveBorrowingsInFile(filename, *library, *borrowings);
					break;

				default:
					printf("\n\033[33m   Selectionner une option\033[00m\n");
					break;
			}

		} else {
			printf("\n\033[31m   Choix Invalide\033[00m\n");
		}
	}
}


void menuChoice3(library_t * library, borrowings_t ** borrowings) {
	char filename[255];     /*Pour stocker le nom du fichier à ouvrir*/
	int  typeFilename = 1;  /*Booléen -saisie du nom du fichier ou -nom automatique*/
	char lineTmp[255];      /*Chaine de caractères pour récupérer la saisie avec fgets()*/

	printf("\n" \
	        "\033[32m   |\033[36m Nom du fichier des rendus :          \033[32m|\n" \
		            "   |\033[36m    text_files/brought_back.txt   : 1 \033[32m|\n" \
		            "   |\033[36m    Autre nom à entrer            : 0 \033[32m|\033[00m\n" \
		    "         -: ");
	fgets(lineTmp, 255, stdin);
	typeFilename = lineTmp[0] - 48;

	if (typeFilename == 0) {
		printf("\n\033[32m   |\033[36m Entrer le nom du fichier des retours : \033[32m|\033[00m\n" \
			    "         -: ");
		fgets(filename, 255, stdin);
		remove_endstr_n(filename);

		printf("   Actualisation des livres empruntés depuis le fichier des retours :\n" \
			   "         \033[32m%s\033[00m\n", filename);
		broughtBackBook(filename, library, borrowings);

	} else if (typeFilename == 1) {
		strcpy(filename, "text_files/brought_back.txt");
		printf("   Actualisation des livres empruntés depuis le fichier des retours :\n" \
			   "         \033[32m%s\033[00m\n", filename);
		broughtBackBook(filename, library, borrowings);
	
	} else {
		printf("\n\033[31m   Choix Invalide\033[00m\n");
	}
}


void menuChoice4(borrowings_t * borrowings) {
	char date[255]; /*date saisie*/

	printf("\n" \
		    "\033[32m   |\033[36m Selectionner une date AAAAMMJJ : \033[32m|\n" \
		    "\033[00m         -: ");

	fgets(date, 255, stdin);
	remove_endstr_n(date);

	if (isDateInputCorrect(date)) {
		displayBorrowingsBeforeDate(borrowings, date);

	} else {
		printf("\n\033[31m   Date Invalide\033[00m\n");
	}
}


void remove_endstr_n(char * line){
	int i = 0; /*Compteur*/

	while (line[i]!='\0') {
		i++;
	}
	i--;

	if (line[i] == '\n') {
		line[i] = '\0';
	}
}


int isDateInputCorrect(char date[255]) {
	int  error = 1; /*Retour d'erreur*/
	int  i     = 0; /*Compteur*/

	while (date[i] != '\0' && error == 1) {
		if (date[i] < 48 || date[i] > 57 || i >= 8) {
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


void findFilenameMax(char filenameMax[22]) {
	DIR * rep = opendir("./borrowings");   /*Pointeur répertoire*/
	strcpy(filenameMax, "0000-00-00_00h00'00''");

	if (rep != NULL) {
		struct dirent * ent = NULL;        /*Pointeur entitée*/
		char            filename[22];      /*Nom du fichier*/
		char            filenameDate[15];  /*Date de la forme AAAAMMJJhhmmss contenue dans le nom du fichier*/
		char            filenameDateMax[15] = "00000000000000"; 
		int             i = 0;
		int             j = 0;

		while ((ent = readdir(rep)) != NULL) {

			if (strcmp(ent->d_name, ".") && strcmp(ent->d_name, "..")) {
				
				strcpy(filename, ent->d_name);

				/*Remplissage de filenameDate avec uniquement les chiffres contenus dans filename*/
				i = 0; j = 0;
				while (filename[i] != '\0') {
					if (filename[i] >= 48 && filename[i] <= 57) {
						filenameDate[j] = filename[i];
						j++;
					}
					i++;
				}
				filenameDate[14] = '\0';

				/*filenameMax contient le nom du fichier le plus récent s'il existe, "0000-00-00_00h00'00''" sinon*/
				if (atoi(filenameDate) > atoi(filenameDateMax)) {
					strcpy(filenameMax, filename);
				}
			}

		}

		closedir(rep);

	}
}
