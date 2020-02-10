
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "commun.h"
#include "emprunts.h"

void afficherEmprunts(emprunts_t * trEmp){
	emprunts_t * courEmp=trEmp;
	printf("on afficher la liste des emprunts\n");
	while (courEmp!=NULL){
		printf("numero:%d  DateRetour:%s\n",courEmp->numero, courEmp->DateRetour);
		courEmp=courEmp->suiv;
	}
}

//lit le fichier des emprunts et rempli la liste chainée
void emprunterLivre(char * filename, biblio_t * trCat, emprunts_t ** trEmp){
	FILE * file = NULL;
	file = fopen(filename,"r");

	if (file != NULL){
		printf("on lit le fichier emprunts\n");
		char categorie[4];
		int numero=0;
		char date[9];

		while (!feof(file)){
			fscanf(file, "%s %d %s", categorie, &numero, date);
			if (chercherExistence(trCat, categorie, numero)){
				insertionEmprunts(trEmp, numero,date);
			}
		}
		fclose(file);
	}
	else{
		printf("Nom de fichier pour les emprunts inexistant\n");
	}
}

//chercher dans la liste Categories si le livre emprunté existe
//renvoie 1 si lelement a ete trouve
int chercherExistence(biblio_t * trCat, char categorie[4], int numero){
	biblio_t * courCat = trCat;
	livres_t * courLiv = NULL;
	bool booleen=false;

	while (courCat != NULL && strcmp(courCat->categorie,categorie)){
		courCat=courCat->suiv;
	}

	if (courCat != NULL){
		courLiv = courCat->dbtLivres;
		while (courLiv != NULL && courLiv->numero!=numero){
			courLiv=courLiv->suiv;
		}
	}
	if (courLiv!=NULL){
		booleen=true;
	}
	return booleen;
}

//insere le livre emprunté dans la liste emprunts
void insertionEmprunts(emprunts_t ** trEmp, int numero, char date[9]){
	emprunts_t * courEmp = *trEmp;

	emprunts_t * elemEmp = (emprunts_t *)malloc(sizeof(emprunts_t));
	if (elemEmp != NULL){
		elemEmp->numero=numero;
		strcpy(elemEmp->DateRetour,date);

		if (courEmp != NULL && atoi(date) > atoi(courEmp->DateRetour)){
			while (courEmp->suiv!=NULL && atoi(date) > atoi(courEmp->suiv->DateRetour)){
				courEmp=courEmp->suiv;
			}
			elemEmp->suiv=courEmp->suiv;
			courEmp->suiv=elemEmp;
		}
		else {
			*trEmp=elemEmp;
			elemEmp->suiv=courEmp;
		}
	}
}