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


/* ---------------------------------------------------------------------------- */
/* fillBooksInLibrary   Creer et rempli la liste chainée contenant les          */
/*                      livres d'une catégorie                                  */
/*                                                                              */
/* En entrée:  file         : fichier ouvert dans createLibrary ("library.txt") */
/*             curLib       : pointeur courant sur la bibliothèque (par valeur) */
/*             categorySize : entier, nombre de livres dans la catégorie        */
/*                                                                              */
/* En sortie:  int : Retour d'erreur, 1 si reussi, 0 sinon                      */
/* ---------------------------------------------------------------------------- */
int fillBooksInLibrary(FILE *, library_t *, int);


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