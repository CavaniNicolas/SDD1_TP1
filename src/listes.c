#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "commun.h"
#include "listes.h"

// %[^\n] pour recuperer les chaines de caracteres compportant des espaces jusquau premier \n a laide dun scanf
// dans un scanf : %n permet de recuperer le nombre de caractere lu par le scanf
// scanf return le nombre d'arguments quelle a rempli (largumetn %n nest pas pris en compte)

void lireFichier_creerListes(char * filename, biblio_t ** trCat){
	FILE * file = NULL;
	file = fopen(filename,"r");

	if (file != NULL){
		char nom_categorie[4];
		int taille_categorie=0;
		int i=0;
		int numero=0;
		char titre[11];

		biblio_t * elemCat;
		biblio_t * courCat = *trCat;

		livres_t * elemLiv;

		while (!feof(file)){
			fscanf(file,"%s %d",nom_categorie, &taille_categorie);
			// printf("%s %d\n",nom_categorie,taille_categorie);
			
			elemCat = (biblio_t *)malloc(sizeof(biblio_t));
		
			if (elemCat!=NULL){
				// remove_finchaine_r_windows(nom_categorie);
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
					// printf("%d %s\n",numero,titre);

					elemLiv = (livres_t *)malloc(sizeof(livres_t));

					if (elemLiv!=NULL){
						elemLiv->numero=numero;
						remove_finchaine_r_windows(titre);
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
			}
		}
			
		fclose(file);
	}
	else{
		printf("Nom de fichier inexistant\n");
	}
}

void remove_finchaine_r_windows(char * ligne){
	int i=0;
	while (ligne[i]!='\0'){
		i++;
	}
	i--;
	if (ligne[i]=='\r'){
		ligne[i]='\0';
	}
}

void afficher(biblio_t * tr){
	biblio_t * courCat = tr;
	livres_t * courLiv = NULL;
	while (courCat!=NULL){
		printf("%s\n",courCat->categorie);
		courLiv=courCat->dbtLivres;
		while (courLiv!=NULL){
			printf("%d %s %d\n", courLiv->numero, courLiv->titre, courLiv->BoolEmprunt);
			courLiv=courLiv->suiv;
		}
		courCat=courCat->suiv;
	}
}

void libererlistes(biblio_t ** trCat, emprunts_t ** trEmp){
	biblio_t * courCat = *trCat;
	livres_t * courLiv = NULL;
	emprunts_t * courEmp = *trEmp;

	while (*trCat!=NULL){
		courLiv=courCat->dbtLivres;

		while (courCat->dbtLivres!=NULL){
			courLiv=courLiv->suiv;
			free(courCat->dbtLivres);
			courCat->dbtLivres=courLiv;
		}
		
		courCat=courCat->suiv;
		free(*trCat);
		*trCat=courCat;
	}

	while (*trEmp!=NULL){
		courEmp=courEmp->suiv;
		free(*trEmp);
		*trEmp=courEmp;
	}
}
