/* --------------------------------------------------------------------------- */
/*  lists.h                                                                    */
/*            Contient les déclarations des fonctions du fichier lists.c       */
/*                                                                             */
/* --------------------------------------------------------------------------- */

#ifndef listsH
#define listsH


/* -------------------------------------------------------------------- */
/* createLibrary   Creer la bibliothèque (liste chainée library)        */
/*                                                                      */
/* En entrée:  filename : nom du fichier à lire pour remplir la liste   */
/*             library  : pointeur sur la bibliothèque (par adresse)    */
/*                                                                      */
/* En sortie:  int : Retour d'erreur, 1 si reussi, 0 sinon              */
/* -------------------------------------------------------------------- */
int createLibrary(char *, library_t **);


/* ------------------------------------------------------------------------------- */
/* createCategory   Creer une categorie et l'ajoute dans la bibliothèque (en tête) */
/*                                                                                 */
/* En entrée:  library  : pointeur sur la bibliothèque (par adresse)               */
/*             category : nom de la catégorie en 3 caractères max                  */
/*                                                                                 */
/* En sortie:  int : Retour d'erreur, 1 si reussi, 0 sinon                         */
/* ------------------------------------------------------------------------------- */
int createCategory (library_t **, char[4]);


/* ----------------------------------------------------------------------------------- */
/* createBook   Creer un livre et l'ajoute à la fin de la liste des livres             */
/*              de la même catégorie                                                   */
/*                                                                                     */
/* En entrée:   library  : pointeur sur la bibliothèque (par adresse)                  */
/*              lastBook : pointeur sur le dernier livre de la categorie (par adresse) */
/*              bookNb   : entier, numero du livre                                     */
/*              title    : chaine de caractères, nom du livre                          */
/*                                                                                     */
/* En sortie:  int : Retour d'erreur, 1 si reussi, 0 sinon                             */
/* ----------------------------------------------------------------------------------- */
int createBook(library_t **, books_t **, int, char[11]);


/* -------------------------------------------------------------------- */
/* displayLibrary      Affiche la bibliothèque                          */
/*                                                                      */
/* En entrée:  curLib : pointeur sur la bibliothèque (par valeur)       */
/*                                                                      */
/* En sortie:  void                                                     */
/* -------------------------------------------------------------------- */
void displayLibrary(library_t const *);


/* -------------------------------------------------------------------- */
/* remove_endstr_r_windows   Supprime le caractère \r de fin de chaine  */
/*                           si il existe                               */
/*                                                                      */
/* En entrée:  line : chaine de caractères                              */
/*                                                                      */
/* En sortie:  void                                                     */
/* -------------------------------------------------------------------- */
void remove_endstr_r_windows(char *);


/* -------------------------------------------------------------------- */
/* freeLibrary            Libère la mémoire                             */
/*                                                                      */
/* En entrée:  library : pointeur sur la bibliothèque (par adresse)     */
/*                                                                      */
/* En sortie:  void                                                     */
/* -------------------------------------------------------------------- */
void freeLibrary(library_t **);


#endif