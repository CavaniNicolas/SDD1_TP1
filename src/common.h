/* --------------------------------------------------------------------------- */
/*                                                                             */
/*                                                                             */
/*                                                                             */
/* --------------------------------------------------------------------------- */

#ifndef commonH
#define commonH
#include <stdbool.h>

/* --------------------------------------------------------------------------- */
/*                                                                             */
/*                                                                             */
/*                                                                             */
/* --------------------------------------------------------------------------- */
typedef struct books{ // Triée selon numero bookNb croissant
	int bookNb;
	char title[11];
	bool isBorrowed;
	struct books * next;
}books_t;


typedef struct library{ // Liste non triée
	char category[4];
	struct books * begBooks;
	struct library * next;
}library_t;


typedef struct borrowings{ // Triée sur la date retour en croissant
	int bookNb;
	char returnDate[9]; // Forme AAAAMMJJ
	struct borrowings * next;
}borrowings_t;


#endif