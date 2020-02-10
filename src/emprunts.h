#ifndef empruntsH
#define empruntsH

void afficherEmprunts(emprunts_t *);

void emprunterLivre(char *, biblio_t *, emprunts_t **);
int chercherExistence(biblio_t *, char[4], int);
void insertionEmprunts(emprunts_t **, int, char[9]);




#endif