/* --------------------------------------------------------------------------- */
/*  menu.h                                                                     */
/*            Contient les déclarations des fonctions du fichier menu.c        */
/*                                                                             */
/* --------------------------------------------------------------------------- */

#ifndef menuH
#define menuH


/* ---------------------------------------------------------------------- */
/* menu        Fonction de menu (graphique)                               */
/*                                                                        */
/* En entrée:  library    : pointeur sur la bibliothèque (par adresse)    */
/*             borrowings : pointeur sur la liste emprunts (par adresse)  */
/*                                                                        */
/* En sortie:  int : On reste dans le menu tant que menu ne renvoie pas 0 */
/* ---------------------------------------------------------------------- */
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
int isDateInputCorrect(char[9]);


/* ---------------------------------------------------------------------- */
/* createFilename  Remplie la chaine de caractères passée en paramètre    */
/*                 avec la date et l'heure à laquelle est créé le fichier */
/*                                                                        */
/* En entrée:  filename : chaine de caractères                            */
/*                                                                        */
/* En sortie:  void                                                       */
/* ---------------------------------------------------------------------- */
void createFilename(char *);


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