#ifndef _ERREURS_H_
#define _ERREURS_H_
#include "../Arbre/arbre.h"

#define code_erreur_declaration_var 1
#define code_erreur_parenthese_ouvrante 2
#define code_erreur_parenthese_fermante 3

/** --------------------------------------*
* @author : MATHEVON Baptiste
* @brief : Affichage de l'erreur quand erreur d'une expression arithmétique
*-----------------------------------------*/
void erreur_exp_arith(int type1, int type_operation, int type2);

/** --------------------------------------*
* @author : MATHEVON Baptiste
* @brief : Affichage de l'erreur quand erreur d'une affectation
* @param type1 : type de l'expression de gauche
* @param type2 : type de l'expression de droite
*-----------------------------------------*/
void erreur_affectation(int type1, int type2);

/**
 * @brief Affichage de l'erreur de l'expression booléenne
 * @author Principal : GUNES Ozan 
 * @param type1 : Le type de l'expression de gauche
 * @param type2 : Le type de l'expression de droite
*/
void erreur_exp_booleenne(int type1, int type2);

/**
 * @brief Affichage de l'erreur des indices
 * @author Principal : GUNES Ozan 
 * @param type_indice : Le type basique de l'indice utilisé 
*/
void erreur_indice_tab(int type_indice);

/**
 * @brief Affichage de l'erreur du nombre des arguments 
 * @author Principal : GUNES Ozan 
 * @param nb_arguments_recu : Le nombre d'arguments recus
 * @param nb_arguments_attendu : Le nombre d'arguments attendus
*/
void erreur_declaration_champ_structure(int num_lex_champ);

/**
 * @brief Affichae l'erreur du nombre des arguments 
 * @author Principal : GUNES Ozan 
 * @param nb_arguments_recu : Le nombre d'arguments recus
 * @param nb_arguments_attendu : Le nombre d'arguments attendus
*/
void erreur_nb_arguments(int nb_arguements_recu, int nb_arguements_attendu);

/** --------------------------------------*
* @author : MATHEVON Baptiste
* @brief : Définition d'un code erreur quand erreur de syntaxe pour affichage au moment de l'appel de yyerror()
* @param code : macro pour le code de l'erreur
*-----------------------------------------*/
void erreur(int code);

/**
 * @brief Affichage du type basique 
 * @author Principal : GUNES Ozan 
 * @param type1: Le type basique utilisé
  * @return char * : int, float, bool ou char
*/
char * type_f (int type1);

/**
 * @brief Verifie si l'indice utilisé est bien dans les dimenssion du tableau
 * @author Principal : GUNES Ozan - Secondaire :
 * @param type1: Type de l'expression 1 
 * @param type2 : Type de l'expression 2
 * @param appel ; nom de l'appel (fonction ou procédure)
*/
void erreur_type_argument(int type1, int type2, int appel);

/**
 * @brief Verifie si le retour est celui d'une fonction
 * @author Principal : GUNES Ozan - Secondaire : YILDIZ Tolga
 * @param region :  region du retour 
 * @return int : 1 si est contenue dans une fonction, 0 sinon
*/
int recherche_indice_fct(int region);

/**
 * @brief Creer le noeud d'un argument d'une procédure ou d'une fonction
 * @author Principal : GUNES Ozan - Secondaire : YILDIZ Tolga
 * @param expression : noeud qui contient l'argument d'un tableau
 * @param numero_argument : le numéro de positionnement de l'argument
 * @param numero_declaration_appel : numero de déclaration de l'appel (fonction ou procédure)
 * @return arbre ; Le noeud indice avec son fils
*/
arbre creer_noeud_argument(arbre expression, int numero_argument, int numero_declaration_appel);

/**
 * @brief Creer le noeud "RETOURNE" d'une fonction
 * @author Principal : GUNES Ozan - Secondaire : YILDIZ Tolga
 * @param retour : noeud qui contient le retour de la fonction
 * @return arbre ; Le noeud "RETOURNE" avec son fils
*/
arbre creer_noeud_retour(arbre retour);

/**
 * @brief Creer le noeud d'un indice d'un tableau
 * @author Principal : GUNES Ozan - Secondaire : YILDIZ Tolga
 * @param a : noeud qui contient l'indice du tableau
 * @param numero_declaration_tableau : numero de déclaration du tableau
 * @return arbre ; Le noeud indice avec son fils
*/
arbre creer_noeud_indice(arbre expression,int numero_declaration_tableau);

/**
 * @brief Creer le noeud des expressions arithmétiques avec les cas d'erreurs
 * @author Principal : MATHEVON Baptiste - Secondaire : YILDIZ Tolga, GUNES Ozan
 * @param expression_gauche : noeud qui contient l'expression de gauche de l'expression arithmétique
 * @param expression_droite : noeud qui contient l'expression de droite de l'expression arithmétique
 * @param type_operation : Le type de l'opération à faire 
 * @return arbre ; Le noeud de l'expression avec son fils et frere
*/
arbre creer_noeud_expression_arithmetique(arbre expression_gauche, arbre expression_droite, int type_operation);

/**
 * @brief Creer le noeud des expressions booléennes avec les cas d'erreurs
 * @author Principal : GUNES Ozan - Secondaire : YILDIZ Tolga
 * @param expression_gauche : noeud qui contient l'expression de gauche de l'expression booléenne
 * @param expression_droite : noeud qui contient l'expression de droite de l'expression booléenne
 * @param type_comparaison : Le noeud du type de comparaison à faire 
 * @return arbre ; Le noeud de l'expression avec son fils et frère
*/
arbre creer_noeud_expression_booleenne_compare(arbre expression_gauche, arbre expression_droite, arbre type_comparaison);

/** --------------------------------------*
* @author : MATHEVON Baptiste
* @brief : Vérification de la déclaration d'un champ dans une structure (et ses sous-structures -> récursif)
*-----------------------------------------*/
int verif_declaration_champ(int num_decl_struct, int num_lex_champ);

#endif