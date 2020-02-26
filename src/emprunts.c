
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "commun.h"
#include "emprunts.h"


void displayBorrowings(borrowings_t const * curBorrow) {
	printf("\n\033[32m   On affiche la liste des emprunts :\033[00m\n");
	
	if (curBorrow != NULL) {
		while (curBorrow != NULL) {
			printf("\tbookNb: \033[35m%d\033[00m  returnDate: \033[35m%s\033[00m\n", curBorrow->bookNb, curBorrow->returnDate);
			curBorrow = curBorrow->next;
		}
	} else {
		printf("\n\033[31m   Liste emprunts vide\033[00m\n");
	}

}


void borrowBook(char * filename, library_t * library, borrowings_t ** borrowings) {
	FILE * file = NULL;
	file = fopen(filename, "r");

	books_t * bookBorrowed = NULL;

	if (library != NULL) {

		if (file != NULL) {
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
		printf("\n\033[31m   Bibliotheque vide\033[00m\n");
	}
}


books_t * isBookInLibrary(library_t const * curLib, char category[4], int bookNb) {
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

	// } else { Livre de la liste à emprunter inexistant }
	}
}


void broughtBackBook(char * filename, library_t * library, borrowings_t ** borrowings) {
	FILE * file = NULL;
	file = fopen(filename, "r");

	if (library != NULL) {

		if (file != NULL) {
			char category[4];
			int  bookNb = 0;

			while (!feof(file)) {
				fscanf(file, "%s %d", category, &bookNb);
				deleteBorrowing(borrowings, bookNb);
				isBorrowedToFalse(library, category, bookNb);
			}

			fclose(file);
		} else {
			printf("\n\033[31m   Nom de fichier pour les retours inexistant\033[00m\n");
		}

	} else {
		printf("\n\033[31m   Liste bibliotheque vide\033[00m\n");
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
	} else {
		prevBorrow->next = NULL;
	}

	if (curBorrow == *borrowings) {
		*borrowings = (*borrowings)->next;
	}

	free(curBorrow);
}


void isBorrowedToFalse(library_t * curLib, char category[4], int bookNb) {
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


void displayBorrowingsBeforeDate(borrowings_t const * curBorrow, char date[9]) {
	int i = 0;

	printf("\n");
	while (curBorrow != NULL && atoi(curBorrow->returnDate) < atoi(date)) {
		printf("   Livre numero : \033[35m%d\033[00m à rendre avant le \033[35m%s\033[00m\n", curBorrow->bookNb, curBorrow->returnDate);
		curBorrow = curBorrow->next;
		i++;
	}

	if (i == 0) {
		printf("   Aucun livre à rendre avant cette date\n");
	}
}


void saveBorrowingsInFile(char * filename, library_t const * library, borrowings_t const * curBorrow) {
	FILE * file = NULL;
	file = fopen(filename, "w");
	char category[4];

	printf("\n   fichier créé : \033[35m%s\033[00m\n", filename);

	while (curBorrow != NULL) {
		findCategoryName(library, curBorrow->bookNb, category);
		fprintf(stdout, "      %s %d %s\n", category, curBorrow->bookNb, curBorrow->returnDate);
		fprintf(file, "%s %d %s", category, curBorrow->bookNb, curBorrow->returnDate);
		curBorrow = curBorrow->next;

		if (curBorrow != NULL) {
			fprintf(file, "\n");
		}
	}

	fclose(file);
}


void findCategoryName(library_t const * curLib, int bookNb, char category[4]) {
	int isfound = 0;
	books_t * curBooks = NULL;

	while (curLib != NULL && isfound == 0) {
		strcpy(category, curLib->category);
		curBooks = curLib->begBooks;

		while (curBooks != NULL && curBooks->bookNb != bookNb) {
			curBooks = curBooks->next;
		}

		if (curBooks != NULL) {
			isfound = 1;
		}

		curLib = curLib->next;
	}
}
