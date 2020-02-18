#ifndef empruntsH
#define empruntsH

void displayBorrowings(borrowings_t const *);

// Lit le fichier des emprunts et rempli la liste chainée
void borrowBook(char *, library_t *, borrowings_t **);

// Chercher dans la liste category si le livre emprunté existe
// Renvoie l'adresse du livre si il a ete a ete trouve, NULL sinon
books_t * isBookInLibrary(library_t *, char[4], int);

// Insere le livre emprunté dans la liste emprunts
// et modifie la valeur de isBorrowed dans la liste library
void insertBorrowing(borrowings_t **, books_t * curBooks, char[9]);


// Lit le fichier des livres rapportés et les supprime de la liste emprunts
// et modifie la valeur de isBorrowed dans la liste library
void broughtBackBook(char *, library_t **, borrowings_t **);

void deleteBorrowing(borrowings_t ** , int );
void isBorrowedToFalse(library_t **, char[4], int);



/*
interface : 
    lexecutable se lance,
    lutilisateur clic, le fichier des emprunts est lu, puis le fichier des retours est lu,
        (donc les listes sont créées et les actions effectuées dans cet ordre)
    
    menu :
        lutilisateur peut:
            - afficher les listes:
                        la bibliotheque
                        les emprunts
                        la liste des livres dont la date de retour est inférieure à une date donnée

            - demander de lire le ficher retour

            - generer le fichier sauvegarde des emprunts (on ecrase)
                (sauf: le nom du fichier prend la date/heure de la sauvegarde, et
                        lors de la prochaine execution, le fichier emprunts avec la date la plus elevée est lu)

            - quitter
*/


#endif