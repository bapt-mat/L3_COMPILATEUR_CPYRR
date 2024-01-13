/**
 * @file table_declaration.h
 * @author MATHEVON Baptiste
 * @brief TAD implémentation de la table des déclarations
 * @date 19-10-2023
*/
#ifndef TABLE_DECLARATION_H
#define TABLE_DECLARATION_H

#include "../TAD_table_lexico/table_lexico.h"
#include "../TAD_region/region.c"
#include "../Erreurs/erreurs.h"

#define TAILLE_MAX_TABLE_DECLARATION 5000
#define TYPE_B 0
#define VAR 1
#define FCT 2
#define PROC 3
#define PARAM 4
#define TYPE_S 5
#define TYPE_T 6
#define PROC_FCT 7 //juste utiliser pour un warning -> appel (fonction/procedure)

/**
 * @brief Structure d'une ligne de la table des declarations
*/
struct ligne_decl{
    int nature;
    int suivant;
    int region;
    int description;
    int execution;
};

/**
 * @brief Typedef de la table des declarations de taille : TAILLE_MAX_TABLE_DECLARATION (voir #define)
*/
typedef struct ligne_decl tab_declaration[TAILLE_MAX_TABLE_DECLARATION]; 

/**
 * @brief Typedef de la table de représentation des types et des entêtes de sous-programmes
*/
typedef int tab_types[TAILLE_MAX_TABLE_DECLARATION]; //taille suffisante ?

/**
 * @author MATHEVON Baptiste
 * @brief Initialisation de la table des déclarations (toutes les cases sont mises a -1 + insertion des 4 types de bases)
 * @brief Et initialisation de la tables des types et des entêtes de sous-programmes
*/
void init_table_declaration();

/**
 * @author MATHEVON Baptiste
 * @brief Insertion d'une declaration dans la table
 * @param numero_lexico Numero léxicographique du lexème que l'on veut ajouter à la table des déclarations
 * @param nature Nature du lexème à ajouter (VAR, TYPE_S, etc...)
 * @param region Région de déclaration
 * @param description Description de la déclaration
 * @param execution Valeur à l'execution (déplacement pour VAR, région pour FCT, etc...)
 * @return int : Numéro de déclaration
*/
int inserer_declaration(int numero_lexico, int nature, int region, int description, int execution);
/**
 * @author MATHEVON Baptiste
 * @brief Renvoie le numéro de déclaration d'un objet déclaré dans une région accessible depuis la région d'utilisation
 * @param numero_lexico Numéro lexicographique de l'objet
 * @param nature Nature de l'objet (VAR, TYPE_S, etc...)
 * @return int : Si la déclaration existe/est accessible alors numéro de déclaration, sinon 0???
*/
int association_nom(int numero_lexico, int nature);

/** --------------------------------------*
* @author : MATHEVON Baptiste YILDIZ Tolga
* @brief : Récupération du numéro de déclaration d'un argument
*-----------------------------------------*/
int numero_declaration_argument(int num_lexico, int region);

/**
 * @author MATHEVON Baptiste YILDIZ Tolga
 * @brief Récupération de la valeur du champ execution dans la table des déclarations
 * @param num_declaration Numéro de la déclaration
 * @return int : Valeur du champ exécution
*/
int recup_champ_execution(int num_declaration);

/**
 * @author MATHEVON Baptiste YILDIZ Tolga
 * @brief Calcul de la taille d'une dimension d'un tableau
 * @param borne_inf Borne inférieur de la dimension
 * @param borne_sup Borne supérieur de la dimension
 * @return int : Taille de la dimension
*/
int calcul_taille_dim_tableau(int borne_inf, int borne_sup);

/**
 * @author MATHEVON Baptiste
 * @brief Récupération du numéro de déclaration d'un type
 * @param type Type souhaité
 * @param nature Nature de l'objet nécessitant de trouver ce type
 * @return int : numéro de déclaration
*/
int num_declaration_type(char type[], int nature);

/*-- TABLES DES TYPES --*/

/**
 * @author MATHEVON Baptiste
 * @brief Increment le nombres de champs d'une structure dans la table des types au fur et a mesure qu'un champ est traité
 * @param index Position dans la table des types du nombre de champs de la structure actuelle
*/
void incr_index_table_types(int index);

/**
 * @author MATHEVON Baptiste
 * @brief Insertion d'un entier dans la table des types à la position pos
*/
void inserer_table_types_position(int position, int entier);

/**
 * @author MATHEVON Baptiste
 * @brief Insertion d'un entier dans la table des types a la première pos de la table des types
*/
void inserer_table_types(int entier);

/**
 * @author MATHEVON Baptiste
 * @brief Vérifie la déclaration d'une variable
*/
int recup_declaration_variable_param(int num_lex);

/**
 * @author MATHEVON Baptiste GUNES Ozan
 * @brief Vérifie existance d'un champ pour les types structure
*/
int verif_champ_type(int num_lex_type, int num_lex_champ);

/*-- WARNINGS ET ERREURS --*/
/**
 * @author MATHEVON Baptiste GUNES Ozan
 * @brief Affichage d'un Warning en cas de redéclaration
 * @brief Fonction appelée dans inserer_declaration si la déclaration existe déja 
*/
void erreur_redeclaration(int numero_lexico, int nature);

/**
 * @author MATHEVON Baptiste GUNES Ozan
 * @brief Affichage d'un Warning en cas de non déclaration
*/
void erreur_declaration(int numero_lexico, char type_erreur[], int nature);

/*-- AFFICHAGE TERMINAL DES TABLES --*/

/**
 * @author MATHEVON Baptiste
 * @brief Affichage dans le terminal de la table des déclarations
*/
void affichage_table_declaration();

/**
 * @author MATHEVON Baptiste
 * @brief Affichage sur le terminal de la table des types et des entêtes
*/
void affichage_table_types();

#endif
