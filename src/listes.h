#ifndef listesH
#define listesH

void createLibrary(char *, library_t **);
void displayLibrary(library_t *);
void remove_endstr_r_windows(char *);
void freeAllLists(library_t **, borrowings_t **);

#endif