/* --------------------------------------------------------------------------- */
/*  borrow.h                                                                   */
/*             Contient les déclarations des fonctions du fichier borrow.c     */
/*                                                                             */
/* --------------------------------------------------------------------------- */

#ifndef empruntsH
#define empruntsH


/* ---------------------------------------------------------------------------- */
/* displayBorrowings      Affiche la liste des emprunts                         */
/*                                                                              */
/* En entrée:  curBorrow : pointeur courant sur la liste emprunts (par valeur)  */
/*                                                                              */
/* En sortie:  void                                                             */
/* ---------------------------------------------------------------------------- */
void displayBorrowings(borrowings_t const *);


/* -------------------------------------------------------------------- */
/* borrowBook  Lit le fichier des emprunts et rempli la liste chainée   */
/*                                                                      */
/* En entrée:  filename   : chaine de caractères, nom du fichier        */
/*             library    : pointeur sur la bibliothèque (par valeur)   */
/*             borrowings : pointeur sur la liste emprunts (par adresse)*/
/*                                                                      */
/* En sortie:  void                                                     */
/* -------------------------------------------------------------------- */
void borrowBook(char *, library_t *, borrowings_t **);


/* ----------------------------------------------------------------------- */
/* isBookInLibrary  Cherche dans la bibliothèque si le livre               */
/*                  que l'on veut emprunter existe                         */
/*                                                                         */
/* En entrée:  curLib   : pointeur courant sur la bibliothèque (par valeur)*/
/*             category : categorie du livre recherché                     */
/*             bookNb   : numéro du livre recherché                        */
/*                                                                         */
/* En sortie:  pointeur contenant l'adresse du livre de la bibliothèque    */
/*             que l'on souhaite emprunter, NULL si il n'est pas trouvé    */
/* ----------------------------------------------------------------------- */
books_t * isBookInLibrary(library_t const *, char[4], int);


/* ------------------------------------------------------------------------ */
/* insertBorrowing    Insere le livre emprunté dans la liste emprunts et    */
/*                    modifie la valeur de isBorrowed dans la bibliothèque  */
/*                                                                          */
/* En entrée:  borrowings   : pointeur sur la liste emprunts (par adresse)  */
/*             bookBorrowed : adresse du livre de la bibliothèque que l'on  */
/*                            souhaite emprunter                            */
/*             date         : chaine de caractère, date retour du livre     */
/*                                                                          */
/* En sortie:  void                                                         */
/* ------------------------------------------------------------------------ */
void insertBorrowing(borrowings_t **, books_t * curBooks, char[9]);



/* ----------------------------------------------------------------------- */
/* broughtBackBook  Lit le fichier des retours, supprime les livres        */
/*                  rendus de la liste des emprunts et modifie la          */
/*                  valeur de isBorrowed dans la bibliothèque              */
/*                                                                         */
/* En entrée:  filename   : chaine de caractère, nom du fichier des retours*/
/*             library    : pointeur sur la bibliothèque (par valeur)      */
/*             borrowings : pointeur sur la liste emprunts (par adresse)   */
/*                                                                         */
/* En sortie:  void                                                        */
/* ----------------------------------------------------------------------- */
void broughtBackBook(char *, library_t *, borrowings_t **);


/* ---------------------------------------------------------------------- */
/* deleteBorrowing   Supprime de la liste des emprunts le livre dont      */
/*                   le numéro est passé en paramètre (libération mémoire)*/
/*                                                                        */
/* En entrée:  borrowings : pointeur sur la liste emprunts (par adresse)  */
/*             bookNb     : entier, numéro du livre à supprimer           */
/*                                                                        */
/* En sortie:  void                                                       */
/* ---------------------------------------------------------------------- */
void deleteBorrowing(borrowings_t ** , int);


/* --------------------------------------------------------------------- */
/* isBorrowedToFalse   Passe la valeur de isBorrowed de la bibliothèque  */
/*                     à False (le livre à été rendu)                    */
/*                                                                       */
/* En entrée:  curLib   : pointeur courant sur la liste bibliothèque     */
/*             category : chaine de caractères, categorie du livre rendu */
/*             bookNb   : entier, numéro du livre rendu                  */
/*                                                                       */
/* En sortie:  void                                                      */
/* --------------------------------------------------------------------- */
void isBorrowedToFalse(library_t *, char[4], int);




/* --------------------------------------------------------------------------- */
/* displayBorrowingsBeforeDate  Affiche le numéro et dateRetour des            */
/*                              livres à rendre avant date (en paramètre)      */
/*                                                                             */
/* En entrée:  curBorrow : pointeur courant sur la liste emprunts (par valeur) */
/*             date      : chaine de caractère                                 */
/*                                                                             */
/* En sortie:  void                                                            */
/* --------------------------------------------------------------------------- */
void displayBorrowingsBeforeDate(borrowings_t const *, char[9]);


/* ---------------------------------------------------------------------- */
/* saveBorrowingsInFile   Sauvegarde les emprunts dans un fichier pouvant */
/*                        être lu par borrowBook()                        */
/*                                                                        */
/* En entrée:  filename  : chaine de caractères, nom du fichier           */
/*             library   : pointeur sur la bibliothèque (par valeur)      */
/*             curBorrow : pointeur courant sur la liste des emprunts     */
/*                                                                        */
/* En sortie:  void                                                       */
/* ---------------------------------------------------------------------- */
void saveBorrowingsInFile(char *, library_t const *, borrowings_t const * curBorrow);


/* ---------------------------------------------------------------------- */
/* findCategoryName   Remplie la chaine de caractères passée en paramètre */
/*                    avec le nom de la categorie correspondant au numéro */
/*                    du livre                                            */
/*                                                                        */
/* En entrée:  curLib   : pointeur courant sur la liste bibliothèque      */
/*             bookNb   : entier, numéro du livre                         */
/*             category : chaine de caractères à remplir                  */
/*                                                                        */
/* En sortie:  void                                                       */
/* ---------------------------------------------------------------------- */
void findCategoryName(library_t const *, int, char[4]);


#endif