
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "commun.h"
#include "listes.h"

// %[^\n] pour recuperer les chaines de caracteres compportant des espaces jusquau premier \n a laide dun scanf
// dans un scanf : %n permet de recuperer le nombre de caractere lu par le scanf
// scanf return le nombre d'arguments quelle a rempli (largumetn %n nest pas pris en compte)

void createLibrary(char * filename, library_t ** library) {
	FILE * file = NULL;
	file = fopen(filename,"r");

	if (file != NULL){
		char categoryName[4];
		int categorySize = 0;
		int i = 0;
		int bookNb = 0;
		char title[11];

		library_t * elemLib;
		library_t * curLib = *library;

		books_t * elemBooks;

		while (!feof(file)) {
			fscanf(file,"%s %d", categoryName, &categorySize);
			
			elemLib = (library_t *)malloc(sizeof(library_t));
		
			if (elemLib != NULL) {

				strcpy(elemLib->category, categoryName);
				elemLib->begBooks = NULL;
				elemLib->endBooks = NULL;
				elemLib->next = NULL;

				if (*library == NULL) {
					*library=elemLib;
				}
				else {
					curLib->next = elemLib;
				}
				curLib = elemLib;


				for (i=0; i<categorySize; i++) {
					fscanf(file, "%d %[^\n]", &bookNb, title);

					elemBooks = (books_t *)malloc(sizeof(books_t));

					if (elemBooks != NULL) {
						elemBooks->bookNb = bookNb;
						remove_endstr_r_windows(title);
						strcpy(elemBooks->title, title);
						elemBooks->isBorrowed = false;
						elemBooks->next = NULL;

						if (curLib->begBooks == NULL) {
							curLib->begBooks = elemBooks;
						}
						else {
							curLib->endBooks->next = elemBooks;
						}
						curLib->endBooks = elemBooks;
					}
				}
			}
		}
			
		fclose(file);
	}
	else {
		printf("Nom de fichier inexistant\n");
	}
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

void displayLibrary(library_t * library) {
	library_t * curLib = library;
	books_t * curBooks = NULL;
	printf("\non affiche la liste bibliothèque\n");

	while (curLib != NULL) {
		printf("%s\n", curLib->category);
		curBooks = curLib->begBooks;
		while (curBooks != NULL) {
			printf("%d %s %d\n", curBooks->bookNb, curBooks->title, curBooks->isBorrowed);
			curBooks = curBooks->next;
		}
		curLib = curLib->next;
	}
}

void freeAllLists(library_t ** library, borrowings_t ** borrowings) {
	library_t * curLib = *library;
	books_t * curBooks = NULL;
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
