/**
 * @file table_lexico.h
 * @author MATHEVON Baptiste
 * @brief TAD implémentation de la table lexicographique
 * @date 15-10-2023
*/
#ifndef TABLE_LEXICO_H
#define TABLE_LEXICO_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>


#define TAILLE_MAX_TABLE_LEXICO 500
#define TAILLE_MAX_LEXEME 500

/**
 * @brief Structure d'une ligne de la table lexicographique
*/
struct ligne_lex{
    int longueur;
    char lexeme[TAILLE_MAX_LEXEME];
    int suivant;
};

/**
 * @brief Typedef de la table lexicographique de taille : TAILLE_MAX_TABLE_LEXICO (voir #define)
*/
typedef struct ligne_lex tab_lexico[TAILLE_MAX_TABLE_LEXICO];

/**
 * @author MATHEVON Baptiste
 * @brief Initialisation de la table lexico (et de la table de hashcode)
*/
void init_table_lexico();

/**
 * @author MATHEVON Baptiste
 * @brief Calcul du hashcode d'un lexeme donné
 * @param lexeme Lexeme dont on calcule le hashcode
 * @return int : numéro de hashcode du lexème
*/
int calcul_hashcode(char * lexeme);

/**
 * @author MATHEVON Baptiste
 * @brief Insertion d'un lexeme dans la table des lexemes
 * @param lexeme Lexeme a insérer dans la table
 * @return int : numero lexico du lexème si déja dans la table, sinon numéro lexico du lexème qui vient d'être inséré
*/
int inserer_lexeme(char lexeme[]);

/**
 * @author MATHEVON Baptiste
 * @brief Recupération du numéro lexicographique (donc verification si le lexème est déja dans la table ou non)
 * @param lexeme Lexeme dont on veut récupérer le numéro lexicographique
 * @return int : numero lexico du lexeme si déja dans la table, -1 sinon
*/
int numero_lexico(char * lexeme);

/**
 * @author MATHEVON Baptiste
 * @brief Affichage sur le terminal de la table des lexèmes
*/
void affichage_table_lexeme();

/**
 * @author MATHEVON Baptiste
 * @brief Affichage sur le terminal de la table de hashcode
*/
void affichage_table_hashcode();

/**
 * @author MATHEVON Baptiste
 * @brief Récupération du lexème associé à un certain numéro lexicographique
 * @param numero_lexico Numéro lexicographique dont on veut récupérer le lexème
 * @return char* : le lexème associé à ce numéro
*/
char * lexeme(int numero_lexico);

#endif
