#ifndef listesH
#define listesH

/* -------------------------------------------------------------------- */
/* createLibrary                                                        */
/*                                                                      */
/* En entrée:                                                           */
/*                                                                      */
/*                                                                      */
/*                                                                      */
/* En sortie:  void                                                     */
/* -------------------------------------------------------------------- */
int createLibrary(char *, library_t **);


/* ---------------------------------------------------------------------------- */
/* fillBooksInLibrary   creer et rempli la liste chainée contenant les          */
/*                      livres d'une catégorie                                  */
/*                                                                              */
/* En entrée:  file         : fichier "Livres.txt"                              */
/*             curLib       : pointeur courant sur la bibliothèque (par valeur) */
/*             categorySize : entier, nombre de livres dans la catégorie        */
/*                                                                              */
/* En sortie:  void                                                             */
/* ---------------------------------------------------------------------------- */
int fillBooksInLibrary(FILE *, library_t *, int);

//________________________________________________________________________________________________________



/* ------------------------------------------ */
/* createLibrary_OLD                          */
/*                                            */
/* En entrée:                                 */
/*                                            */
/* En sortie:  void                           */
/* ------------------------------------------ */
void createLibrary_OLD(char *, library_t **);


/* -------------------------------------------------------------------- */
/* displayLibrary                                                       */
/*                                                                      */
/* En entrée:                                                           */
/*                                                                      */
/*                                                                      */
/*                                                                      */
/* En sortie:  void                                                     */
/* -------------------------------------------------------------------- */
void displayLibrary(library_t *);


/* -------------------------------------------------------------------- */
/* remove_endstr_r_windows                                              */
/*                                                                      */
/* En entrée:                                                           */
/*                                                                      */
/*                                                                      */
/*                                                                      */
/* En sortie:  void                                                     */
/* -------------------------------------------------------------------- */
void remove_endstr_r_windows(char *);


/* -------------------------------------------------------------------- */
/* freeAllLists                                                         */
/*                                                                      */
/* En entrée:                                                           */
/*                                                                      */
/*                                                                      */
/*                                                                      */
/* En sortie:  void                                                     */
/* -------------------------------------------------------------------- */
void freeAllLists(library_t **, borrowings_t **);

#endif