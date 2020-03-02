/* --------------------------------------------------------------------------- */
/*  lists.c                                                                    */
/*              Contient les fonctions associées à la liste bibliothèque       */
/*                                                                             */
/* --------------------------------------------------------------------------- */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "common.h"
#include "lists.h"


int createLibrary(char * filename, library_t ** library) {
	FILE * file = NULL;           /*Fichier*/
	file = fopen(filename, "r");

	int       error = 1;          /*Retour d'erreur*/

	char      category[4]  = "_"; /*Catégorie lue dans le fichier*/
	int       categorySize = 0;   /*Nombre de livre dans une catégorie*/

	int       i = 0;              /*Compteur*/
	books_t * lastBook = NULL;    /*Dernier livre creé*/
					
	int       bookNb = 0;         /*Numéro du livre lu dans le fichier*/
	char      title[11];          /*Titre lu dans le fichier*/

	if (file != NULL) {

		while (!feof(file) && error == 1) {

			fscanf(file, "%s %d", category, &categorySize);
			
			// verification importante dans le cas où le fichier ne contient qu'une ligne avec \n
			if (category[0] != '_') {
				error = createCategory(library, category);
				
				if (error == 1){

					for (i = 0; i < categorySize; i++) {
						// %[^\n] pour récupérer les chaines de caracteres comportants des espaces jusqu'au premier \n à l'aide d'un scanf
						fscanf(file, "%d %[^\n]", &bookNb, title);
						remove_endstr_r_windows(title);
						error = createBook(library, &lastBook, bookNb, title);
					}
				}
			}
		}
		fclose(file);

	} else {
		error = 0;
	}
	return error;
}


int createCategory(library_t ** library, char category[4]) {
	int         error = 1;    /*Retour d'erreur*/
	library_t * elemLib = (library_t *)malloc(sizeof(library_t));

	if (elemLib != NULL) {
		strcpy(elemLib->category, category);
		elemLib->begBooks = NULL;
		elemLib->next = *library;
		*library = elemLib;

	} else {
		error = 0;
	}

	return error;
}


int createBook(library_t ** library, books_t ** lastBook, int bookNb, char title[11]) {
	int       error = 1;    /*Retour d'erreur*/
	books_t * elemBook = (books_t *)malloc(sizeof(books_t));

	if (elemBook != NULL) {
		elemBook->bookNb = bookNb;
		strcpy(elemBook->title, title);
		elemBook->isBorrowed = 0;
		elemBook->next = NULL;

		if ((*library)->begBooks == NULL) {
			(*library)->begBooks = elemBook;
		} else {
			(*lastBook)->next = elemBook;
		}

		*lastBook = elemBook;

	} else {
		error = 0;
	}
	return error;
}


void remove_endstr_r_windows(char * line){
	int i = 0; /*Compteur*/

	while (line[i]!='\0') {
		i++;
	}
	i--;

	if (line[i] == '\r') {
		line[i] = '\0';
	}
}


void displayLibrary(library_t const * curLib) {
	books_t * curBooks = NULL; /*Pointeur courant sur la liste des livres d'une catégorie*/

	printf("\n\033[32m   On affiche la bibliothèque :\033[00m\n");

	if (curLib != NULL) {
		while (curLib != NULL) {
			printf("\t%s\n", curLib->category);
			curBooks = curLib->begBooks;

			while (curBooks != NULL) {
				printf("\t   %d %s %d\n", curBooks->bookNb, curBooks->title, curBooks->isBorrowed);
				curBooks = curBooks->next;
			}

			curLib = curLib->next;
		}

	} else {
		printf("\n\033[31m   Liste bibliothèque vide\033[00m\n");
	}
}


void freeLibrary(library_t ** library) {
	library_t * curLib   = *library;  /*Pointeur courant sur la bibliothèque*/
	books_t   * curBooks = NULL;      /*Pointeur courant sur la liste des livres d'une catégorie*/

	/*Libération de la bibliothèque*/
	while (*library != NULL) {
		curBooks = curLib->begBooks;

		/*Libération des livres d'une catégorie*/
		while (curLib->begBooks != NULL) {
			curBooks = curBooks->next;
			free(curLib->begBooks);
			curLib->begBooks = curBooks;
		}

		/*Libération des catégories*/
		curLib = curLib->next;
		free(*library);
		*library = curLib;
	}
}
