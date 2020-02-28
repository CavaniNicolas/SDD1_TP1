/* --------------------------------------------------------------------------- */
/*  menu.h                                                                     */
/*            Contient les déclarations des fonctions du fichier menu.c        */
/*                                                                             */
/* --------------------------------------------------------------------------- */

#ifndef menuH
#define menuH


/* ---------------------------------------------------------------------- */
/* menu        Fonction de menu (graphique)                               */
/*             On reste dans cette fonction tant qu'on ne choisi pas 0    */
/*                                                                        */
/* En entrée:  library    : pointeur sur la bibliothèque (par adresse)    */
/*             borrowings : pointeur sur la liste emprunts (par adresse)  */
/*                                                                        */
/* En sortie:  void                                                       */
/* ---------------------------------------------------------------------- */
void menu(library_t **, borrowings_t **);


/* ---------------------------------------------------------------------- */
/* menuChoice3      Action à executer lors du choix 3 dans le menu        */
/*                                                                        */
/* En entrée:  library    : pointeur sur la bibliothèque (par valeur)     */
/*             borrowings : pointeur sur la liste emprunts (par adresse)  */
/*                                                                        */
/* En sortie:  void                                                       */
/* ---------------------------------------------------------------------- */
void menuChoice3(library_t *, borrowings_t **);


/* ---------------------------------------------------------------------- */
/* menuChoice4      Action à executer lors du choix 4 dans le menu        */
/*                                                                        */
/* En entrée:  borrowings : pointeur sur la liste emprunts (par valeur)   */
/*                                                                        */
/* En sortie:  void                                                       */
/* ---------------------------------------------------------------------- */
void menuChoice4(borrowings_t *);


/* -------------------------------------------------------------------- */
/* remove_endstr_n        Supprime le caractère \n de fin de chaine     */
/*                        si il existe                                  */
/*                                                                      */
/* En entrée:  line : chaine de caractères                              */
/*                                                                      */
/* En sortie:  void                                                     */
/* -------------------------------------------------------------------- */
void remove_endstr_n(char * line);


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
int isDateInputCorrect(char[9]);


/* ------------------------------------------------------------------------ */
/* findFileName   Modifie la chaine de caractères passées en paramètre,     */
/*                Celle ci prend le  nom du dernier fichier emprunts        */
/*                créé, à lire lors de la prochaine excecution du programme */
/*                                                                          */
/* En entrée:  filenameMax : chaine de caractères                           */
/*                                                                          */
/* En sortie:  void                                                         */
/* ------------------------------------------------------------------------ */
void findFilenameMax(char [22]);


#endif