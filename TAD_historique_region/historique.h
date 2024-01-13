#ifndef HISTORIQUE_H
#define HISTORIQUE_H


/**
 * @file historique.c
 * @author ASSAL Yasser YILDIZ Tolga GUNES Ozan
 * @brief Historique de la tanme des régions avec leur NIS
 * @date 08-11-2023
*/

#define MAX_REGION 100


/**
 *  @brief Structure d'une ligne qui à chaque numero_region associe son nis
*/
struct historique_region{
    int numero_region;
    int NIS;
};

/**
 * @brief historique permettant de stocker les numéros de régions et leur nis pour les ajouter correctement dans la table des regions
*/
typedef struct historique_region historique_region[100] ;

/**
 * @brief Fonction qui ajoute un nouveau num_region à l'historique lorsqu'on change de region
 * @author ASSAL Yasser YILDIZ Tolga GUNES Ozan
 * @param numero_region Le numéro de région qu'on va ajouter à l'historique de la table des régions
 * @param NIS NIS de la région "num_region"
*/
void ajout_region(int numero_region, int NIS);

/**
 * @brief Fonction qui renvoie le NIS du numero_region qu'on veut
 * @author ASSAL Yasser YILDIZ Tolga GUNES Ozan
 * @param numero_region numero_region dans historique
 * @return int : NIS de la région qu'on veut
*/
int nis_region(int numero_region);

/**
 * @brief Affiche l'historique de la table des régions
 * @author ASSAL Yasser YILDIZ Tolga GUNES Ozan
*/
void afficher_historique();

#endif