#ifndef __PILE_EXECUTION_H__
#define __PILE_EXECUTION_H__

#include "../TAD_table_region/table_region.c"

#define CELLULE_VIDE 'n'
#define CELLULE_IDF 'i'
#define CELLULE_ENTIER 'e'
#define CELLULE_REEL 'r'
#define CELLULE_CHAR 'c'
#define CELLULE_CHAIN_DYN 'd'
#define CELLULE_CHAIN_STAT 's'
#define CELLULE_TYPE_S_T 't'
#define CELLULE_BOOL 'b'

union cellule_pile{
    int entier ;
    float reel ;
    char booleen ;
    char caractere ;
};

struct valeur_cellule{
    union cellule_pile valeur;
    char type;
};

typedef struct valeur_cellule pile_execution[5000]; //malloc ?


void affichage_pile();


struct valeur_cellule parcours_arbre(arbre a, int num_region_appelante);

#endif // __PILE_EXECUTION_H__