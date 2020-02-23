#ifndef empruntsH
#define empruntsH

/* --------------------------------------------------------------------------------- */
/* displayBorrowings      Affiche la liste des emprunts                              */
/*                                                                                   */
/* En entrée:  borrowings : pointeur constant sur la liste emprunts (par valeur)     */
/*                                                                                   */
/* En sortie:  void                                                                  */
/* --------------------------------------------------------------------------------- */
void displayBorrowings(borrowings_t const *);


/* -------------------------------------------------------------------- */
/* borrowBook  Lit le fichier des emprunts et rempli la liste chainée   */
/*                                                                      */
/* En entrée:  filename : chaine de caractères, nom du fichier          */
/*             library : pointeur sur la bibliothèque (par valeur)      */
/*             borrowings : pointeur la liste emprunts (par adresse)    */
/*                                                                      */
/* En sortie:  void                                                     */
/* -------------------------------------------------------------------- */
void borrowBook(char *, library_t *, borrowings_t **);


/* ----------------------------------------------------------------------- */
/* isBookInLibrary  Cherche dans la bibliothèque si le livre               */
/*                  que l'on veut emprunter existe                         */
/*                                                                         */
/* En entrée:  curLib : pointeur courant sur la bibliothèque (par valeur)  */
/*             category : categorie du livre recherché                     */
/*             bookNb : numéro du livre recherché                          */
/*                                                                         */
/* En sortie:  pointeur contenant l'adresse du livre de la bibliothèque    */
/*             que l'on souhaite emprunter, NULL si il n'est pas trouvé    */
/* ----------------------------------------------------------------------- */
books_t * isBookInLibrary(library_t *, char[4], int);


/* ------------------------------------------------------------------------ */
/* insertBorrowing    Insere le livre emprunté dans la liste emprunts et    */
/*                    modifie la valeur de isBorrowed dans la bibliothèque  */
/*                                                                          */
/* En entrée:  borrowings : pointeur sur la liste emprunts (par adresse)    */
/*             bookBorrowed : adresse du livre de la bibliothèque que l'on  */
/*                            souhaite emprunter                            */
/*             date : chaine de caractère, date retour du livre             */
/*                                                                          */
/* En sortie:  void                                                         */
/* ------------------------------------------------------------------------ */
void insertBorrowing(borrowings_t **, books_t * curBooks, char[9]);



// Lit le fichier des livres rapportés et les supprime de la liste emprunts
// et modifie la valeur de isBorrowed dans la liste library

/* -------------------------------------------------------------------- */
/* broughtBackBook                                                      */
/*                                                                      */
/* En entrée:                                                           */
/*                                                                      */
/*                                                                      */
/*                                                                      */
/* En sortie:  void                                                     */
/* -------------------------------------------------------------------- */
void broughtBackBook(char *, library_t **, borrowings_t **);


/* -------------------------------------------------------------------- */
/* deleteBorrowing                                                      */
/*                                                                      */
/* En entrée:                                                           */
/*                                                                      */
/*                                                                      */
/*                                                                      */
/* En sortie:  void                                                     */
/* -------------------------------------------------------------------- */
void deleteBorrowing(borrowings_t ** , int );


/* -------------------------------------------------------------------- */
/* isBorrowedToFalse                                                    */
/*                                                                      */
/* En entrée:                                                           */
/*                                                                      */
/*                                                                      */
/*                                                                      */
/* En sortie:  void                                                     */
/* -------------------------------------------------------------------- */
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