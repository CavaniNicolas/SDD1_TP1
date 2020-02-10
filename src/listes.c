#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "commun.h"
#include "listes.h"

// %[^\n] pour recuperer les chaines de caracteres compportant des espaces jusquau premier \n a laide dun scanf
// dans un scanf : %n permet de recuperer le nombre de caractere lu par le scanf
// scanf return le nombre d'arguments quelle a rempli (largumetn %n nest pas pris en compte)

void lireFichier_creerListes(char * filename, biblio_t ** trCat) {
	FILE * file = NULL;
	file = fopen(filename,"r");

	if (file != NULL){
		char nom_category[4];
		int taille_category = 0;
		int i = 0;
		int bookNb = 0;
		char title[11];

		biblio_t * elemCat;
		biblio_t * courCat = *trCat;

		books_t * elemLiv;

		while (!feof(file)) {
			fscanf(file,"%s %d", nom_category, &taille_category);
			// printf("%s %d\n",nom_category,taille_category);
			
			elemCat = (biblio_t *)malloc(sizeof(biblio_t));
		
			if (elemCat != NULL) {
				// remove_finchaine_r_windows(nom_category);
				strcpy(elemCat->category, nom_category);
				elemCat->dbtBooks = NULL;
				elemCat->finBooks = NULL;
				elemCat->next = NULL;

				if (*trCat == NULL) {
					*trCat=elemCat;
				}
				else {
					courCat->next = elemCat;
				}
				courCat = elemCat;


				for (i=0; i<taille_category; i++) {
					fscanf(file, "%d %[^\n]", &bookNb, title);
					// printf("%d %s\n",bookNb,title);

					elemLiv = (books_t *)malloc(sizeof(books_t));

					if (elemLiv != NULL) {
						elemLiv->bookNb = bookNb;
						remove_finchaine_r_windows(title);
						strcpy(elemLiv->title, title);
						elemLiv->isBorrowed = 0;
						elemLiv->next = NULL;

						if (courCat->dbtBooks == NULL) {
							courCat->dbtBooks = elemLiv;
						}
						else {
							courCat->finBooks->next = elemLiv;
						}
						courCat->finBooks = elemLiv;
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

void remove_finchaine_r_windows(char * ligne){
	int i = 0;
	while (ligne[i]!='\0') {
		i++;
	}
	i--;
	if (ligne[i] == '\r') {
		ligne[i] = '\0';
	}
}

void afficher(biblio_t * tr) {
	biblio_t * courCat = tr;
	books_t * courLiv = NULL;
	while (courCat != NULL) {
		printf("%s\n", courCat->category);
		courLiv = courCat->dbtBooks;
		while (courLiv != NULL){
			printf("%d %s %d\n", courLiv->bookNb, courLiv->title, courLiv->isBorrowed);
			courLiv = courLiv->next;
		}
		courCat = courCat->next;
	}
}

void libererlistes(biblio_t ** trCat, emprunts_t ** trEmp) {
	biblio_t * courCat = *trCat;
	books_t * courLiv = NULL;
	emprunts_t * courEmp = *trEmp;

	while (*trCat != NULL) {
		courLiv = courCat->dbtBooks;

		while (courCat->dbtBooks != NULL) {
			courLiv = courLiv->next;
			free(courCat->dbtBooks);
			courCat->dbtBooks = courLiv;
		}
		
		courCat = courCat->next;
		free(*trCat);
		*trCat = courCat;
	}

	while (*trEmp != NULL) {
		courEmp = courEmp->next;
		free(*trEmp);
		*trEmp = courEmp;
	}
}
