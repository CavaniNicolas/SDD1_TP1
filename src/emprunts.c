
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "commun.h"
#include "emprunts.h"

void displayBorrowings(borrowings_t const * borrowings) {
	borrowings_t const * curBorrow = borrowings;
	printf("\non affiche la liste des emprunts\n");

	while (curBorrow != NULL) {
		printf("bookNb:%d  returnDate:%s\n", curBorrow->bookNb, curBorrow->returnDate);
		curBorrow = curBorrow->next;
	}

}

// Fct pour ajouter un emprunt
void borrowBook(char * filename, library_t * library, borrowings_t ** borrowings) {
	FILE * file = NULL;
	file = fopen(filename, "r");

	if (file != NULL) {
		printf("on lit le fichier emprunts\n");
		char category[4];
		int bookNb = 0;
		char date[9];

		while (!feof(file)) {
			fscanf(file, "%s %d %s", category, &bookNb, date);
			if (isBookInLibrary(library, category, bookNb)) {
				insertBorrowing(borrowings, bookNb ,date);
			}
		}
		fclose(file);
	}
	else{
		printf("Nom de fichier pour les emprunts inexistant\n");
	}
}


int isBookInLibrary(library_t * library, char category[4], int bookNb) {
	library_t * curLib = library;
	books_t * curBooks = NULL;
	bool isIn = false;

	while (curLib != NULL && strcmp(curLib->category, category)) {
		curLib = curLib->next;
	}

	if (curLib != NULL) {
		curBooks = curLib->begBooks;
		while (curBooks != NULL && curBooks->bookNb != bookNb) {
			curBooks = curBooks->next;
		}
	}
	if (curBooks != NULL) {
		curBooks->isBorrowed = true;
		isIn = true;
	}
	return isIn;
}


void insertBorrowing(borrowings_t ** borrowings, int bookNb, char date[9]) {
	borrowings_t * curBorrow = *borrowings;

	borrowings_t * elemBorrow = (borrowings_t *)malloc(sizeof(borrowings_t));

	if (elemBorrow != NULL) {
		elemBorrow->bookNb = bookNb;
		strcpy(elemBorrow->returnDate, date);

		if (curBorrow != NULL && atoi(date) > atoi(curBorrow->returnDate)) {
			while (curBorrow->next != NULL && atoi(date) > atoi(curBorrow->next->returnDate)) {
				curBorrow=curBorrow->next;
			}
			elemBorrow->next = curBorrow->next;
			curBorrow->next = elemBorrow;
		}
		else {
			*borrowings = elemBorrow;
			elemBorrow->next = curBorrow;
		}
	}
}

// Fct pour supprimer un emprunt
void broughtBackBook(char * filename, library_t ** library, borrowings_t ** borrowings) {
	FILE * file = NULL;
	file = fopen(filename, "r");

	if (file != NULL) {
		char category[4];
		int bookNb = 0;

		while (!feof(file)) {
			fscanf(file, "%s %d", category, &bookNb);
			deleteBorrowing(borrowings, bookNb);
			isBorrowedToFalse(library, category, bookNb);

		}
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
