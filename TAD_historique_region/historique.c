/**
 * @file historique.c
 * @author ASSAL Yasser YILDIZ Tolga GUNES Ozan
 * @brief Historique de la table des régions avec leur NIS
 * @date 08-11-2023
*/

#include "./historique.h"

extern int numero_region;
extern historique_region historique_reg ;

/**
 * @brief Fonction qui ajoute un nouveau num_region à l'historique lorsqu'on change de region
 * @author ASSAL Yasser YILDIZ Tolga GUNES Ozan
 * @param numero_region Le numéro de région qu'on va ajouter à l'historique de la table des régions
 * @param NIS NIS de la région "num_region"
*/

void ajout_region(int numero_region, int NIS){
    historique_reg[numero_region].numero_region = numero_region ;
    historique_reg[numero_region].NIS = NIS ;
}

/**
 * @brief Fonction qui renvoie le NIS du numero_region qu'on veut
 * @author ASSAL Yasser YILDIZ Tolga GUNES Ozan
 * @param numero_region numero_region dans historique
 * @return int : NIS de la région qu'on veut
*/
int nis_region(int numero_region){
    return historique_reg[numero_region].NIS ;
}

/**
 * @brief Affiche l'historique de la table des régions
 * @author ASSAL Yasser YILDIZ Tolga GUNES Ozan
*/

void afficher_historique(){
    int i ;
    for(i = 0; i < numero_region; i++){
        printf("numero_region %d -> NIS %d \n",historique_reg[i].numero_region, historique_reg[i].NIS);
    }
}
