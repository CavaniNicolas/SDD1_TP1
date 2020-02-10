#ifndef communH
#define communH

//doxygen documentation generator
//greffon pour code

typedef struct books{ //triée selon numero bookNb croissant
	int bookNb;
	char title[11];
	int isBorrowed;
	struct books * next;
}books_t;

typedef struct biblio{ //liste non triée
	char category[4];
	struct books * dbtBooks;
	struct books * finBooks;
	struct biblio * next;
}biblio_t;

typedef struct emprunts{ //triée sur la date retour en croissant
	int bookNb;
	char returnDate[9]; //forme AAAAMMJJ
	struct emprunts * next;
}emprunts_t;

#endif