#ifndef communH
#define communH

//doxygen documentation generator
//greffon pour code

typedef struct livres{ //triée selon numero croissant
	int numero;
	char titre[11];
	int BoolEmprunt;
	struct livres * suiv;
}livres_t;

typedef struct biblio{ //liste non triée
	char categorie[4];
	struct livres * dbtLivres;
	struct livres * finLivres;
	struct biblio * suiv;
}biblio_t;

typedef struct emprunts{ //triée sur la date retour en croissant
	int numero;
	char DateRetour[9]; //forme AAAAMMJJ
	struct emprunts * suiv;
}emprunts_t;

#endif