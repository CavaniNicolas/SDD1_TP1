#ifndef menuH
#define menuH

/* -------------------------------------------------------------------- */
/* menu         Fonction de menu (graphique)                            */
/*                                                                      */
/* En entrée:  library    :    pointeur sur la bibliothèque (adresse)   */
/*             borrowings : pointeur sur la liste emprunts (adresse)    */
/*                                                                      */
/*                                                                      */
/* En sortie:  int                                                      */
/* -------------------------------------------------------------------- */
int menu(library_t **, borrowings_t **);

/* ------------------------------------------------ */
/* emptyBuffer       Vide le Buffer                 */
/*                                                  */
/* En entrée:  void                                 */
/*                                                  */
/* En sortie:  void                                 */
/* ------------------------------------------------ */
void emptyBuffer();


/* -------------------------------------------------------------------- */
/* isDateInputCorrect    Verifie si la chaine passée en paramètre est   */
/*                       une date de la forme AAAAMMJJ                  */
/*                                                                      */
/* En entrée:  date : chaine de caractères                              */
/*                                                                      */
/* En sortie:  int  : 1 si reussi (format de la date conforme), 0 sinon */
/* -------------------------------------------------------------------- */
int isDateInputCorrect(char date[9]);


#endif