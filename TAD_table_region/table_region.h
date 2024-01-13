/**
 * @file table_region.h
 * @author GUNES Ozane ASSAL Yasser YILDIZ Tolga 
 * @brief TAD pour la table des régions
 * @date 22-10-2023
 */
#ifndef TABLE_REGION_H
#define TABLE_REGION_H

#include <stdio.h>
#include <stdlib.h>
#include "../Arbre/arbre.h"
#include "../TAD_table_declaration/table_declaration.c"


#define MAX_REGIONS 100 /* la taille maximum de régions */

/**
 * @brief Structure pour une région
 */
struct ligneRegion{
    int taille;
    int NIS; 
    arbre arbre;
    struct ligneRegion *suivant;
};

typedef struct ligneRegion ligneRegion; 

/**
 * @brief Typedef pour une table des régions
 */

typedef ligneRegion tab_regions[MAX_REGIONS];
int region_courante = 0;


/**
 * @brief initialisation de la table des régions
 * @author GUNES Ozan ASSAL Yasser YILDIZ Tolga 
*/
void initTableRegions();

/**
 * @brief Remplit une ligne de la table des régions avec les informations données
 * @author GUNES Ozan ASSAL Yasser YILDIZ Tolga
 * @param taille Taille de la région 
 * @param NIS NIS de la région
 * @param a L'arbre de la région
 * @return int : Le nombre total de région incrémenté
*/
int ajouterRegion(int taille, int NIS, arbre a);

/**
 * @brief Affiche toutes les régions sur le terminal
 * @author GUNES Ozan ASSAL Yasser YILDIZ Tolga
*/
void afficherRegions();


#endif
