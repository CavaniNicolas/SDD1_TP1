
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <dirent.h>
#include <errno.h>
#include <sys/types.h>
#include <sys/stat.h>
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

	// Dans un scanf : %n permet de récupérer le nombre de caractères lu par le scanf
	// scanf return le nombre d'arguments qu'elle a rempli (l'argument %n n'est pas pris en compte)
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
				        "\033[32m   |\033[36m Nom du fichier des rendus :          \033[32m|\n" \
					            "   |\033[36m    text_files/brought_back.txt   : 1 \033[32m|\n" \
					            "   |\033[36m    Autre nom à entrer            : 0 \033[32m|\033[00m\n" \
					    "         -: ");
				scanf("%d",&typeFilename);

				if (typeFilename == 0) {
					printf("\n\033[32m   |\033[36m Entrer le nom du fichier des retours : \033[32m|\033[00m\n" \
						    "         -: ");
					scanf("%s", filename);
					printf("   Actualisation des livres empruntés depuis le fichier des retours :\n" \
						   "         \033[32m%s\033[00m\n", filename);
					broughtBackBook(filename, *library, borrowings);

				} else if (typeFilename == 1) {
					strcpy(filename, "text_files/brought_back.txt");
					printf("   Actualisation des livres empruntés depuis le fichier des retours :\n" \
						   "         \033[32m%s\033[00m\n", filename);
					broughtBackBook(filename, *library, borrowings);
				
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
				createFilename(filename);
				saveBorrowingsInFile(filename, *library, *borrowings);
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


void createFilename(char * filename) {
	int h, min, s, day, month, year;
	time_t now;
	time(&now);

	mkdir("borrowings", 777);

	struct tm *local = localtime(&now);
	h = local->tm_hour;
	min = local->tm_min;
	s = local->tm_sec;
	day = local->tm_mday;
	month = local->tm_mon + 1;
	year = local->tm_year + 1900;

	snprintf(filename, 40, "borrowings/%d-%02d-%02d_%02dh%02d'%02d''", year, month, day, h, min, s);
}


void findFilenameMax(char filenameMax[22]) {
	DIR * rep = opendir("./borrowings");
	strcpy(filenameMax, "0000-00-00_00h00'00''");

	if (rep != NULL) {
		struct dirent * ent = NULL;
		char            filename[22];
		char            filenameDate[15];
		char            filenameDateMax[15] = "00000000000000";
		int             i = 0;
		int             j = 0;

		while ((ent = readdir(rep)) != NULL) {

			if (strcmp(ent->d_name, ".") && strcmp(ent->d_name, "..")) {
				
				strcpy(filename, ent->d_name);

				i = 0; j = 0;
				while (filename[i] != '\0') {
					if (filename[i] >= 48 && filename[i] <= 57) {
						filenameDate[j] = filename[i];
						j++;
					}
					i++;
				}
				filenameDate[14] = '\0';

				if (atoi(filenameDate) > atoi(filenameDateMax)) {
					strcpy(filenameMax, filename);
				}
			}

		}

		closedir(rep);

	}
}


void emptyBuffer() {
	while (getchar () != '\n');
}
