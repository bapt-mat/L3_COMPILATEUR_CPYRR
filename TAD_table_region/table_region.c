#include "table_region.h"
/**
 * @file table_region.c
 * @author GUNES Ozane ASSAL Yasser YILDIZ Tolga
 * @brief TAD implémentation de la table des regions
 * @date 22-10-2023
*/

// Attention!!!!! tab_regions est le type, table_regions est la variable
extern tab_regions table_regions;
extern int numero_region;
extern tab_declaration table_declaration;
int nb_regions = 0;


/**
 * @brief initialisation de la table des régions
 * @author GUNES Ozan ASSAL Yasser YILDIZ Tolga 
*/
void initTableRegions(){
    int i;
    for(i=0; i < MAX_REGIONS; i++){
        table_regions[i].taille = 0;
        table_regions[i].NIS = 0;
        table_regions[i].arbre = NULL;
    }
}

/**
 * @brief Remplit une ligne de la table des régions avec les informations données
 * @author GUNES Ozan ASSAL Yasser YILDIZ Tolga
 * @param taille Taille de la région 
 * @param NIS NIS de la région
 * @param a L'arbre de la région
 * @return int : Le nombre total de région incrémenté
*/
int ajouterRegion(int taille, int NIS , arbre a){
    table_regions[nb_regions].taille = taille;
    table_regions[nb_regions].NIS = NIS;
    table_regions[nb_regions].arbre = a; 

    return nb_regions++;
}

/**
 * @brief Affiche toutes les régions sur le terminal
 * @author GUNES Ozan ASSAL Yasser YILDIZ Tolga
*/
void afficherRegions(){
    printf("\n-- TABLE DES REGIONS --\n");

    for (int i = 0; i < nb_regions; i++) {
        printf("[%d] Taille : %d -- NIS : %d -- arbre : %p\n", i, table_regions[i].taille, table_regions[i].NIS, table_regions[i].arbre);
        /* rajouter arbre plus tard*/
        printf("\n");
    }
}


