#ifndef empruntsH
#define empruntsH

void displayBorrowings(borrowings_t const *);

// Lit le fichier des emprunts et rempli la liste chainée
void borrowBook(char *, library_t *, borrowings_t **);

// Chercher dans la liste category si le livre emprunté existe
// Renvoie 1 si lelement a ete trouve
// et modifie la valeur de isBorrowed dans la liste library
int isBookInLibrary(library_t *, char[4], int);

// Insere le livre emprunté dans la liste emprunts
void insertBorrowing(borrowings_t **, int, char[9]);

// Lit le fichier des livres rapportés et les supprime de la liste emprunts
// et modifie la valeur de isBorrowed dans la liste library
void broughtBackBook(char *, library_t **, borrowings_t **);

void deleteBorrowing(borrowings_t ** , int );
void isBorrowedToFalse(library_t **, char[4], int);


#endif