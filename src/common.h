/* --------------------------------------------------------------------------- */
/*  common.h         Contient les déclarations des structures de               */
/*                   listes communes aux autres fichiers du projet             */
/*                                                                             */
/* --------------------------------------------------------------------------- */

#ifndef commonH
#define commonH

/* --------------------------------------------------------------------------- */
/*            Structure pour la liste des catégories (bibliothèque)            */
/*                    Triée selon l'entier bookNb croissant                    */
/* --------------------------------------------------------------------------- */
typedef struct books {
	int bookNb;
	char title[11];
	char isBorrowed;
	struct books * next;
}books_t;


/* --------------------------------------------------------------------------- */
/*             Structure pour la liste des livres d'une catégorie              */
/*                               Liste non triée                               */
/* --------------------------------------------------------------------------- */
typedef struct library {
	char category[4];
	struct books * begBooks;
	struct library * next;
}library_t;


/* --------------------------------------------------------------------------- */
/*                    Structure pour la liste des emprunts                     */
/*                    Triée sur la date retour en croissant                    */
/* --------------------------------------------------------------------------- */
typedef struct borrowings {
	int bookNb;
	char returnDate[9]; // Forme AAAAMMJJ
	struct borrowings * next;
}borrowings_t;


#endif