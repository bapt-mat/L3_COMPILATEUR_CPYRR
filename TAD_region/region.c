/**
 * @file region.c
 * @author MATHEVON Baptiste
 * @brief TAD implémentation de la gestion des régions (pile)
 * @date 31-11-2023
*/
#include "./region.h"

extern pile_region pile_des_regions;
extern int numero_region;

/**
 * @brief Initialisation de la pile des régions -> on empile la région du programme (0)
*/
void init_pile_region(){
    empiler_pile_region(0);
}

/**
 * @brief La pile des régions est elle vide ?
 * @return int : Oui ou Non
*/
int pile_region_vide(){
    return pile_des_regions==NULL;
}

/**
 * @brief Empile un entier sur la pile des régions
 * @param valeur Numéro de la région a empiler
*/
void empiler_pile_region(int valeur){
    pile_region nouveau = (pile_region) malloc (sizeof(cellule));
    if (nouveau == NULL){
        fprintf(stderr,"empiler_pile_region : malloc error\n");
        exit (-1);
    }
    nouveau->valeur=valeur;
    nouveau->suivant=pile_des_regions;
    pile_des_regions=nouveau;
}

/**
 * @brief Depile le sommet de la pile des régions
*/
void depiler_pile_region(){
    pile_region courant = pile_des_regions;
    if (pile_region_vide()){
        fprintf(stdout,"La pile des régions est déja vide\n");
        exit(0);
    }
    pile_des_regions=courant->suivant;
    free(courant);
}

/**
 * @brief Renvoie le sommet de la pile des régions
 * @return int : sommet de la pile des régions 
*/
int sommet_pile_region(){
    if (pile_region_vide()){
        fprintf(stderr,"La pile des régions est vide -> pas de sommet\n");
        exit(-1);
    }
    return pile_des_regions->valeur;
}

/**
 * @brief Affichage sur le terminal de la pile des régions
*/
void affichage_pile_region(){
    printf("-- PILE DES REGIONS --\n");
    pile_region courant=pile_des_regions;

    if (pile_region_vide()){
        printf("VIDE\n");
    }
    else{
        while(courant!=NULL){
            printf("|%d|\n", courant->valeur);
            courant=courant->suivant;
        }
    }
}

/**
 * @brief Destruction de la pile des régions, inutile ?
*/
void detruire_pile_region(){
    while(pile_des_regions!=NULL){
        depiler_pile_region();
    }
}

/**
 * @brief Permet de récupérer le NIS courant
 * @return int : NIS courant
*/
int niveau_imbrication_statique(){
    int nis=0;
    pile_region courant = pile_des_regions;
    while(courant!=NULL){
        nis+=1;
        courant=courant->suivant;
    }
    return nis;
}

/**
 * @brief Incremente la variable globale numero_region
*/
void incremente_num_region(){
    numero_region+=1;
}