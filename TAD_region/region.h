/**
 * @file region.h
 * @author MATHEVON Baptiste
 * @brief TAD implémentation de la gestion des régions (pile)
 * @date 31-11-2023
*/
#ifndef __REGION_H__
#define __REGION_H__

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct cellule{
    int valeur;
    struct cellule * suivant;
}cellule;

typedef cellule * pile_region;

/**
 * @brief Initialisation de la pile des régions -> on empile la région du programme (0)
*/
void init_pile_region();

/**
 * @brief La pile des régions est elle vide ?
 * @return int : Oui ou Non
*/
int pile_region_vide();

/**
 * @brief Empile un entier sur la pile des régions
 * @param valeur Numéro de la région a empiler
*/
void empiler_pile_region(int valeur);

/**
 * @brief Depile le sommet de la pile des régions
*/
void depiler_pile_region();

/**
 * @brief Renvoie le sommet de la pile des régions
 * @return int : sommet de la pile des régions 
*/
int sommet_pile_region();

/**
 * @brief Affichage sur le terminal de la pile des régions
*/
void affichage_pile_region();

/**
 * @brief Destruction de la pile des régions, inutile ?
*/
void detruire_pile_region();

/**
 * @brief Permet de récupérer le NIS courant
 * @return int : NIS courant
*/
int niveau_imbrication_statique();

/**
 * @brief Incremente la variable globale numero_region
*/
void incremente_num_region();

#endif
