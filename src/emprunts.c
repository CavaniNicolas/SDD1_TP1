
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "commun.h"
#include "emprunts.h"

void afficherEmprunts(emprunts_t const * trEmp) {
	emprunts_t const * courEmp = trEmp;
	printf("on afficher la liste des emprunts\n");
	while (courEmp != NULL) {
		printf("bookNb:%d  returnDate:%s\n", courEmp->bookNb, courEmp->returnDate);
		courEmp = courEmp->next;
	}
}

// Lit le fichier des emprunts et rempli la liste chainée
void emprunterLivre(char * filename, biblio_t * trCat, emprunts_t ** trEmp){
	FILE * file = NULL;
	file = fopen(filename, "r");

	if (file != NULL){
		printf("on lit le fichier emprunts\n");
		char category[4];
		int bookNb = 0;
		char date[9];

		while (!feof(file)){
			fscanf(file, "%s %d %s", category, &bookNb, date);
			if (chercherExistence(trCat, category, bookNb)) {
				insertionEmprunts(trEmp, bookNb ,date);
			}
		}
		fclose(file);
	}
	else{
		printf("Nom de fichier pour les emprunts inexistant\n");
	}
}

//chercher dans la liste category si le livre emprunté existe
//renvoie 1 si lelement a ete trouve
int chercherExistence(biblio_t * trCat, char category[4], int bookNb) {
	biblio_t * courCat = trCat;
	books_t * courLiv = NULL;
	bool booleen=false;

	while (courCat != NULL && strcmp(courCat->category,category)) {
		courCat=courCat->next;
	}

	if (courCat != NULL){
		courLiv = courCat->dbtBooks;
		while (courLiv != NULL && courLiv->bookNb != bookNb) {
			courLiv=courLiv->next;
		}
	}
	if (courLiv!=NULL){
		booleen=true;
	}
	return booleen;
}

//insere le livre emprunté dans la liste emprunts
void insertionEmprunts(emprunts_t ** trEmp, int bookNb, char date[9]){
	emprunts_t * courEmp = *trEmp;

	emprunts_t * elemEmp = (emprunts_t *)malloc(sizeof(emprunts_t));
	if (elemEmp != NULL){
		elemEmp->bookNb=bookNb;
		strcpy(elemEmp->returnDate,date);

		if (courEmp != NULL && atoi(date) > atoi(courEmp->returnDate)){
			while (courEmp->next!=NULL && atoi(date) > atoi(courEmp->next->returnDate)){
				courEmp=courEmp->next;
			}
			elemEmp->next=courEmp->next;
			courEmp->next=elemEmp;
		}
		else {
			*trEmp=elemEmp;
			elemEmp->next=courEmp;
		}
	}
}