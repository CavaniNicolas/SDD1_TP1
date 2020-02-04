#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "TP1.h"

// %[^\n] pour recuperer les chaines de caracteres compportant des espaces jusquau premier \n a laide dun scanf
// dans un scanf : %n permet de recuperer le nombre de caractere lu par le scanf
// scanf return le nombre d'arguments quelle a rempli (largumetn %n nest pas pris en compte)

void lireFichier_creerListes(char * filename, biblio_t ** trCat, emprunts_t ** trEmp){
	FILE * file = NULL;
	file = fopen(filename,"r");

	if (file != NULL){
		char nom_categorie[4];
		int taille_categorie=0;
		int i=0;
		int numero;
		char titre[11];

		biblio_t * elemCat;
		biblio_t * courCat = *trCat;

		livres_t * elemLiv;

		while (!feof(file)){
			fscanf(file,"%s %d",nom_categorie, &taille_categorie);
			printf("%s %d\n",nom_categorie,taille_categorie);
			
			elemCat = (biblio_t *)malloc(sizeof(biblio_t));
			
			strcpy(elemCat->categorie,nom_categorie);
			elemCat->dbtLivres=NULL;
			elemCat->finLivres=NULL;
			elemCat->suiv=NULL;

			if (*trCat==NULL){
				*trCat=elemCat;
			}
			else{
				courCat->suiv=elemCat;
			}
			courCat=elemCat;


			for (i=0;i<taille_categorie;i++){
				fscanf(file,"%d %[^\n]",&numero,titre);
				printf("%d %s\n",numero,titre);

				elemLiv = (livres_t *)malloc(sizeof(livres_t));

				elemLiv->numero=numero;
				strcpy(elemLiv->titre,titre);
				elemLiv->BoolEmprunt=0;
				elemLiv->suiv=NULL;

				if (courCat->dbtLivres==NULL){
					courCat->dbtLivres=elemLiv;
				}
				else{
					courCat->finLivres->suiv=elemLiv;
				}
				courCat->finLivres=elemLiv;
			}
		}
		fclose(file);
	}
	else{
		printf("Nom de fichier inexistent\n");
	}
}

int main(int argc, char ** argv){
	if (argc<2){
		printf("Entrez un nom de fichier à lire\n");
	}
	else{
		biblio_t * trCat = NULL;
		emprunts_t * trEmp = NULL;

		lireFichier_creerListes(argv[1], &trCat, &trEmp);
	}

	return 0;
}