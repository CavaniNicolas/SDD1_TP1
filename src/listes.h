#ifndef listesH
#define listesH

void lireFichier_creerListes(char *, biblio_t **);
void afficher(biblio_t *);
void remove_finchaine_r_windows(char *);
void libererlistes(biblio_t **, emprunts_t **);

#endif