
#include <stdio.h>
#include <stdlib.h>
#include "commun.h"
#include "emprunts.h"
#include "listes.h"


int main(int argc, char ** argv){
	if (argc<2){
		printf("Entrez un nom de fichier à lire\n");
	}
	else{
		library_t * library = NULL;
		borrowings_t * borrowings = NULL;

		createLibrary(argv[1], &library);
		displayLibrary(library);

		borrowBook("Emprunts.txt", library, &borrowings);

		displayBorrowings(borrowings);
		displayLibrary(library);

		deleteBorrowing(&borrowings, 15);
		displayBorrowings(borrowings);

		freeAllLists(&library, &borrowings);
	}
	return 0;
}