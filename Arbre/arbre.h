#ifndef _ARBRE_H_
#define _ARBRE_H_

/**
 * @author Principaux: GUNES Ozan, YILDIZ Tolga - Secondaire: ASSAL Yasser
 * @date 28-10-2023
*/

#include <stdio.h>
#include <stdlib.h>

/*
* TYPES DES NOEUDS
*/

#define T_VIDE 0
#define T_LISTE 1
#define T_LISTE_CHAMPS 2
#define T_LISTE_INDICES 3
#define T_LISTE_ARGUMENTS 4
#define T_RETOURNE 5
#define T_IDF 6
#define T_CSTE_E 7
#define T_CSTE_F 8
#define T_CSTE_CHAR 9
#define T_CSTE_BOOL 10
#define T_CSTE_CHAINE 11
#define T_PLUS 12
#define T_MOINS 13
#define T_MULT 14
#define T_DIV 15
#define T_OU 16
#define T_ET 17
#define T_NON 18
#define T_INF 19
#define T_SUP 20
#define T_DOUBLEEGAL 21
#define T_SUP_EGAL 22
#define T_INF_EGAL 23
#define T_SI_ALORS 24
#define T_SI_ALORS_SINON 25
#define T_POUR 26
#define T_TANT_QUE 27
#define T_FAIRE_TANT_QUE 28
#define T_AFFECT 29
#define T_APPEL_PROC 30
#define T_APPEL_FCT 31
#define T_LISTE_ARGUMENTS_ECRIRE 32
#define T_ECRIRE 33
#define T_LISTE_ARGUMENTS_LIRE 34
#define T_LIRE 35
#define T_RANDINT 36

/*****************************************/


/**
 * @brief Structure d'un noeud
*/
struct noeud {
    int type;
    int num_declaration;
    int num_lexico;
    struct noeud * fils;
    struct noeud * frere;
};

/**
 * @brief Typedef d'un arbre 
*/
typedef struct noeud * arbre;

/**
 * @brief retourne un arbre vide 
 * @author Principaux: GUNES Ozan, YILDIZ Tolga - Secondaire: ASSAL Yasser 
 * @return NULL
*/
arbre arbre_vide();


/**
 * @brief Vérifie si l'arbre est vide
 * @author Principaux: GUNES Ozan, YILDIZ Tolga - Secondaire: ASSAL Yasser
 * @param arbre : L'arbre à vérifier
 * @return int : 1 si vide, 0 sinon
*/
int est_arbre_vide(arbre a);

/**
 * @brief Création d'un noeud avec ses information : type, numéro de déclaration et numéro lexicographique
 * @author Principaux: GUNES Ozan, YILDIZ Tolga - Secondaire: ASSAL Yasser
 * @param type : Le type du noeud
 * @param num_lex : Le numéro lexicographique du noeud 
 * @param num_decl : Le numéro de déclaration du noeud  
 * @return arbre ; renvoie le noeud créé avec les champs numero de déclaration, numéro lexicographique, type, son fils et son fils remplient
*/
arbre creer_noeud(int type, int num_lex, int num_decl);

/**
 * @brief ajoute un fils à l'arbre
 * @author Principaux: GUNES Ozan, YILDIZ Tolga - Secondaire: ASSAL Yasser
 * @param arbre a : ajout du noeud dans cet arbre
 * @param arbre fils : noeud ajouté à a 
*/
void ajouter_fils(arbre a, arbre fils);

/**
 * @brief ajoute un frère à l'arbre
 * @author Principaux: GUNES Ozan, YILDIZ Tolga - Secondaire: ASSAL Yasser
 * @param arbre a : ajout du noeud dans cet arbre
 * @param arbre frere : noeud "frère" ajouté à a 
*/
void ajouter_frere(arbre a, arbre frere);

/**
 * @brief Affiche l'arbre en entier 
 * @author Principaux: GUNES Ozan, YILDIZ Tolga - Secondaire: ASSAL Yasser
 * @param a : L'arbre entier a afficher 
*/
void afficher_arbre(arbre a);


/**
 * @brief Affiche le noeud de a 
 * @author Principaux: GUNES Ozan, YILDIZ Tolga - Secondaire: ASSAL Yasser
 * @param a : Le noeud a afficher  
*/
void affichage_arbre (arbre a, int i);

/**
 * @brief détruit l'arbre
 * @param arbre a : arbre à detruire
*/
void detruire_arbre(arbre a);

/* Couleurs dans xterm                                     */
#define couleur(param) printf("\033[%sm",param)

#define NOIR  "30"
#define ROUGE "31"
#define VERT  "32"
#define JAUNE "33"
#define BLEU  "34"
#define CYAN  "36"
#define BLANC "37"
#define REINIT "0"

#endif /*_ARBRE_H_*/
