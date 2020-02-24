
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "commun.h"
#include "emprunts.h"

// Affiche la liste des emprunts
void displayBorrowings(borrowings_t const * borrowings) {
	borrowings_t const * curBorrow = borrowings;
	printf("\n\033[32m   On affiche la liste des emprunts :\033[00m\n");
	
	if (curBorrow != NULL) {
		while (curBorrow != NULL) {
			printf("\tbookNb: %d  returnDate: %s\n", curBorrow->bookNb, curBorrow->returnDate);
			curBorrow = curBorrow->next;
		}
	} else {
		printf("\n\033[31m   Liste emprunts vide\033[00m\n");
	}

}

// Fct pour ajouter un emprunt
void borrowBook(char * filename, library_t * library, borrowings_t ** borrowings) {
	FILE * file = NULL;
	file = fopen(filename, "r");

	books_t * bookBorrowed = NULL;

	if (library != NULL) {
		if (file != NULL) {
			printf("\n   On lit le fichier emprunts\n");
			char category[4];
			int bookNb = 0;
			char date[9];

			while (!feof(file)) {
				fscanf(file, "%s %d %s", category, &bookNb, date);
				bookBorrowed = isBookInLibrary(library, category, bookNb);
				insertBorrowing(borrowings, bookBorrowed ,date);
			}
			fclose(file);
		} else {
			printf("\n\033[31m   Nom de fichier pour les emprunts inexistant\033[00m\n");
		}
	} else {
		printf("\n\033[31m   Liste bibliotheque vide\033[00m\n");
	}
}


books_t * isBookInLibrary(library_t * curLib, char category[4], int bookNb) {
	books_t * curBooks = NULL;

	while (curLib != NULL && strcmp(curLib->category, category)) {
		curLib = curLib->next;
	}

	if (curLib != NULL) {
		curBooks = curLib->begBooks;
		while (curBooks != NULL && curBooks->bookNb != bookNb) {
			curBooks = curBooks->next;
		}
	}

	return curBooks;
}


void insertBorrowing(borrowings_t ** borrowings, books_t * bookBorrowed, char date[9]) {
	borrowings_t * curBorrow = *borrowings;
	borrowings_t * elemBorrow = NULL;

	if (bookBorrowed != NULL && bookBorrowed->isBorrowed != true) {
		bookBorrowed->isBorrowed = true;

		elemBorrow = (borrowings_t *)malloc(sizeof(borrowings_t));

		if (elemBorrow != NULL) {
			elemBorrow->bookNb = bookBorrowed->bookNb;
			strcpy(elemBorrow->returnDate, date);

			// fct qui renvoie laddresse de lelem a faire
			if (curBorrow != NULL && atoi(date) > atoi(curBorrow->returnDate)) {
				while (curBorrow->next != NULL && atoi(date) > atoi(curBorrow->next->returnDate)) {
					curBorrow=curBorrow->next;
				}
				elemBorrow->next = curBorrow->next;
				curBorrow->next = elemBorrow;
			} else {
				*borrowings = elemBorrow;
				elemBorrow->next = curBorrow;
			}
		}
	} else {
		printf("\n\033[31m   Livre de la liste à emprunter inexistant\033[00m");
	}
}

// Fct pour supprimer un emprunt
void broughtBackBook(char * filename, library_t ** library, borrowings_t ** borrowings) {
	FILE * file = NULL;
	file = fopen(filename, "r");

	if (*library != NULL) {
		if (file != NULL) {
			char category[4];
			int  bookNb = 0;

			while (!feof(file)) {
				fscanf(file, "%s %d", category, &bookNb);
				deleteBorrowing(borrowings, bookNb);
				isBorrowedToFalse(library, category, bookNb);
			}
		} else {
			printf("\n\033[31m   Nom de fichier pour les retours inexistant\033[00m\n");
		}
	} else {
		printf("\n\033[31m   Liste bibliotheque vide\033[00m\n");
	}
}


void isBorrowedToFalse(library_t ** library, char category[4], int bookNb) {
	library_t * curLib = *library;
	books_t * curBooks = NULL;

	while (curLib != NULL && strcmp(curLib->category,category)) {
		curLib = curLib->next;
	}
	if (curLib != NULL) {
		curBooks = curLib->begBooks;

		while (curBooks != NULL && curBooks->bookNb != bookNb) {
			curBooks = curBooks->next;
		}
	}

	if (curBooks->bookNb == bookNb) {
		curBooks->isBorrowed = false;
	}
}


void deleteBorrowing(borrowings_t ** borrowings, int bookNb) {
	borrowings_t * curBorrow = *borrowings;
	borrowings_t * prevBorrow = *borrowings;

	while (curBorrow != NULL && curBorrow->bookNb != bookNb) {
		prevBorrow = curBorrow;
		curBorrow = curBorrow->next;
	}

	if (curBorrow != NULL) {
		prevBorrow->next = curBorrow->next;
	}
	else {
		prevBorrow->next = NULL;
	}

	if (curBorrow == *borrowings) {
		*borrowings = (*borrowings)->next;
	}

	free(curBorrow);
}
