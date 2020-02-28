
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "common.h"
#include "lists.h"


int createLibrary(char * filename, library_t ** library) {
	int error = 1;

	FILE * file = NULL;
	file = fopen(filename, "r");

	if (file != NULL) {
		char category[4] = "_";
		int  categorySize = 0;

		library_t * elemLib = NULL;

		while (!feof(file)) {

			elemLib = (library_t *)malloc(sizeof(library_t));

			if (elemLib != NULL) {
				fscanf(file, "%s %d", category, &categorySize);
				
				// verification importante dans le cas où le fichier ne contient qu'une ligne avec \n
				if (category[0] != '_') {
					strcpy(elemLib->category, category);
					elemLib->begBooks = NULL;
					elemLib->next = *library;
					*library = elemLib;

					fillBooksInLibrary(file, elemLib, categorySize);
				}

			} else {
				error = 0;
			}
		}

		fclose(file);
	} else {
		error = 0;
	}
	return error;
}


int fillBooksInLibrary(FILE * file, library_t * curLib, int categorySize) {
	int  error = 1;
	int  i = 0;
	int  bookNb = 0;
	char title[11];
	books_t * elemBooks = NULL;
	books_t * curBooks = curLib->begBooks;

	for (i=0; i<categorySize; i++) {
		elemBooks = (books_t *)malloc(sizeof(books_t));

		if (elemBooks != NULL) {
			// %[^\n] pour récupérer les chaines de caracteres comportants des espaces jusqu'au premier \n à l'aide d'un scanf
			fscanf(file, "%d %[^\n]", &bookNb, title);
			remove_endstr_r_windows(title);
			elemBooks->bookNb = bookNb;
			strcpy(elemBooks->title, title);
			elemBooks->isBorrowed = false;
			elemBooks->next = NULL;

			if (curLib->begBooks == NULL) {
				curLib->begBooks = elemBooks;
				curBooks = elemBooks;
			} else {
				curBooks->next = elemBooks;
			}

			curBooks = elemBooks;

		} else {
			error = 0;
		}
	}
	return error;
}


void remove_endstr_r_windows(char * line){
	int i = 0;

	while (line[i]!='\0') {
		i++;
	}
	i--;

	if (line[i] == '\r') {
		line[i] = '\0';
	}
}


void displayLibrary(library_t const * curLib) {
	books_t   * curBooks = NULL;

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


void freeAllLists(library_t ** library, borrowings_t ** borrowings) {
	library_t    * curLib = *library;
	books_t      * curBooks = NULL;
	borrowings_t * curBorrow = *borrowings;

	while (*library != NULL) {
		curBooks = curLib->begBooks;

		while (curLib->begBooks != NULL) {
			curBooks = curBooks->next;
			free(curLib->begBooks);
			curLib->begBooks = curBooks;
		}
		
		curLib = curLib->next;
		free(*library);
		*library = curLib;
	}

	while (*borrowings != NULL) {
		curBorrow = curBorrow->next;
		free(*borrowings);
		*borrowings = curBorrow;
	}
}
