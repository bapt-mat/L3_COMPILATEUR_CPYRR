/**
 * @file pile_execution.c
 * @author Principal : MATHEVON Baptiste - Secondaires : YILDIZ Tolga, GUNES Ozan 
 * @brief Pile à l'exécution d'un programme CPYRR
 * @date 21-12-2023
*/

#include "pile_execution.h"

extern pile_execution pile;
extern int BC;
extern int * tab_chainage_statique;
extern int indice_tab_chainage_statique;
extern int indice_affichage_pile;
extern int indice_BC_dispo;
extern tab_regions table_regions;
extern tab_lexico table;

/*Pour la liste des arguments d'une fonction/procedure*/
extern int num_description_tmp;
extern int num_argument_courant;
extern int num_region_appelante_liste_arguments;

/*Pour 'ecrire'*/
extern union cellule_pile * tab_arguments_ecrire;
extern int indice_tab_arguments_ecrire;

/*Pour les strucutres*/
extern int indice_description_tmp;
extern int indice_champ_tmp;

/*Pour les tableaux*/
extern int indice_tableau_tmp;
extern int taille_dimension_tmp;
extern int * tab_taille_dimensions;
extern int indice_tab_taille_dimensions;
extern int taille_case_tab;

extern FILE * yyin;

/*----------------------------------------*
| NOTE : -> probablement de gros problèmes pour les récupérations de descriptions de struct et de tableaux depuis la table des types si déclaré dans la zone de débordement !!!
|        -> car accès avec le numéro lexico et non le numéro de déclaration depuis la table des types 
|        -> faire des fonctions d'association de noms pour récupérer le numéro de déclaration depuis le numéro lexico
*-----------------------------------------*/

/** --------------------------------------*
* @author : MATHEVON Baptiste
* @brief : Affichage de la pile dans le terminal
*-----------------------------------------*/
void affichage_pile() {
    printf("\n---- PILE A L'EXECUTION ----\n");
    for (int i=0; i<indice_affichage_pile+50; i++){
        if (pile[i].type == CELLULE_ENTIER){
            printf(" %d |", pile[i].valeur.entier);
        }
        if (pile[i].type == CELLULE_REEL){
            printf(" %.2f |", pile[i].valeur.reel);
        }
        if (pile[i].type == CELLULE_CHAR){
            printf(" %c |", pile[i].valeur.caractere);
        }
        if (pile[i].type == CELLULE_BOOL){
            if (pile[i].valeur.entier == 1){
                printf("True %d |", pile[i].valeur.entier);
            }
            else{
                printf("False %d |", pile[i].valeur.entier);
            }
        }
        if (pile[i].type == CELLULE_CHAIN_DYN){ //chainage dynamique
            couleur(ROUGE); fprintf(stdout, " %d ", pile[i].valeur.entier); couleur(REINIT); printf("|");
        }
        if (pile[i].type == CELLULE_CHAIN_STAT){//chainage statique
            couleur(VERT); fprintf(stdout, " %d ", pile[i].valeur.entier); couleur(REINIT); printf("|");
        }
        if (pile[i].type == CELLULE_VIDE){
            printf(" - |");
        }
    }
    printf("\n");
}

/** --------------------------------------*
* @author : MATHEVON Baptiste
* @brief : Fonction de vidage du buffer pour l'utilisation de stdin
*-----------------------------------------*/
void viderBuffer(){
    int c = 0;
    while (c != '\n' && c != EOF)
    {
        c = getchar();
    }
}

/** --------------------------------------*
* @author : MATHEVON Baptiste
* @brief : Init des variables nécessaires pour les parcours des structures et des tableaux
*-----------------------------------------*/
void init_var_deplacement_struct_tab(int indice_description_struct){
    /*Pour les structures (indice_champ_tmp = 1 -> pour accéder directement au num lex du premier champ)*/
    indice_champ_tmp = 1;
    indice_description_tmp = indice_description_struct;
    taille_dimension_tmp = 1;
    /*Pour les tableaux (indice_tableau_tmp -> +1 pour avoir le nombre de dimensions directement)*/
    indice_tableau_tmp = indice_description_tmp + 1; 
    indice_tab_taille_dimensions = 0; 
    taille_case_tab = table_declaration[table_types[indice_description_tmp]].execution;
}

/** --------------------------------------*
* @author : MATHEVON Baptiste
* @brief : Calcul arithmétique entre deux expressions entières
*-----------------------------------------*/
int calcul_arithmetique_entier(int expression1, int expression2, int type_operation){
    int resultat;
    switch (type_operation){
        case T_PLUS : 
            resultat = expression1 + expression2;
            break;
        case T_MOINS : 
            resultat = expression1 - expression2;
            break;
        case T_MULT : 
            resultat = expression1 * expression2;
            break;
        case T_DIV :
            if (expression2 == 0){
                printf("ERREUR : division par 0\n");
            } 
            else{
                resultat = expression1 / expression2;
            }
            break;
        default : 
            break;
    }
    return resultat;
}

/** --------------------------------------*
* @author : MATHEVON Baptiste
* @brief : Calcul arithmétique entre deux expressions réelles
*-----------------------------------------*/
float calcul_arithmetique_reel(float expression1, float expression2, int type_operation){
    float resultat;
    switch (type_operation){
        case T_PLUS : 
            resultat = expression1 + expression2;
            break;
        case T_MOINS : 
            resultat = expression1 - expression2;
            break;
        case T_MULT : 
            resultat = expression1 * expression2;
            break;
        case T_DIV : 
            if (expression2 == 0){
                printf("ERREUR : division par 0\n");
            } 
            else{
                resultat = expression1 / expression2;
            }            
            break;
        default : 
            break;
    }
    return resultat;
}

/** --------------------------------------*
* @author : MATHEVON Baptiste
* @brief : Calcul arithmétique entre deux expressions
*-----------------------------------------*/
struct valeur_cellule calcul_arithmetique (int num_region_actuelle, struct valeur_cellule resultat_gauche, struct valeur_cellule resultat_droite, int type_operation, arbre arbre_ope){
    int decalage_gauche_NIS;
    int decalage_droite_NIS;
    struct valeur_cellule resultat;
    int deplacement_gauche;
    int deplacement_droite;
    
    if (resultat_gauche.type == CELLULE_ENTIER){
        if (resultat_droite.type == CELLULE_ENTIER){
            resultat.valeur.entier = calcul_arithmetique_entier(resultat_gauche.valeur.entier, resultat_droite.valeur.entier, type_operation);
            resultat.type = CELLULE_ENTIER;
        }
        if (resultat_droite.type == CELLULE_IDF){
            decalage_gauche_NIS = table_regions[num_region_actuelle].NIS - table_regions[table_declaration[resultat_droite.valeur.entier].region].NIS;
            deplacement_droite = table_declaration[resultat_droite.valeur.entier].execution;
            if (decalage_gauche_NIS != 0){
                resultat.valeur.entier = calcul_arithmetique_entier(resultat_gauche.valeur.entier, pile[pile[BC+decalage_gauche_NIS].valeur.entier + deplacement_droite].valeur.entier, type_operation);
            }
            else{
                resultat.valeur.entier = calcul_arithmetique_entier(resultat_gauche.valeur.entier, pile[BC + deplacement_droite].valeur.entier, type_operation);
            }
            resultat.type = CELLULE_ENTIER;
        }
        if (resultat_droite.type == CELLULE_TYPE_S_T){
            decalage_gauche_NIS = table_regions[num_region_actuelle].NIS - table_regions[table_declaration[resultat_droite.valeur.entier].region].NIS;
            deplacement_droite = table_declaration[resultat_droite.valeur.entier].execution;
            init_var_deplacement_struct_tab(table_declaration[table_declaration[resultat_droite.valeur.entier].description].description);
            deplacement_droite += parcours_arbre(arbre_ope->fils->frere->fils, num_region_actuelle).valeur.entier;
            if (decalage_gauche_NIS != 0){
                resultat.valeur.entier = calcul_arithmetique_entier(resultat_gauche.valeur.entier, pile[pile[BC+decalage_gauche_NIS].valeur.entier + deplacement_droite].valeur.entier, type_operation);
            }
            else{
                resultat.valeur.entier = calcul_arithmetique_entier(resultat_gauche.valeur.entier, pile[BC + deplacement_droite].valeur.entier, type_operation);
            }
            resultat.type = CELLULE_ENTIER;
        }
    }
    if (resultat_gauche.type == CELLULE_REEL){
        if (resultat_droite.type == CELLULE_REEL){
            resultat.valeur.reel = calcul_arithmetique_reel(resultat_gauche.valeur.reel, resultat_droite.valeur.reel, type_operation);
            resultat.type = CELLULE_REEL;
        }
        if (resultat_droite.type == CELLULE_IDF){
            decalage_gauche_NIS = table_regions[num_region_actuelle].NIS - table_regions[table_declaration[resultat_droite.valeur.entier].region].NIS;
            deplacement_droite = table_declaration[resultat_droite.valeur.entier].execution;
            if(decalage_gauche_NIS != 0){
                resultat.valeur.reel = calcul_arithmetique_reel(resultat_gauche.valeur.reel, pile[pile[BC+decalage_gauche_NIS].valeur.entier + deplacement_droite].valeur.reel, type_operation);
            }
            else{
                resultat.valeur.reel = calcul_arithmetique_reel(resultat_gauche.valeur.reel, pile[BC + deplacement_droite].valeur.reel, type_operation);
            }
            resultat.type = CELLULE_REEL;
        }
        if (resultat_droite.type == CELLULE_TYPE_S_T){
            decalage_gauche_NIS = table_regions[num_region_actuelle].NIS - table_regions[table_declaration[resultat_droite.valeur.entier].region].NIS;
            deplacement_droite = table_declaration[resultat_droite.valeur.entier].execution;
            init_var_deplacement_struct_tab(table_declaration[table_declaration[resultat_droite.valeur.entier].description].description);
            deplacement_droite += parcours_arbre(arbre_ope->fils->frere->fils, num_region_actuelle).valeur.entier;
            if (decalage_gauche_NIS != 0){
                resultat.valeur.reel = calcul_arithmetique_entier(resultat_gauche.valeur.reel, pile[pile[BC+decalage_gauche_NIS].valeur.entier + deplacement_droite].valeur.reel, type_operation);
            }
            else{
                resultat.valeur.reel = calcul_arithmetique_entier(resultat_gauche.valeur.reel, pile[BC + deplacement_droite].valeur.reel, type_operation);
            }
            resultat.type = CELLULE_REEL;
        }
    }
    if (resultat_gauche.type == CELLULE_IDF){
        decalage_gauche_NIS = table_regions[num_region_actuelle].NIS - table_regions[table_declaration[resultat_gauche.valeur.entier].region].NIS;
        deplacement_gauche = table_declaration[resultat_gauche.valeur.entier].execution;
        if (resultat_droite.type == CELLULE_ENTIER){
            if (decalage_gauche_NIS != 0){
                resultat.valeur.entier = calcul_arithmetique_entier(pile[pile[BC+decalage_gauche_NIS].valeur.entier + deplacement_gauche].valeur.entier, resultat_droite.valeur.entier, type_operation);
            }
            else{
                /*----------------------------------------*
                | Si c'est un param 
                *-----------------------------------------*/
                if (table_declaration[resultat_gauche.valeur.entier].nature == PARAM){
                    BC = pile[BC].valeur.entier;
                }
                resultat.valeur.entier = calcul_arithmetique_entier(pile[BC + deplacement_gauche].valeur.entier, resultat_droite.valeur.entier, type_operation);
            }
            resultat.type = CELLULE_ENTIER;
        }
        if (resultat_droite.type == CELLULE_REEL){
            if (decalage_gauche_NIS != 0){
                resultat.valeur.reel = calcul_arithmetique_reel(pile[pile[BC+decalage_gauche_NIS].valeur.entier + deplacement_gauche].valeur.reel, resultat_droite.valeur.reel, type_operation);
            }
            else{
                resultat.valeur.reel = calcul_arithmetique_reel(pile[BC + deplacement_gauche].valeur.reel, resultat_droite.valeur.reel, type_operation);
            }
            resultat.type = CELLULE_REEL;
        }
        if (resultat_droite.type == CELLULE_IDF){
            decalage_droite_NIS = table_regions[num_region_actuelle].NIS - table_regions[table_declaration[resultat_droite.valeur.entier].region].NIS;
            deplacement_droite = table_declaration[resultat_droite.valeur.entier].execution;
            
            if (table_declaration[resultat_gauche.valeur.entier].description == 0){ // alors ce sont des entiers
                if (decalage_droite_NIS != 0){
                    if (decalage_gauche_NIS != 0){
                        resultat.valeur.entier = calcul_arithmetique_entier(pile[pile[BC+decalage_gauche_NIS].valeur.entier  + deplacement_gauche].valeur.entier, pile[pile[BC+decalage_droite_NIS].valeur.entier + deplacement_droite].valeur.entier, type_operation);
                    }
                    else{
                        resultat.valeur.entier = calcul_arithmetique_entier(pile[BC + deplacement_gauche].valeur.entier, pile[pile[BC+decalage_droite_NIS].valeur.entier + deplacement_droite].valeur.entier, type_operation);
                    }
                }
                else{
                    if (decalage_gauche_NIS != 0){
                        resultat.valeur.entier = calcul_arithmetique_entier(pile[pile[BC+decalage_gauche_NIS].valeur.entier  + deplacement_gauche].valeur.entier, pile[BC + deplacement_droite].valeur.entier, type_operation);
                    }
                    else{
                        resultat.valeur.entier = calcul_arithmetique_entier(pile[BC + deplacement_gauche].valeur.entier, pile[BC + deplacement_droite].valeur.entier, type_operation);
                    }
                }
                resultat.type = CELLULE_ENTIER;
            }
            else{//sinon ce sont des floats
                if (decalage_droite_NIS != 0){
                    if (decalage_gauche_NIS != 0){
                        resultat.valeur.reel = calcul_arithmetique_reel(pile[pile[BC+decalage_gauche_NIS].valeur.entier  + deplacement_gauche].valeur.reel, pile[pile[BC+decalage_droite_NIS].valeur.entier + deplacement_droite].valeur.reel, type_operation);
                    }
                    else{
                        resultat.valeur.reel = calcul_arithmetique_reel(pile[BC + deplacement_gauche].valeur.reel, pile[pile[BC+decalage_droite_NIS].valeur.entier + deplacement_droite].valeur.reel, type_operation);
                    }
                }
                else{
                    if (decalage_gauche_NIS != 0){
                        resultat.valeur.reel = calcul_arithmetique_reel(pile[pile[BC+decalage_gauche_NIS].valeur.entier  + deplacement_gauche].valeur.reel, pile[BC + deplacement_droite].valeur.reel, type_operation);
                    }
                    else{
                        resultat.valeur.reel = calcul_arithmetique_reel(pile[BC + deplacement_gauche].valeur.reel, pile[BC + deplacement_droite].valeur.reel, type_operation);
                    }
                }
                resultat.type =CELLULE_REEL;
            }
        }
        if (resultat_droite.type == CELLULE_TYPE_S_T){
            decalage_droite_NIS = table_regions[num_region_actuelle].NIS - table_regions[table_declaration[resultat_droite.valeur.entier].region].NIS;
            deplacement_droite = table_declaration[resultat_droite.valeur.entier].execution;
            init_var_deplacement_struct_tab(table_declaration[table_declaration[resultat_droite.valeur.entier].description].description);
            deplacement_droite += parcours_arbre(arbre_ope->fils->frere->fils, num_region_actuelle).valeur.entier;
            if (table_declaration[resultat_gauche.valeur.entier].description == 0){ // alors ce sont des entiers
                if (decalage_droite_NIS != 0){
                    if (decalage_gauche_NIS != 0){
                        resultat.valeur.entier = calcul_arithmetique_entier(pile[pile[BC+decalage_gauche_NIS].valeur.entier  + deplacement_gauche].valeur.entier, pile[pile[BC+decalage_droite_NIS].valeur.entier + deplacement_droite].valeur.entier, type_operation);
                    }
                    else{
                        resultat.valeur.entier = calcul_arithmetique_entier(pile[BC + deplacement_gauche].valeur.entier, pile[pile[BC+decalage_droite_NIS].valeur.entier + deplacement_droite].valeur.entier, type_operation);
                    }
                }
                else{
                    if (decalage_gauche_NIS != 0){
                        resultat.valeur.entier = calcul_arithmetique_entier(pile[pile[BC+decalage_gauche_NIS].valeur.entier  + deplacement_gauche].valeur.entier, pile[BC + deplacement_droite].valeur.entier, type_operation);
                    }
                    else{
                        resultat.valeur.entier = calcul_arithmetique_entier(pile[BC + deplacement_gauche].valeur.entier, pile[BC + deplacement_droite].valeur.entier, type_operation);
                    }
                }
                resultat.type = CELLULE_ENTIER;
            }
            else{//sinon ce sont des floats
                if (decalage_droite_NIS != 0){
                    if (decalage_gauche_NIS != 0){
                        resultat.valeur.reel = calcul_arithmetique_reel(pile[pile[BC+decalage_gauche_NIS].valeur.entier  + deplacement_gauche].valeur.reel, pile[pile[BC+decalage_droite_NIS].valeur.entier + deplacement_droite].valeur.reel, type_operation);
                    }
                    else{
                        resultat.valeur.reel = calcul_arithmetique_reel(pile[BC + deplacement_gauche].valeur.reel, pile[pile[BC+decalage_droite_NIS].valeur.entier + deplacement_droite].valeur.reel, type_operation);
                    }
                }
                else{
                    if (decalage_gauche_NIS != 0){
                        resultat.valeur.reel = calcul_arithmetique_reel(pile[pile[BC+decalage_gauche_NIS].valeur.entier  + deplacement_gauche].valeur.reel, pile[BC + deplacement_droite].valeur.reel, type_operation);
                    }
                    else{
                        resultat.valeur.reel = calcul_arithmetique_reel(pile[BC + deplacement_gauche].valeur.reel, pile[BC + deplacement_droite].valeur.reel, type_operation);
                    }
                }
                resultat.type = CELLULE_REEL;
            }
        }
    }
    if (resultat_gauche.type == CELLULE_TYPE_S_T){
        decalage_gauche_NIS = table_regions[num_region_actuelle].NIS - table_regions[table_declaration[resultat_gauche.valeur.entier].region].NIS;
        deplacement_gauche = table_declaration[resultat_gauche.valeur.entier].execution;
        init_var_deplacement_struct_tab(table_declaration[table_declaration[resultat_gauche.valeur.entier].description].description);
        deplacement_gauche += parcours_arbre(arbre_ope->fils->fils, num_region_actuelle).valeur.entier;
        if (resultat_droite.type == CELLULE_ENTIER){
            if (decalage_gauche_NIS != 0){
                resultat.valeur.entier = calcul_arithmetique_entier(pile[pile[BC+decalage_gauche_NIS].valeur.entier + deplacement_gauche].valeur.entier, resultat_droite.valeur.entier, type_operation);
            }
            else{
                resultat.valeur.entier = calcul_arithmetique_entier(pile[BC + deplacement_gauche].valeur.entier, resultat_droite.valeur.entier, type_operation);
            }
            resultat.type = CELLULE_ENTIER;
        }
        if (resultat_droite.type == CELLULE_REEL){
            if (decalage_gauche_NIS != 0){
                resultat.valeur.reel = calcul_arithmetique_reel(pile[pile[BC+decalage_gauche_NIS].valeur.entier + deplacement_gauche].valeur.reel, resultat_droite.valeur.reel, type_operation);
            }
            else{
                resultat.valeur.reel = calcul_arithmetique_reel(pile[BC + deplacement_gauche].valeur.reel, resultat_droite.valeur.reel, type_operation);
            }
            resultat.type = CELLULE_REEL;
        }
        if (resultat_droite.type == CELLULE_IDF){
            decalage_droite_NIS = table_regions[num_region_actuelle].NIS - table_regions[table_declaration[resultat_droite.valeur.entier].region].NIS;
            deplacement_droite = table_declaration[resultat_droite.valeur.entier].execution;
            if (table_declaration[resultat_droite.valeur.entier].description == 0){ // alors ce sont des entiers
                if (decalage_droite_NIS != 0){
                    if (decalage_gauche_NIS != 0){
                        resultat.valeur.entier = calcul_arithmetique_entier(pile[pile[BC+decalage_gauche_NIS].valeur.entier  + deplacement_gauche].valeur.entier, pile[pile[BC+decalage_droite_NIS].valeur.entier + deplacement_droite].valeur.entier, type_operation);
                    }
                    else{
                        resultat.valeur.entier = calcul_arithmetique_entier(pile[BC + deplacement_gauche].valeur.entier, pile[pile[BC+decalage_droite_NIS].valeur.entier + deplacement_droite].valeur.entier, type_operation);
                    }
                }
                else{
                    if (decalage_gauche_NIS != 0){
                        resultat.valeur.entier = calcul_arithmetique_entier(pile[pile[BC+decalage_gauche_NIS].valeur.entier  + deplacement_gauche].valeur.entier, pile[BC + deplacement_droite].valeur.entier, type_operation);
                    }
                    else{
                        resultat.valeur.entier = calcul_arithmetique_entier(pile[BC + deplacement_gauche].valeur.entier, pile[BC + deplacement_droite].valeur.entier, type_operation);
                    }
                }
                resultat.type = CELLULE_ENTIER;
            }
            else{//sinon ce sont des floats
                if (decalage_droite_NIS != 0){
                    if (decalage_gauche_NIS != 0){
                        resultat.valeur.reel = calcul_arithmetique_reel(pile[pile[BC+decalage_gauche_NIS].valeur.entier  + deplacement_gauche].valeur.reel, pile[pile[BC+decalage_droite_NIS].valeur.entier + deplacement_droite].valeur.reel, type_operation);
                    }
                    else{
                        resultat.valeur.reel = calcul_arithmetique_reel(pile[BC + deplacement_gauche].valeur.reel, pile[pile[BC+decalage_droite_NIS].valeur.entier + deplacement_droite].valeur.reel, type_operation);
                    }
                }
                resultat.type = CELLULE_REEL;
            }
        }
        if (resultat_droite.type == CELLULE_TYPE_S_T){
            decalage_droite_NIS = table_regions[num_region_actuelle].NIS - table_regions[table_declaration[resultat_droite.valeur.entier].region].NIS;
            deplacement_droite = table_declaration[resultat_droite.valeur.entier].execution;
            init_var_deplacement_struct_tab(table_declaration[table_declaration[resultat_droite.valeur.entier].description].description);
            deplacement_droite += parcours_arbre(arbre_ope->fils->frere->fils, num_region_actuelle).valeur.entier;
            
            if (arbre_ope->num_declaration == 0){ // alors ce sont des entiers
                if (decalage_droite_NIS != 0){
                    if (decalage_gauche_NIS != 0){
                        resultat.valeur.entier = calcul_arithmetique_entier(pile[pile[BC+decalage_gauche_NIS].valeur.entier  + deplacement_gauche].valeur.entier, pile[pile[BC+decalage_droite_NIS].valeur.entier + deplacement_droite].valeur.entier, type_operation);
                    }
                    else{
                        resultat.valeur.entier = calcul_arithmetique_entier(pile[BC + deplacement_gauche].valeur.entier, pile[pile[BC+decalage_droite_NIS].valeur.entier + deplacement_droite].valeur.entier, type_operation);
                    }
                }
                else{
                    if (decalage_gauche_NIS != 0){
                        resultat.valeur.entier = calcul_arithmetique_entier(pile[pile[BC+decalage_gauche_NIS].valeur.entier  + deplacement_gauche].valeur.entier, pile[BC + deplacement_droite].valeur.entier, type_operation);
                    }
                    else{
                        resultat.valeur.entier = calcul_arithmetique_entier(pile[BC + deplacement_gauche].valeur.entier, pile[BC + deplacement_droite].valeur.entier, type_operation);
                    }
                }
                resultat.type = CELLULE_ENTIER;
            }
            else{//sinon ce sont des floats
                if (decalage_droite_NIS != 0){
                    if (decalage_gauche_NIS != 0){
                        resultat.valeur.reel = calcul_arithmetique_reel(pile[pile[BC+decalage_gauche_NIS].valeur.entier  + deplacement_gauche].valeur.reel, pile[pile[BC+decalage_droite_NIS].valeur.entier + deplacement_droite].valeur.reel, type_operation);
                    }
                    else{
                        resultat.valeur.reel = calcul_arithmetique_reel(pile[BC + deplacement_gauche].valeur.reel, pile[pile[BC+decalage_droite_NIS].valeur.entier + deplacement_droite].valeur.reel, type_operation);
                    }
                }
                resultat.type = CELLULE_REEL;
            }
        }
    }
    return resultat;
}

/** --------------------------------------*
* @author : MATHEVON Baptiste
* @brief : Calcul logique entre deux expressions (booléen représenté par un entier (1 pour TRUE et 0 pour FALSE))
*-----------------------------------------*/
int calcul_logique_et_ou (int expression_droite, int expression_gauche, int type_operation){
    int resultat;
    switch (type_operation){
        case T_ET : 
            if (expression_gauche == 1 && expression_droite == 1){
                resultat = 1;
                break;
            }
            if (expression_gauche == 0 && expression_droite == 0){
                resultat = 1;
                break;
            }
            else{
                resultat = 0;
            }
            break;
        case T_OU :
            if (expression_gauche == 1 || expression_droite == 1){
                resultat = 1;
                break;
            }
            else{
                resultat = 0;
            }
            break;
        default : 
            break;
    }
    return resultat;
}

/** --------------------------------------*
* @author : MATHEVON Baptiste
* @brief : Inverse le booléen d'une expression (booléen représenté par un entier (1 pour TRUE et 0 pour FALSE))
*-----------------------------------------*/
struct valeur_cellule inverse_bool(int num_region_actuelle, struct valeur_cellule resultat_expr, arbre arbre_ope){
    int decalage_NIS;
    int deplacement;
    struct valeur_cellule resultat;
    
    if (resultat_expr.type == CELLULE_BOOL){
        resultat.valeur.entier = !resultat_expr.valeur.entier;
    }
    if (resultat_expr.type == CELLULE_IDF){
        decalage_NIS = table_regions[num_region_actuelle].NIS - table_regions[table_declaration[resultat_expr.valeur.entier].region].NIS;
        deplacement = table_declaration[resultat_expr.valeur.entier].execution;
        if (decalage_NIS != 0){
            resultat.valeur.entier = !pile[pile[BC+decalage_NIS].valeur.entier + deplacement].valeur.entier;
        }
        else{
            resultat.valeur.entier = !pile[BC + deplacement].valeur.entier;
        }
    }
    if (resultat_expr.type == CELLULE_TYPE_S_T){
        decalage_NIS = table_regions[num_region_actuelle].NIS - table_regions[table_declaration[resultat_expr.valeur.entier].region].NIS;
        deplacement = table_declaration[resultat_expr.valeur.entier].execution;
        init_var_deplacement_struct_tab(table_declaration[table_declaration[resultat_expr.valeur.entier].description].description);
        deplacement += parcours_arbre(arbre_ope->fils->frere->fils, num_region_actuelle).valeur.entier;
        if (decalage_NIS != 0){
            resultat.valeur.entier = !pile[pile[BC+decalage_NIS].valeur.entier + deplacement].valeur.entier;
        }
        else{
            resultat.valeur.entier = !pile[BC + deplacement].valeur.entier;
        }
    }
    resultat.type = CELLULE_BOOL;
    return resultat;
}

/** --------------------------------------*
* @author : MATHEVON Baptiste
* @brief : Calcul logique entre deux expressions
*-----------------------------------------*/
struct valeur_cellule calcul_logique(int num_region_actuelle, struct valeur_cellule resultat_gauche, struct valeur_cellule resultat_droite, int type_operation, arbre arbre_ope){
    int decalage_gauche_NIS;
    int decalage_droite_NIS;
    struct valeur_cellule resultat;
    int deplacement_gauche;
    int deplacement_droite;
    
    if (resultat_gauche.type == CELLULE_BOOL){
        if (resultat_droite.type == CELLULE_BOOL){
            resultat.valeur.entier = calcul_logique_et_ou(resultat_droite.valeur.entier, resultat_gauche.valeur.entier, type_operation);
        }
        if (resultat_droite.type == CELLULE_IDF){
            decalage_gauche_NIS = table_regions[num_region_actuelle].NIS - table_regions[table_declaration[resultat_droite.valeur.entier].region].NIS;
            deplacement_droite = table_declaration[resultat_droite.valeur.entier].execution;
            if (decalage_gauche_NIS != 0){
                resultat.valeur.entier = calcul_logique_et_ou(pile[pile[BC+decalage_gauche_NIS].valeur.entier + deplacement_droite].valeur.entier, resultat_gauche.valeur.entier, type_operation);
            }
            else{
                resultat.valeur.entier = calcul_logique_et_ou(pile[BC + deplacement_droite].valeur.entier, resultat_gauche.valeur.entier, type_operation);
            }
        }
        if (resultat_droite.type == CELLULE_TYPE_S_T){
            decalage_gauche_NIS = table_regions[num_region_actuelle].NIS - table_regions[table_declaration[resultat_droite.valeur.entier].region].NIS;
            deplacement_droite = table_declaration[resultat_droite.valeur.entier].execution;
            init_var_deplacement_struct_tab(table_declaration[table_declaration[resultat_droite.valeur.entier].description].description);
            deplacement_droite += parcours_arbre(arbre_ope->fils->frere->fils, num_region_actuelle).valeur.entier;
            if (decalage_gauche_NIS != 0){
                resultat.valeur.entier = calcul_logique_et_ou(pile[pile[BC+decalage_gauche_NIS].valeur.entier + deplacement_droite].valeur.entier, resultat_gauche.valeur.entier, type_operation);
            }
            else{
                resultat.valeur.entier = calcul_logique_et_ou(pile[BC + deplacement_droite].valeur.entier, resultat_gauche.valeur.entier, type_operation);
            }
        }
    }
    if (resultat_gauche.type == CELLULE_IDF){
        decalage_gauche_NIS = table_regions[num_region_actuelle].NIS - table_regions[table_declaration[resultat_gauche.valeur.entier].region].NIS;
        deplacement_gauche = table_declaration[resultat_gauche.valeur.entier].execution;
        if (resultat_droite.type == CELLULE_BOOL){
            if (decalage_gauche_NIS != 0){
                resultat.valeur.entier = calcul_logique_et_ou(pile[pile[BC+decalage_gauche_NIS].valeur.entier + deplacement_gauche].valeur.entier, resultat_droite.valeur.entier, type_operation);
            }
            else{
                resultat.valeur.entier = calcul_logique_et_ou(pile[BC + deplacement_gauche].valeur.entier, resultat_droite.valeur.entier, type_operation);
            }
        }
        if (resultat_droite.type == CELLULE_IDF){
            decalage_droite_NIS = table_regions[num_region_actuelle].NIS - table_regions[table_declaration[resultat_droite.valeur.entier].region].NIS;
            deplacement_droite = table_declaration[resultat_droite.valeur.entier].execution;
            
            if (decalage_droite_NIS != 0){
                if (decalage_gauche_NIS != 0){
                    resultat.valeur.entier = calcul_logique_et_ou(pile[pile[BC+decalage_gauche_NIS].valeur.entier  + deplacement_gauche].valeur.entier, pile[pile[BC+decalage_droite_NIS].valeur.entier + deplacement_droite].valeur.entier, type_operation);
                }
                else{
                    resultat.valeur.entier = calcul_logique_et_ou(pile[BC + deplacement_gauche].valeur.entier, pile[pile[BC+decalage_droite_NIS].valeur.entier + deplacement_droite].valeur.entier, type_operation);
                }
            }
            else{
                if (decalage_gauche_NIS != 0){
                    resultat.valeur.entier = calcul_logique_et_ou(pile[pile[BC+decalage_gauche_NIS].valeur.entier  + deplacement_gauche].valeur.entier, pile[BC + deplacement_droite].valeur.entier, type_operation);
                }
                else{
                    resultat.valeur.entier = calcul_logique_et_ou(pile[BC + deplacement_gauche].valeur.entier, pile[BC + deplacement_droite].valeur.entier, type_operation);
                }
            }
        }
        if (resultat_droite.type == CELLULE_TYPE_S_T){
            decalage_droite_NIS = table_regions[num_region_actuelle].NIS - table_regions[table_declaration[resultat_droite.valeur.entier].region].NIS;
            deplacement_droite = table_declaration[resultat_droite.valeur.entier].execution;
            init_var_deplacement_struct_tab(table_declaration[table_declaration[resultat_droite.valeur.entier].description].description);
            deplacement_droite += parcours_arbre(arbre_ope->fils->frere->fils, num_region_actuelle).valeur.entier;
            if (decalage_droite_NIS != 0){
                if (decalage_gauche_NIS != 0){
                    resultat.valeur.entier = calcul_logique_et_ou(pile[pile[BC+decalage_gauche_NIS].valeur.entier  + deplacement_gauche].valeur.entier, pile[pile[BC+decalage_droite_NIS].valeur.entier + deplacement_droite].valeur.entier, type_operation);
                }
                else{
                    resultat.valeur.entier = calcul_logique_et_ou(pile[BC + deplacement_gauche].valeur.entier, pile[pile[BC+decalage_droite_NIS].valeur.entier + deplacement_droite].valeur.entier, type_operation);
                }
            }
            else{
                if (decalage_gauche_NIS != 0){
                    resultat.valeur.entier = calcul_logique_et_ou(pile[pile[BC+decalage_gauche_NIS].valeur.entier  + deplacement_gauche].valeur.entier, pile[BC + deplacement_droite].valeur.entier, type_operation);
                }
                else{
                    resultat.valeur.entier = calcul_logique_et_ou(pile[BC + deplacement_gauche].valeur.entier, pile[BC + deplacement_droite].valeur.entier, type_operation);
                }
            }
        }
    }
    if (resultat_gauche.type == CELLULE_TYPE_S_T){
        decalage_gauche_NIS = table_regions[num_region_actuelle].NIS - table_regions[table_declaration[resultat_gauche.valeur.entier].region].NIS;
        deplacement_gauche = table_declaration[resultat_gauche.valeur.entier].execution;
        init_var_deplacement_struct_tab(table_declaration[table_declaration[resultat_gauche.valeur.entier].description].description);
        deplacement_gauche += parcours_arbre(arbre_ope->fils->fils, num_region_actuelle).valeur.entier;
        if (resultat_droite.type == CELLULE_BOOL){
            if (decalage_gauche_NIS != 0){
                resultat.valeur.entier = calcul_logique_et_ou(pile[pile[BC+decalage_gauche_NIS].valeur.entier + deplacement_gauche].valeur.entier, resultat_droite.valeur.entier, type_operation);
            }
            else{
                resultat.valeur.entier = calcul_logique_et_ou(pile[BC + deplacement_gauche].valeur.entier, resultat_droite.valeur.entier, type_operation);
            }
        }
        if (resultat_droite.type == CELLULE_IDF){
            decalage_droite_NIS = table_regions[num_region_actuelle].NIS - table_regions[table_declaration[resultat_droite.valeur.entier].region].NIS;
            deplacement_droite = table_declaration[resultat_droite.valeur.entier].execution;
            if (decalage_droite_NIS != 0){
                if (decalage_gauche_NIS != 0){
                    resultat.valeur.entier = calcul_logique_et_ou(pile[pile[BC+decalage_gauche_NIS].valeur.entier  + deplacement_gauche].valeur.entier, pile[pile[BC+decalage_droite_NIS].valeur.entier + deplacement_droite].valeur.entier, type_operation);
                }
                else{
                    resultat.valeur.entier = calcul_logique_et_ou(pile[BC + deplacement_gauche].valeur.entier, pile[pile[BC+decalage_droite_NIS].valeur.entier + deplacement_droite].valeur.entier, type_operation);
                }
            }
            else{
                if (decalage_gauche_NIS != 0){
                    resultat.valeur.entier = calcul_logique_et_ou(pile[pile[BC+decalage_gauche_NIS].valeur.entier  + deplacement_gauche].valeur.entier, pile[BC + deplacement_droite].valeur.entier, type_operation);
                }
                else{
                    resultat.valeur.entier = calcul_logique_et_ou(pile[BC + deplacement_gauche].valeur.entier, pile[BC + deplacement_droite].valeur.entier, type_operation);
                }
            }
        }
        if (resultat_droite.type == CELLULE_TYPE_S_T){
            decalage_droite_NIS = table_regions[num_region_actuelle].NIS - table_regions[table_declaration[resultat_droite.valeur.entier].region].NIS;
            deplacement_droite = table_declaration[resultat_droite.valeur.entier].execution;
            init_var_deplacement_struct_tab(table_declaration[table_declaration[resultat_droite.valeur.entier].description].description);
            deplacement_droite += parcours_arbre(arbre_ope->fils->frere->fils, num_region_actuelle).valeur.entier;
            
            if (decalage_droite_NIS != 0){
                if (decalage_gauche_NIS != 0){
                    resultat.valeur.entier = calcul_logique_et_ou(pile[pile[BC+decalage_gauche_NIS].valeur.entier + deplacement_gauche].valeur.entier, pile[pile[BC+decalage_droite_NIS].valeur.entier + deplacement_droite].valeur.entier, type_operation);
                }
                else{
                    resultat.valeur.entier = calcul_logique_et_ou(pile[BC + deplacement_gauche].valeur.entier, pile[pile[BC+decalage_droite_NIS].valeur.entier + deplacement_droite].valeur.entier, type_operation);
                }
            }
            else{
                if (decalage_gauche_NIS != 0){
                    resultat.valeur.entier = calcul_logique_et_ou(pile[pile[BC+decalage_gauche_NIS].valeur.entier + deplacement_gauche].valeur.entier, pile[BC + deplacement_droite].valeur.entier, type_operation);
                }
                else{
                    resultat.valeur.entier = calcul_logique_et_ou(pile[BC + deplacement_gauche].valeur.entier, pile[BC + deplacement_droite].valeur.entier, type_operation);
                }
            }
        }
    }
    resultat.type = CELLULE_BOOL;
    return resultat;
}

/** --------------------------------------*
* @author : MATHEVON Baptiste
* @brief : Calcul logique de comparaisons entre deux chars
*-----------------------------------------*/
int calcul_comparaison_char(char expression_gauche, char expression_droite, int type_operation){
    int resultat;
    switch (type_operation){
        case T_SUP : 
            if (expression_gauche > expression_droite){
                resultat = 1;
            }
            else{
                resultat = 0;
            }
            break;
        case T_INF :
            if (expression_gauche < expression_droite){
                resultat = 1;
            }
            else{
                resultat = 0;
            }
            break;
        case T_SUP_EGAL :
            if (expression_gauche >= expression_droite){
                resultat = 1;
            }
            else{
                resultat = 0;
            }
            break;
        case T_INF_EGAL :
            if (expression_gauche <= expression_droite){
                resultat = 1;
            }
            else{
                resultat = 0;
            }
            break;
        case T_DOUBLEEGAL :
            if (expression_gauche == expression_droite){
                resultat = 1;
            }
            else{
                resultat = 0;
            }
            break;
        default : 
            break;
    }
    return resultat;
}

/** --------------------------------------*
* @author : MATHEVON Baptiste
* @brief : Calcul logique de comparaisons entre deux entiers
*-----------------------------------------*/
int calcul_comparaison_entier(int expression_gauche, int expression_droite, int type_operation){
    int resultat;
    switch (type_operation){
        case T_SUP : 
            if (expression_gauche > expression_droite){
                resultat = 1;
            }
            else{
                resultat = 0;
            }
            break;
        case T_INF :
            if (expression_gauche < expression_droite){
                resultat = 1;
            }
            else{
                resultat = 0;
            }
            break;
        case T_SUP_EGAL :
            if (expression_gauche >= expression_droite){
                resultat = 1;
            }
            else{
                resultat = 0;
            }
            break;
        case T_INF_EGAL :
            if (expression_gauche <= expression_droite){
                resultat = 1;
            }
            else{
                resultat = 0;
            }
            break;
        case T_DOUBLEEGAL :
            if (expression_gauche == expression_droite){
                resultat = 1;
            }
            else{
                resultat = 0;
            }
            break;
        default : 
            break;
    }
    return resultat;
}

/** --------------------------------------*
* @author : MATHEVON Baptiste
* @brief : Calcul logique de comparaisons entre deux reels
*-----------------------------------------*/
int calcul_comparaison_reel(float expression_gauche, float expression_droite, int type_operation){
    int resultat;
    switch (type_operation){
        case T_SUP : 
            if (expression_gauche > expression_droite){
                resultat = 1;
            }
            else{
                resultat = 0;
            }
            break;
        case T_INF :
            if (expression_gauche < expression_droite){
                resultat = 1;
            }
            else{
                resultat = 0;
            }
            break;
        case T_SUP_EGAL :
            if (expression_gauche >= expression_droite){
                resultat = 1;
            }
            else{
                resultat = 0;
            }
            break;
        case T_INF_EGAL :
            if (expression_gauche <= expression_droite){
                resultat = 1;
            }
            else{
                resultat = 0;
            }
            break;
        case T_DOUBLEEGAL :
            if (expression_gauche == expression_droite){
                resultat = 1;
            }
            else{
                resultat = 0;
            }
            break;
        default : 
            break;
    }
    return resultat;
}

/** --------------------------------------*
* @author : MATHEVON Baptiste
* @brief : Calcul logique de comparaisons entre deux expressions
*-----------------------------------------*/
struct valeur_cellule calcul_comparaison(int num_region_actuelle, struct valeur_cellule resultat_gauche, struct valeur_cellule resultat_droite, int type_operation, arbre arbre_ope){
    int decalage_gauche_NIS;
    int decalage_droite_NIS;
    struct valeur_cellule resultat;
    int deplacement_gauche;
    int deplacement_droite;
    
    if (resultat_gauche.type == CELLULE_CHAR){
        if (resultat_droite.type == CELLULE_CHAR){
            resultat.valeur.entier = calcul_comparaison_char(resultat_gauche.valeur.caractere, resultat_droite.valeur.caractere, type_operation);
        }
        if (resultat_droite.type == CELLULE_IDF){
            decalage_droite_NIS = table_regions[num_region_actuelle].NIS - table_regions[table_declaration[resultat_droite.valeur.entier].region].NIS;
            deplacement_droite = table_declaration[resultat_droite.valeur.entier].execution;
            if (decalage_droite_NIS != 0){
                resultat.valeur.entier = calcul_comparaison_char(resultat_gauche.valeur.caractere, pile[pile[BC+decalage_droite_NIS].valeur.entier + deplacement_droite].valeur.entier, type_operation);
            }
            else{
                resultat.valeur.entier = calcul_comparaison_char(resultat_gauche.valeur.caractere, pile[BC + deplacement_droite].valeur.entier, type_operation);
            }
        }
        if (resultat_droite.type == CELLULE_TYPE_S_T){
            decalage_droite_NIS = table_regions[num_region_actuelle].NIS - table_regions[table_declaration[resultat_droite.valeur.entier].region].NIS;
            deplacement_droite = table_declaration[resultat_droite.valeur.entier].execution;
            init_var_deplacement_struct_tab(table_declaration[table_declaration[resultat_droite.valeur.entier].description].description);
            deplacement_droite += parcours_arbre(arbre_ope->fils->frere->fils, num_region_actuelle).valeur.entier;
            if (decalage_droite_NIS != 0){
                resultat.valeur.entier = calcul_comparaison_char(resultat_gauche.valeur.caractere, pile[pile[BC+decalage_droite_NIS].valeur.entier + deplacement_droite].valeur.entier, type_operation);
            }
            else{
                resultat.valeur.entier = calcul_comparaison_char(resultat_gauche.valeur.caractere, pile[BC + deplacement_droite].valeur.entier, type_operation);
            }
        }
    }
    if (resultat_gauche.type == CELLULE_ENTIER){
        if (resultat_droite.type == CELLULE_ENTIER){
            resultat.valeur.entier = calcul_comparaison_entier(resultat_gauche.valeur.entier, resultat_droite.valeur.entier, type_operation);
        }
        if (resultat_droite.type == CELLULE_IDF){
            decalage_droite_NIS = table_regions[num_region_actuelle].NIS - table_regions[table_declaration[resultat_droite.valeur.entier].region].NIS;
            deplacement_droite = table_declaration[resultat_droite.valeur.entier].execution;
            if (decalage_droite_NIS != 0){
                resultat.valeur.entier = calcul_comparaison_entier(resultat_gauche.valeur.entier, pile[pile[BC+decalage_droite_NIS].valeur.entier + deplacement_droite].valeur.entier, type_operation);
            }
            else{
                resultat.valeur.entier = calcul_comparaison_entier(resultat_gauche.valeur.entier, pile[BC + deplacement_droite].valeur.entier, type_operation);
            }
        }
        if (resultat_droite.type == CELLULE_TYPE_S_T){
            decalage_droite_NIS = table_regions[num_region_actuelle].NIS - table_regions[table_declaration[resultat_droite.valeur.entier].region].NIS;
            deplacement_droite = table_declaration[resultat_droite.valeur.entier].execution;
            init_var_deplacement_struct_tab(table_declaration[table_declaration[resultat_droite.valeur.entier].description].description);
            deplacement_droite += parcours_arbre(arbre_ope->fils->frere->fils, num_region_actuelle).valeur.entier;
            if (decalage_droite_NIS != 0){
                resultat.valeur.entier = calcul_comparaison_entier(resultat_gauche.valeur.entier, pile[pile[BC+decalage_droite_NIS].valeur.entier + deplacement_droite].valeur.entier, type_operation);
            }
            else{
                resultat.valeur.entier = calcul_comparaison_entier(resultat_gauche.valeur.entier, pile[BC + deplacement_droite].valeur.entier, type_operation);
            }
        }
    }
    if (resultat_gauche.type == CELLULE_REEL){
        if (resultat_droite.type == CELLULE_REEL){
            resultat.valeur.entier = calcul_comparaison_reel(resultat_gauche.valeur.reel, resultat_droite.valeur.reel, type_operation);
        }
        if (resultat_droite.type == CELLULE_IDF){
            decalage_droite_NIS = table_regions[num_region_actuelle].NIS - table_regions[table_declaration[resultat_droite.valeur.entier].region].NIS;
            deplacement_droite = table_declaration[resultat_droite.valeur.entier].execution;
            if (decalage_droite_NIS != 0){
                resultat.valeur.entier = calcul_comparaison_reel(resultat_gauche.valeur.reel, pile[pile[BC+decalage_droite_NIS].valeur.entier + deplacement_droite].valeur.reel, type_operation);
            }
            else{
                resultat.valeur.entier = calcul_comparaison_reel(resultat_gauche.valeur.reel, pile[BC + deplacement_droite].valeur.reel, type_operation);
            }
        }
        if (resultat_droite.type == CELLULE_TYPE_S_T){
            decalage_droite_NIS = table_regions[num_region_actuelle].NIS - table_regions[table_declaration[resultat_droite.valeur.entier].region].NIS;
            deplacement_droite = table_declaration[resultat_droite.valeur.entier].execution;
            init_var_deplacement_struct_tab(table_declaration[table_declaration[resultat_droite.valeur.entier].description].description);
            deplacement_droite += parcours_arbre(arbre_ope->fils->frere->fils, num_region_actuelle).valeur.entier;
            if (decalage_droite_NIS != 0){
                resultat.valeur.entier = calcul_comparaison_reel(resultat_gauche.valeur.reel, pile[pile[BC+decalage_droite_NIS].valeur.entier + deplacement_droite].valeur.reel, type_operation);
            }
            else{
                resultat.valeur.entier = calcul_comparaison_reel(resultat_gauche.valeur.reel, pile[BC + deplacement_droite].valeur.reel, type_operation);
            }
        }
    }
    if (resultat_gauche.type == CELLULE_IDF){
        decalage_gauche_NIS = table_regions[num_region_actuelle].NIS - table_regions[table_declaration[resultat_gauche.valeur.entier].region].NIS;
        deplacement_gauche = table_declaration[resultat_gauche.valeur.entier].execution;
        if (resultat_droite.type == CELLULE_CHAR){
            if (decalage_gauche_NIS != 0){
                resultat.valeur.entier = calcul_comparaison_char(pile[pile[BC+decalage_gauche_NIS].valeur.entier + deplacement_gauche].valeur.caractere, resultat_droite.valeur.caractere, type_operation);
            }
            else{
                resultat.valeur.entier = calcul_comparaison_char(pile[BC + deplacement_gauche].valeur.caractere, resultat_droite.valeur.caractere, type_operation);
            }
        }
        if (resultat_droite.type == CELLULE_ENTIER){
            if (decalage_gauche_NIS != 0){
                resultat.valeur.entier = calcul_comparaison_entier(pile[pile[BC+decalage_gauche_NIS].valeur.entier + deplacement_gauche].valeur.entier, resultat_droite.valeur.entier, type_operation);
            }
            else{
                resultat.valeur.entier = calcul_comparaison_entier(pile[BC + deplacement_gauche].valeur.entier, resultat_droite.valeur.entier, type_operation);
            }
        }
        if (resultat_droite.type == CELLULE_REEL){
            if (decalage_gauche_NIS != 0){
                resultat.valeur.entier = calcul_comparaison_reel(pile[pile[BC+decalage_gauche_NIS].valeur.entier + deplacement_gauche].valeur.reel, resultat_droite.valeur.reel, type_operation);
            }
            else{
                resultat.valeur.entier = calcul_comparaison_reel(pile[BC + deplacement_gauche].valeur.reel, resultat_droite.valeur.reel, type_operation);
            }
        }
        if (resultat_droite.type == CELLULE_BOOL){
            if (decalage_gauche_NIS != 0){
                resultat.valeur.entier = calcul_comparaison_entier(pile[pile[BC+decalage_gauche_NIS].valeur.entier + deplacement_gauche].valeur.entier, resultat_droite.valeur.entier, type_operation);
            }
            else{
                resultat.valeur.entier = calcul_comparaison_entier(pile[BC + deplacement_gauche].valeur.entier, resultat_droite.valeur.entier, type_operation);
            }
        }
        if (resultat_droite.type == CELLULE_IDF){
            decalage_droite_NIS = table_regions[num_region_actuelle].NIS - table_regions[table_declaration[resultat_droite.valeur.entier].region].NIS;
            deplacement_droite = table_declaration[resultat_droite.valeur.entier].execution;
            
            if (decalage_droite_NIS != 0){
                if (decalage_gauche_NIS != 0){
                    resultat.valeur.entier = calcul_comparaison_entier(pile[pile[BC+decalage_gauche_NIS].valeur.entier  + deplacement_gauche].valeur.entier, pile[pile[BC+decalage_droite_NIS].valeur.entier + deplacement_droite].valeur.entier, type_operation);
                }
                else{
                    resultat.valeur.entier = calcul_comparaison_entier(pile[BC + deplacement_gauche].valeur.entier, pile[pile[BC+decalage_droite_NIS].valeur.entier + deplacement_droite].valeur.entier, type_operation);
                }
            }
            else{
                if (decalage_gauche_NIS != 0){
                    resultat.valeur.entier = calcul_comparaison_entier(pile[pile[BC+decalage_gauche_NIS].valeur.entier  + deplacement_gauche].valeur.entier, pile[BC + deplacement_droite].valeur.entier, type_operation);
                }
                else{
                    resultat.valeur.entier = calcul_comparaison_entier(pile[BC + deplacement_gauche].valeur.entier, pile[BC + deplacement_droite].valeur.entier, type_operation);
                }
            }
        }
        if (resultat_droite.type == CELLULE_TYPE_S_T){
            decalage_droite_NIS = table_regions[num_region_actuelle].NIS - table_regions[table_declaration[resultat_droite.valeur.entier].region].NIS;
            deplacement_droite = table_declaration[resultat_droite.valeur.entier].execution;
            init_var_deplacement_struct_tab(table_declaration[table_declaration[resultat_droite.valeur.entier].description].description);
            deplacement_droite += parcours_arbre(arbre_ope->fils->frere->fils, num_region_actuelle).valeur.entier;
            
            if (decalage_droite_NIS != 0){
                if (decalage_gauche_NIS != 0){
                    resultat.valeur.entier = calcul_comparaison_entier(pile[pile[BC+decalage_gauche_NIS].valeur.entier  + deplacement_gauche].valeur.entier, pile[pile[BC+decalage_droite_NIS].valeur.entier + deplacement_droite].valeur.entier, type_operation);
                }
                else{
                    resultat.valeur.entier = calcul_comparaison_entier(pile[BC + deplacement_gauche].valeur.entier, pile[pile[BC+decalage_droite_NIS].valeur.entier + deplacement_droite].valeur.entier, type_operation);
                }
            }
            else{
                if (decalage_gauche_NIS != 0){
                    resultat.valeur.entier = calcul_comparaison_entier(pile[pile[BC+decalage_gauche_NIS].valeur.entier  + deplacement_gauche].valeur.entier, pile[BC + deplacement_droite].valeur.entier, type_operation);
                }
                else{
                    resultat.valeur.entier = calcul_comparaison_entier(pile[BC + deplacement_gauche].valeur.entier, pile[BC + deplacement_droite].valeur.entier, type_operation);
                }
            }
        }
    }
    if (resultat_gauche.type == CELLULE_TYPE_S_T){
        decalage_gauche_NIS = table_regions[num_region_actuelle].NIS - table_regions[table_declaration[resultat_gauche.valeur.entier].region].NIS;
        deplacement_gauche = table_declaration[resultat_gauche.valeur.entier].execution;
        init_var_deplacement_struct_tab(table_declaration[table_declaration[resultat_gauche.valeur.entier].description].description);
        deplacement_gauche += parcours_arbre(arbre_ope->fils->fils, num_region_actuelle).valeur.entier;
        if (resultat_droite.type == CELLULE_CHAR){
            if (decalage_gauche_NIS != 0){
                resultat.valeur.entier = calcul_comparaison_char(pile[pile[BC+decalage_gauche_NIS].valeur.entier + deplacement_gauche].valeur.caractere, resultat_droite.valeur.caractere, type_operation);
            }
            else{
                resultat.valeur.entier = calcul_comparaison_char(pile[BC + deplacement_gauche].valeur.caractere, resultat_droite.valeur.caractere, type_operation);
            }
        }
        if (resultat_droite.type == CELLULE_ENTIER){
            if (decalage_gauche_NIS != 0){
                resultat.valeur.entier = calcul_comparaison_entier(pile[pile[BC+decalage_gauche_NIS].valeur.entier + deplacement_gauche].valeur.entier, resultat_droite.valeur.entier, type_operation);
            }
            else{
                resultat.valeur.entier = calcul_comparaison_entier(pile[BC + deplacement_gauche].valeur.entier, resultat_droite.valeur.entier, type_operation);
            }
        }
        if (resultat_droite.type == CELLULE_REEL){
            if (decalage_gauche_NIS != 0){
                resultat.valeur.entier = calcul_comparaison_reel(pile[pile[BC+decalage_gauche_NIS].valeur.entier + deplacement_gauche].valeur.reel, resultat_droite.valeur.reel, type_operation);
            }
            else {
                resultat.valeur.entier = calcul_comparaison_reel(pile[BC + deplacement_gauche].valeur.reel, resultat_droite.valeur.reel, type_operation);
            }
        }
        if (resultat_droite.type == CELLULE_BOOL){
            if (decalage_gauche_NIS != 0){
                resultat.valeur.entier = calcul_comparaison_entier(pile[pile[BC+decalage_gauche_NIS].valeur.entier + deplacement_gauche].valeur.entier, resultat_droite.valeur.entier, type_operation);
            }
            else{
                resultat.valeur.entier = calcul_comparaison_entier(pile[BC + deplacement_gauche].valeur.entier, resultat_droite.valeur.entier, type_operation);
            }
        }
        if (resultat_droite.type == CELLULE_IDF){
            decalage_droite_NIS = table_regions[num_region_actuelle].NIS - table_regions[table_declaration[resultat_droite.valeur.entier].region].NIS;
            deplacement_droite = table_declaration[resultat_droite.valeur.entier].execution;
            
            if (decalage_droite_NIS != 0){
                if (decalage_gauche_NIS != 0){
                    resultat.valeur.entier = calcul_comparaison_entier(pile[pile[BC+decalage_gauche_NIS].valeur.entier  + deplacement_gauche].valeur.entier, pile[pile[BC+decalage_droite_NIS].valeur.entier + deplacement_droite].valeur.entier, type_operation);
                }
                else{
                    resultat.valeur.entier = calcul_comparaison_entier(pile[BC + deplacement_gauche].valeur.entier, pile[pile[BC+decalage_droite_NIS].valeur.entier + deplacement_droite].valeur.entier, type_operation);
                }
            }
            else{
                if (decalage_gauche_NIS != 0){
                    resultat.valeur.entier = calcul_comparaison_entier(pile[pile[BC+decalage_gauche_NIS].valeur.entier  + deplacement_gauche].valeur.entier, pile[BC + deplacement_droite].valeur.entier, type_operation);
                }
                else{
                    resultat.valeur.entier = calcul_comparaison_entier(pile[BC + deplacement_gauche].valeur.entier, pile[BC + deplacement_droite].valeur.entier, type_operation);
                }
            }
        }
        if (resultat_droite.type == CELLULE_TYPE_S_T){
            decalage_droite_NIS = table_regions[num_region_actuelle].NIS - table_regions[table_declaration[resultat_droite.valeur.entier].region].NIS;
            deplacement_droite = table_declaration[resultat_droite.valeur.entier].execution;
            init_var_deplacement_struct_tab(table_declaration[table_declaration[resultat_droite.valeur.entier].description].description);
            deplacement_droite += parcours_arbre(arbre_ope->fils->frere->fils, num_region_actuelle).valeur.entier;
            
            if (decalage_droite_NIS != 0){
                if (decalage_gauche_NIS != 0){
                    resultat.valeur.entier = calcul_comparaison_entier(pile[pile[BC+decalage_gauche_NIS].valeur.entier  + deplacement_gauche].valeur.entier, pile[pile[BC+decalage_droite_NIS].valeur.entier + deplacement_droite].valeur.entier, type_operation);
                }
                else{
                    resultat.valeur.entier = calcul_comparaison_entier(pile[BC + deplacement_gauche].valeur.entier, pile[pile[BC+decalage_droite_NIS].valeur.entier + deplacement_droite].valeur.entier, type_operation);
                }
            }
            else{
                if (decalage_gauche_NIS != 0){
                    resultat.valeur.entier = calcul_comparaison_entier(pile[pile[BC+decalage_gauche_NIS].valeur.entier  + deplacement_gauche].valeur.entier, pile[BC + deplacement_droite].valeur.entier, type_operation);
                }
                else{
                    resultat.valeur.entier = calcul_comparaison_entier(pile[BC + deplacement_gauche].valeur.entier, pile[BC + deplacement_droite].valeur.entier, type_operation);
                }
            }
        }
    }
    resultat.type = CELLULE_BOOL;
    return resultat;
}

/** --------------------------------------*
* @author : MATHEVON Baptiste
* @brief : Calcul la taille d'une dimension d'un tableau
*-----------------------------------------*/
int calcul_taille_dimension(int borne_inf, int borne_sup){
    int taille;
    int borne_inf_tmp = borne_inf;
    int borne_sup_tmp = borne_sup;
    /*un tableau ne peut pas avoir une borne sup < borne inf OU une taille de 0 -> aucun sens*/
    if (borne_sup < borne_inf){ 
        printf("ERREUR [ligne %d car. %d] (bornes tableau) : la borne supérieur d'une dimension ne peut pas être inférieur à sa borne inférieur\n", numero_ligne+2/*numero ligne compte -2 -> trouver le bug*/, numero_car);
        return -1;
    }
    if (borne_sup == borne_inf){ 
        printf("WARNING [ligne %d car. %d] (bornes tableau) : les deux bornes de votre tableau sont égales -> inutile (tableau de 0 cases)\n", numero_ligne+1/*idem ici -> bug*/, numero_car);
        return 0;
    }

    taille = borne_sup_tmp - borne_inf_tmp + 1;

    return taille;
}

/*----------------------------------------*
|                                         |
| ~~~ PARCOURS DE L'ARBRE ~~~
|                                         |
*-----------------------------------------*/
/** --------------------------------------*
* @author : MATHEVON Baptiste
* @brief : Parcours l'arbre a récursivement
*-----------------------------------------*/
struct valeur_cellule parcours_arbre(arbre a, int num_region_appelante){
    struct valeur_cellule resultat; /*Resultat du parcours de l'arbre*/
    int deplacement;
    int BC_region_appelante;
    int deplacement_BC;
    int num_region_actuelle;
    int NIS;
    int decalage_NIS; 
    int num_region_resultat;
    int num_lexico_champ;
    int indice_tab_si_champ;

    /*----------------------------------------*
    | Pour stocker l'entrée de l'utilisateur
    *-----------------------------------------*/
    if (a->type == T_LISTE_ARGUMENTS_LIRE){char chaine[500];}

    struct valeur_cellule resultat_gauche; /*Pour calculcs arithmétiques*/
    struct valeur_cellule resultat_droite;

    num_region_actuelle = num_region_appelante; /*La région courante devient la région appelante dans le cas général*/
    
    switch (a->type){
        /*----------------------------------------*
        |                                         |
        | ~~~ T_VIDE ~~~
        |                                         |
        *-----------------------------------------*/
        case T_VIDE : 
            /*----------------------------------------*
            | Instruction Vide -> rien à faire
            *-----------------------------------------*/
            break;

        /*----------------------------------------*
        |                                         |
        | ~~~ T_LISTE ~~~
        |                                         |
        *-----------------------------------------*/
        case T_LISTE : 
            /*----------------------------------------*
            | Continue le parcours de l'arbre en parcourant le fils
            *-----------------------------------------*/
            resultat = parcours_arbre(a->fils, num_region_actuelle);
            break;

        /*----------------------------------------*
        |                                         |
        | ~~~ T_LISTE_CHAMPS ~~~
        |                                         |
        *-----------------------------------------*/
        case T_LISTE_CHAMPS :
            /*----------------------------------------*
            | Récupère le num lexico du champ
            *-----------------------------------------*/
            num_lexico_champ = table_types[indice_description_tmp + indice_champ_tmp];
            resultat.valeur.entier = 0;
            resultat.type = CELLULE_ENTIER; 

            /*----------------------------------------*
            | Si on a trouvé le bon champ dans la liste des champs on renvoie son déplacement
            *-----------------------------------------*/
            if (num_lexico_champ == a->fils->num_lexico){
                resultat.valeur.entier = table_types[indice_description_tmp + indice_champ_tmp + 2];
            }
            /*----------------------------------------*
            | Sinon on parcourt la table des types a la recherche du champ
            *-----------------------------------------*/
            else{
                /*----------------------------------------*
                | Si on a trouvé un champ de type structure et qu'on est dans le champ de cette structure
                *-----------------------------------------*/
                if (table_declaration[table_types[indice_description_tmp + indice_champ_tmp + 1]].nature == TYPE_S && table_types[indice_description_tmp + indice_champ_tmp + 1]== num_lexico_champ){
                    indice_description_tmp = table_declaration[table_types[indice_description_tmp + indice_champ_tmp + 1]].description;
                    indice_champ_tmp = 1;
                    resultat.valeur.entier = parcours_arbre(a, num_region_actuelle).valeur.entier;
                }
                /*----------------------------------------*
                | Sinon on continue de parcourir la table des types
                *-----------------------------------------*/
                else if (indice_champ_tmp/3 < table_types[indice_description_tmp]){
                    indice_champ_tmp += 3;
                    resultat.valeur.entier = parcours_arbre(a, num_region_actuelle).valeur.entier;
                    return resultat;
                }
            } 

            /*----------------------------------------*
            | Si le champ possède des indices
            *-----------------------------------------*/
            if (a->fils->fils != NULL){
                /*WARNING -> risque de poser de gros problèmes si un type ou tableau définit dans la zone de débordement car la on récupère avec le numéro lexico
                il faut faire une fonction comme association_nom qui permet de récupérer le numéro de déclaration a partir du numéro lexico*/
                /*----------------------------------------*
                | On récupère le déplacement pour les indices -> init des variables
                *-----------------------------------------*/
                taille_dimension_tmp = 1;
                indice_tab_taille_dimensions = 0;
                indice_tableau_tmp = table_declaration[table_types[indice_description_tmp + indice_champ_tmp + 1]].description + 1;
                resultat.valeur.entier += parcours_arbre(a->fils->fils, num_region_actuelle).valeur.entier;
            }

            /*----------------------------------------*
            | Si la liste des champs continue on parcourt la suite et on ajoute leurs déplacements
            *-----------------------------------------*/
            if (a->fils->frere != NULL){
                indice_description_tmp = table_declaration[table_types[indice_description_tmp + indice_champ_tmp + 1]].description;
                indice_champ_tmp = 1;
                resultat.valeur.entier += parcours_arbre(a->fils->frere, num_region_actuelle).valeur.entier;
            }

            return resultat;
            break;

        /*----------------------------------------*
        |                                         |
        | ~~~ T_LISTE_INDICES ~~~
        |                                         |
        *-----------------------------------------*/
        case T_LISTE_INDICES :
            /*----------------------------------------*
            | On accède aux champs d'un tableau en passant l'indice de la case en paramètre (de 0 a n avec n taille de la dimension)
            *-----------------------------------------*/
            indice_tab_si_champ = indice_tableau_tmp;
            tab_taille_dimensions = realloc(tab_taille_dimensions, (indice_tab_taille_dimensions+1)*sizeof(int));
            resultat = parcours_arbre(a->fils, num_region_actuelle);

            /*----------------------------------------*
            | NOTE : pour l'instant accès aux indices que par des constantes entières ou IDF -> il faut rajouter appel FCT
            *-----------------------------------------*/
            if (resultat.type == CELLULE_IDF){
                num_region_resultat = table_declaration[resultat.valeur.entier].region;
                int decalage_NIS_resultat = table_regions[num_region_resultat].NIS - table_regions[num_region_actuelle].NIS;
                if (decalage_NIS_resultat != 0){
                    resultat.valeur.entier = pile[pile[BC+decalage_NIS_resultat].valeur.entier + table_declaration[resultat.valeur.entier].execution].valeur.entier;
                }
                else{
                    resultat.valeur.entier = pile[BC + table_declaration[resultat.valeur.entier].execution].valeur.entier;
                }
            }

            /*----------------------------------------*
            | On récupère le déplacement nécessaire pour accéder à la case du tableau
            *-----------------------------------------*/
            /*----------------------------------------*
            | Si on est dans une dimension > 0 on multiplie par la taille des dimensions précédentes pour accéder à la bonne case
            *-----------------------------------------*/
            if (taille_dimension_tmp != 0){
                resultat.valeur.entier -= 1;
                for (int i=0; i<indice_tab_taille_dimensions; i++){
                    resultat.valeur.entier = (resultat.valeur.entier)*tab_taille_dimensions[i];
                }
            }
            /*----------------------------------------*
            | Si on est dans la première dimension pas besoin de multiplier par la taille des dimensions précédentes
            *-----------------------------------------*/
            else{
                resultat.valeur.entier -= 1; //indice 0 
            }

            /*----------------------------------------*
            | Multiplication du déplacement par la taille d'une case du tableau
            *-----------------------------------------*/
            resultat.valeur.entier *= taille_case_tab;

            /*----------------------------------------*
            | On récupère la taille de la dimension actuelle et on l'insère dans le tableau des tailles de dimensions
            *-----------------------------------------*/
            taille_dimension_tmp = calcul_taille_dimension(table_types[indice_tableau_tmp+1], table_types[indice_tableau_tmp+2]);
            tab_taille_dimensions[indice_tab_taille_dimensions] = taille_dimension_tmp;
            indice_tab_taille_dimensions++;

            /*----------------------------------------*
            | Si la liste des indices continue on parcourt la suite et on ajoute leurs déplacements
            *-----------------------------------------*/
            if (a->fils->frere != NULL){
                indice_tableau_tmp+=2;
                resultat.valeur.entier += parcours_arbre(a->fils->frere, num_region_actuelle).valeur.entier;
            }

            /*----------------------------------------*
            | Si l'indice possède des champs
            *-----------------------------------------*/
            if (a->frere != NULL){
                /*----------------------------------------*
                | On récupère le déplacement pour les champs -> init des variables
                *-----------------------------------------*/
                init_var_deplacement_struct_tab(table_declaration[table_types[indice_tab_si_champ-1]].description);
                resultat.valeur.entier += parcours_arbre(a->frere, num_region_actuelle).valeur.entier;
            }

            return resultat;

            break;

        /*----------------------------------------*
        |                                         |
        | ~~~ T_LISTE_ARGUMENTS ~~~
        |                                         |
        *-----------------------------------------*/
        case T_LISTE_ARGUMENTS : 
            resultat = parcours_arbre(a->fils, num_region_actuelle);

            int num_lexico_argument = table_types[num_description_tmp+num_argument_courant];
            int num_declaration_argument = numero_declaration_argument(num_lexico_argument, num_region_actuelle);

            /*----------------------------------------*
            | On affecte la valeur de l'argument à la variable correspondante
            *-----------------------------------------*/
            if (resultat.type == CELLULE_IDF){ 
                /*----------------------------------------*
                | BC de la région ou l'on a passé l'argument en paramètre pour pouvoir récupérer sa valeur
                *-----------------------------------------*/ 
                int BC_tmp = pile[BC].valeur.entier;
                num_region_resultat = table_declaration[resultat.valeur.entier].region;
                /*----------------------------------------*
                | Décalage entre la région ou l'argument est passé en paramètre et la région ou l'on veut récupérer sa valeur
                | On a stocké dans num_region_liste_arguments le numéro de la région qui passe les arguments en paramètres
                *-----------------------------------------*/
                decalage_NIS = table_regions[num_region_appelante_liste_arguments].NIS - table_regions[num_region_resultat].NIS;

                int deplacement = table_declaration[resultat.valeur.entier].execution;

                if (decalage_NIS != 0){
                    pile[BC + table_declaration[num_declaration_argument].execution] = pile[pile[BC_tmp+decalage_NIS].valeur.entier + table_declaration[resultat.valeur.entier].execution];
                }
                else{
                    pile[BC + table_declaration[num_declaration_argument].execution] = pile[BC_tmp + table_declaration[resultat.valeur.entier].execution];
                }
            }
            else{
                pile[BC + table_declaration[num_declaration_argument].execution] = resultat;
            }
            
            /*----------------------------------------*
            | Si la liste des arguments continue
            *-----------------------------------------*/
            if (a->fils->frere != NULL){
                num_argument_courant+=2; //Décalage dans la table des types pour passer à l'argument suivant
                resultat = parcours_arbre(a->fils->frere, num_region_actuelle);
            }

            break;

        /*----------------------------------------*
        |                                         |
        | ~~~ T_RETOURNE ~~~
        |                                         |
        *-----------------------------------------*/
        case T_RETOURNE : 
            /*----------------------------------------*
            | Si il y a une expression à retourner
            *-----------------------------------------*/
            if (a->fils != NULL){
                resultat = parcours_arbre(a->fils, num_region_actuelle);
            }
            /*----------------------------------------*
            | Renvoie la valeur de l'expression qu'on veut retourner plutôt que son numéro de déclaration
            *-----------------------------------------*/
            if (resultat.type == CELLULE_IDF){
                num_region_resultat = table_declaration[resultat.valeur.entier].region;
                int decalage_NIS_resultat = table_regions[num_region_resultat].NIS - table_regions[num_region_actuelle].NIS;
                if (decalage_NIS_resultat != 0){
                    resultat = pile[pile[BC+decalage_NIS_resultat].valeur.entier + table_declaration[resultat.valeur.entier].execution];
                }
                else{
                    resultat = pile[BC + table_declaration[resultat.valeur.entier].execution];
                }
            }
            /*----------------------------------------*
            | FAIRE LES AUTRES VALEURS DE RETURN (APPEL, BOOL, etc...) ?
            *-----------------------------------------*/
            return resultat;

        /*----------------------------------------*
        |                                         |
        | ~~~ T_IDF ~~~
        |                                         |
        *-----------------------------------------*/
        case T_IDF : 
            /*----------------------------------------*
            | Renvoie le numéro de déclaration de l'IDF 
            *-----------------------------------------*/
            resultat.valeur.entier = a->num_declaration;
            if (table_declaration[table_declaration[a->num_declaration].description].nature == TYPE_S || table_declaration[table_declaration[a->num_declaration].description].nature == TYPE_T){
                resultat.type = CELLULE_TYPE_S_T;
            }
            else{
                resultat.type = CELLULE_IDF;
            }
            return resultat;

        /*----------------------------------------*
        |                                         |
        | ~~~ T_CSTE_ENTIERE ~~~
        |                                         |
        *-----------------------------------------*/
        case T_CSTE_E : 
            /*----------------------------------------*
            | Renvoie la valeur de la constante
            *-----------------------------------------*/
            resultat.valeur.entier = a->num_lexico;
            resultat.type = CELLULE_ENTIER;
            return resultat;

        /*----------------------------------------*
        |                                         |
        | ~~~ T_CSTE_FLOAT ~~~
        |                                         |
        *-----------------------------------------*/
        case T_CSTE_F :
            /*----------------------------------------*
            | Renvoie la valeur de la constante
            *-----------------------------------------*/
            resultat.valeur.reel = atof(lexeme(a->num_lexico));
            resultat.type = CELLULE_REEL;
            return resultat;

        /*----------------------------------------*
        |                                         |
        | ~~~ T_CSTE_CHAR ~~~
        |                                         |
        *-----------------------------------------*/
        case T_CSTE_CHAR :
            /*----------------------------------------*
            | Renvoie la valeur de la constante
            *-----------------------------------------*/
            resultat.valeur.caractere = lexeme(a->num_lexico)[1];
            resultat.type = CELLULE_CHAR;
            return resultat;

        /*----------------------------------------*
        |                                         |
        | ~~~ T_CSTE_BOOL ~~~
        |                                         |
        *-----------------------------------------*/
        case T_CSTE_BOOL :
            /*----------------------------------------*
            | Renvoie la valeur de la constante
            *-----------------------------------------*/
            resultat.valeur.entier = a->num_lexico;
            resultat.type = CELLULE_BOOL;
            return resultat;

        /*----------------------------------------*
        |                                         |
        | ~~~ T_PLUS ~~~
        |                                         |
        *-----------------------------------------*/
        case T_PLUS :
            /*----------------------------------------*
            | Récupère la valeur de l'expression de gauche
            *-----------------------------------------*/
            resultat_gauche = parcours_arbre(a->fils, num_region_actuelle);
            /*----------------------------------------*
            | Récupère la valeur de l'expression de droite
            *-----------------------------------------*/
            resultat_droite = parcours_arbre(a->fils->frere, num_region_actuelle);
            /*----------------------------------------*
            | Retourne le résultat de l'opération en fonction des résultats des deux expressions
            *-----------------------------------------*/
            return calcul_arithmetique(num_region_actuelle, resultat_gauche, resultat_droite, T_PLUS, a);

        /*----------------------------------------*
        |                                         |
        | ~~~ T_MOINS ~~~
        |                                         |
        *-----------------------------------------*/
        case T_MOINS : 
            /*----------------------------------------*/
            resultat_gauche = parcours_arbre(a->fils, num_region_actuelle);
            /*----------------------------------------*/
            resultat_droite = parcours_arbre(a->fils->frere, num_region_actuelle);
            /*----------------------------------------*/
            return calcul_arithmetique(num_region_actuelle, resultat_gauche, resultat_droite, T_MOINS, a);

        /*----------------------------------------*
        |                                         |
        | ~~~ T_MULT ~~~
        |                                         |
        *-----------------------------------------*/
        case T_MULT : 
            /*----------------------------------------*/
            resultat_gauche = parcours_arbre(a->fils, num_region_actuelle);
            /*----------------------------------------*/
            resultat_droite = parcours_arbre(a->fils->frere, num_region_actuelle);
            /*----------------------------------------*/
            return calcul_arithmetique(num_region_actuelle, resultat_gauche, resultat_droite, T_MULT, a);

        /*----------------------------------------*
        |                                         |
        | ~~~ T_DIV ~~~
        |                                         |
        *-----------------------------------------*/
        case T_DIV :
            /*----------------------------------------*/
            resultat_gauche = parcours_arbre(a->fils, num_region_actuelle);
            /*----------------------------------------*/
            resultat_droite = parcours_arbre(a->fils->frere, num_region_actuelle);
            /*----------------------------------------*/
            return calcul_arithmetique(num_region_actuelle, resultat_gauche, resultat_droite, T_DIV, a);

        /*----------------------------------------*
        |                                         |
        | ~~~ T_OU ~~~
        |                                         |
        *-----------------------------------------*/
        case T_OU : 
            resultat_gauche = parcours_arbre(a->fils, num_region_actuelle);
            resultat_droite = parcours_arbre(a->fils->frere, num_region_actuelle);
            return calcul_logique(num_region_actuelle, resultat_gauche, resultat_droite, T_OU, a);

        /*----------------------------------------*
        |                                         |
        | ~~~ T_ET ~~~
        |                                         |
        *-----------------------------------------*/
        case T_ET : 
            resultat_gauche = parcours_arbre(a->fils, num_region_actuelle);
            resultat_droite = parcours_arbre(a->fils->frere, num_region_actuelle);
            return calcul_logique(num_region_actuelle, resultat_gauche, resultat_droite, T_ET, a);

        /*----------------------------------------*
        |                                         |
        | ~~~ T_NON ~~~
        |                                         |
        *-----------------------------------------*/
        case T_NON : 
            /*----------------------------------------*/
            resultat = parcours_arbre(a->fils, num_region_actuelle);
            /*----------------------------------------*/
            return inverse_bool(num_region_actuelle, resultat, a);

        /*----------------------------------------*
        |                                         |
        | ~~~ T_INF ~~~
        |                                         |
        *-----------------------------------------*/
        case T_INF :
            resultat_gauche = parcours_arbre(a->fils, num_region_actuelle);
            resultat_droite = parcours_arbre(a->fils->frere, num_region_actuelle);
            return calcul_comparaison(num_region_actuelle, resultat_gauche, resultat_droite, T_INF, a);

        /*----------------------------------------*
        |                                         |
        | ~~~ T_SUP ~~~
        |                                         |
        *-----------------------------------------*/
        case T_SUP : 
            resultat_gauche = parcours_arbre(a->fils, num_region_actuelle);
            resultat_droite = parcours_arbre(a->fils->frere, num_region_actuelle);
            return calcul_comparaison(num_region_actuelle, resultat_gauche, resultat_droite, T_SUP, a);
        
        /*----------------------------------------*
        |                                         |
        | ~~~ T_DOUBLEEGAL ~~~
        |                                         |
        *-----------------------------------------*/
        case T_DOUBLEEGAL : 
            resultat_gauche = parcours_arbre(a->fils, num_region_actuelle);
            resultat_droite = parcours_arbre(a->fils->frere, num_region_actuelle);
            return calcul_comparaison(num_region_actuelle, resultat_gauche, resultat_droite, T_DOUBLEEGAL, a);
        
        /*----------------------------------------*
        |                                         |
        | ~~~ T_SUP_EGAL ~~~
        |                                         |
        *-----------------------------------------*/
        case T_SUP_EGAL : 
            resultat_gauche = parcours_arbre(a->fils, num_region_actuelle);
            resultat_droite = parcours_arbre(a->fils->frere, num_region_actuelle);
            return calcul_comparaison(num_region_actuelle, resultat_gauche, resultat_droite, T_SUP_EGAL, a);
        
        /*----------------------------------------*
        |                                         |
        | ~~~ T_INF_EGAL ~~~
        |                                         |
        *-----------------------------------------*/
        case T_INF_EGAL : 
            resultat_gauche = parcours_arbre(a->fils, num_region_actuelle);
            resultat_droite = parcours_arbre(a->fils->frere, num_region_actuelle);
            return calcul_comparaison(num_region_actuelle, resultat_gauche, resultat_droite, T_INF_EGAL, a);
           
        /*----------------------------------------*
        |                                         |
        | ~~~ T_SI_ALORS ~~~
        |                                         |
        *-----------------------------------------*/
        case T_SI_ALORS : 
            /*----------------------------------------*
            | Récupère la valeur du test
            *-----------------------------------------*/
            resultat_gauche = parcours_arbre(a->fils, num_region_actuelle);
            /*----------------------------------------*
            | Si le test est vrai on parcourt le fils
            *-----------------------------------------*/
            if (resultat_gauche.valeur.entier == 1){
                resultat = parcours_arbre(a->fils->frere->fils, num_region_actuelle);
            }
            break;

        /*----------------------------------------*
        |                                         |
        | ~~~ T_SI_ALORS_SINON ~~~
        |                                         |
        *-----------------------------------------*/
        case T_SI_ALORS_SINON : 
            /*----------------------------------------*
            | Récupère la valeur du test
            *-----------------------------------------*/
            resultat_gauche = parcours_arbre(a->fils, num_region_actuelle);
            /*----------------------------------------*
            | Si le test est vrai on parcourt le fils
            *-----------------------------------------*/
            if (resultat_gauche.valeur.entier == 1){
                resultat = parcours_arbre(a->fils->frere->fils, num_region_actuelle);
            }
            /*----------------------------------------*
            | Sinon on parcourt le frere
            *-----------------------------------------*/
            else{
                if (a->fils->frere->frere != NULL){
                    resultat = parcours_arbre(a->fils->frere->frere, num_region_actuelle);
                }
            }
            break;

        /*----------------------------------------*
        |                                         |
        | ~~~ T_POUR ~~~
        |                                         |
        *-----------------------------------------*/
        case T_POUR :
            /*----------------------------------------*
            | Affectation de la variable de boucle (init ex. i=0)
            *-----------------------------------------*/
            parcours_arbre(a->fils, num_region_actuelle);
            /*----------------------------------------*
            | Récupère la valeur du test de la boucle (condition ex. i<10)
            *-----------------------------------------*/
            resultat = parcours_arbre(a->fils->frere, num_region_actuelle);
            /*----------------------------------------*
            | Tant que le test est vrai on parcourt la liste d'instruction de la boucle 
            *-----------------------------------------*/
            while(resultat.valeur.entier == 1){
                /*----------------------------------------*
                | Liste d'instructions de la boucle -> l'opération sur la variable de la boucle se situe dans le frere de cette liste (ex. i = i+1)
                *-----------------------------------------*/
                parcours_arbre(a->fils->frere->frere, num_region_actuelle);
                /*----------------------------------------*
                | Mise à jour de la valeur du test de la boucle
                *-----------------------------------------*/    
                resultat = parcours_arbre(a->fils->frere, num_region_actuelle);
            }

            break;

        /*----------------------------------------*
        |                                         |
        | ~~~ T_TANT_QUE ~~~
        |                                         |
        *-----------------------------------------*/
        case T_TANT_QUE :
            /*----------------------------------------*
            | Récupère la valeur du test de la boucle (condition ex. i<10)
            *-----------------------------------------*/
            resultat = parcours_arbre(a->fils, num_region_actuelle);
            /*----------------------------------------*
            | Tant que le test est vrai on parcourt la liste d'instruction de la boucle 
            *-----------------------------------------*/
            while(resultat.valeur.entier == 1){
                /*----------------------------------------*
                | Liste d'instructions de la boucle
                *-----------------------------------------*/
                parcours_arbre(a->fils->frere, num_region_actuelle);
                /*----------------------------------------*
                | Mise à jour de la valeur du test de la boucle
                *-----------------------------------------*/    
                resultat = parcours_arbre(a->fils, num_region_actuelle);
            }

            break;
        
        /*----------------------------------------*
        |                                         |
        | ~~~ T_FAIRE_TANT_QUE ~~~
        |                                         |
        *-----------------------------------------*/
        case T_FAIRE_TANT_QUE :
            /*----------------------------------------*
            | Liste d'instructions de la boucle
            *-----------------------------------------*/
            parcours_arbre(a->fils, num_region_actuelle);
            /*----------------------------------------*
            | Récupère la valeur du test de la boucle (condition ex. i<10)
            *-----------------------------------------*/
            resultat = parcours_arbre(a->fils->frere, num_region_actuelle);
            /*----------------------------------------*
            | Tant que le test est vrai on parcourt la liste d'instruction de la boucle 
            *-----------------------------------------*/
            while(resultat.valeur.entier == 1){
                /*----------------------------------------*
                | Liste d'instructions de la boucle
                *-----------------------------------------*/
                parcours_arbre(a->fils, num_region_actuelle);
                /*----------------------------------------*
                | Mise à jour de la valeur du test de la boucle
                *-----------------------------------------*/    
                resultat = parcours_arbre(a->fils->frere, num_region_actuelle);
            }

            break;
        /*----------------------------------------*
        |                                         |
        | ~~~ T_AFFECT ~~~
        |                                         |
        *-----------------------------------------*/
        case T_AFFECT : 
            /*----------------------------------------*
            | Récupère le déplacement nécessaire pour accéder à la variable qu'on veut affecter
            *-----------------------------------------*/
            resultat = parcours_arbre(a->fils, num_region_actuelle);
            deplacement = table_declaration[resultat.valeur.entier].execution;

            /*----------------------------------------*
            | Si c'est un TYPE_S OU TYPE_T On parcourt la liste des champs et des indices
            *-----------------------------------------*/
            if (resultat.type == CELLULE_TYPE_S_T){
                init_var_deplacement_struct_tab(table_declaration[table_declaration[resultat.valeur.entier].description].description);
                /*----------------------------------------*
                | On ajoute le déplacement pour accéder aux bons champs/indices
                *-----------------------------------------*/
                deplacement += parcours_arbre(a->fils->fils, num_region_actuelle).valeur.entier;
            }
            
            decalage_NIS = table_regions[num_region_actuelle].NIS - table_regions[table_declaration[resultat.valeur.entier].region].NIS;
            /*----------------------------------------*
            | Récupère la valeur de l'expression qu'on veut affecter
            *-----------------------------------------*/
            resultat = parcours_arbre(a->fils->frere, num_region_actuelle);

            /*----------------------------------------*
            | Modifie la valeur de la pile à l'adresse de la variable
            *-----------------------------------------*/
            if (resultat.type == CELLULE_ENTIER){
                /*----------------------------------------*
                | Si pas dans la même région 
                *-----------------------------------------*/
                if (decalage_NIS > 0){
                    pile[pile[BC+decalage_NIS].valeur.entier + deplacement] = resultat;
                    pile[pile[BC+decalage_NIS].valeur.entier + deplacement].type = CELLULE_ENTIER;
                }
                else{
                    pile[BC + deplacement] = resultat;
                    pile[BC + deplacement].type = CELLULE_ENTIER;
                }
            }
            if (resultat.type == CELLULE_REEL){
                if (decalage_NIS > 0){
                    pile[pile[BC+decalage_NIS].valeur.entier + deplacement] = resultat;
                    pile[pile[BC+decalage_NIS].valeur.entier + deplacement].type = CELLULE_REEL;
                }
                else{
                    pile[BC + deplacement] = resultat;
                    pile[BC + deplacement].type = CELLULE_REEL;
                }
            }
            if (resultat.type == CELLULE_CHAR){
                if (decalage_NIS > 0){
                    pile[pile[BC+decalage_NIS].valeur.entier + deplacement] = resultat;
                    pile[pile[BC+decalage_NIS].valeur.entier + deplacement].type = CELLULE_CHAR;
                }
                else{
                    pile[BC + deplacement] = resultat;
                    pile[BC + deplacement].type = CELLULE_CHAR;
                }                
            }
            if (resultat.type == CELLULE_BOOL){
                if (decalage_NIS > 0){
                    pile[pile[BC+decalage_NIS].valeur.entier + deplacement] = resultat;
                    pile[pile[BC+decalage_NIS].valeur.entier + deplacement].type = CELLULE_BOOL;
                }
                else{
                    pile[BC + deplacement] = resultat;
                    pile[BC + deplacement].type = CELLULE_BOOL;
                }
            }
            if (resultat.type == CELLULE_IDF){
                num_region_resultat = table_declaration[resultat.valeur.entier].region;
                int decalage_NIS_resultat = table_regions[num_region_actuelle].NIS - table_regions[num_region_resultat].NIS;
                if (decalage_NIS > 0){
                    if (decalage_NIS_resultat > 0){

                        pile[pile[BC+decalage_NIS].valeur.entier + deplacement] = pile[pile[BC+decalage_NIS_resultat].valeur.entier + table_declaration[resultat.valeur.entier].execution];
                    }
                    else{
                        pile[pile[BC+decalage_NIS].valeur.entier + deplacement] = pile[BC + table_declaration[resultat.valeur.entier].execution];
                    }
                }
                else{
                    if (decalage_NIS_resultat > 0){
                        pile[BC + deplacement] = pile[pile[BC + decalage_NIS_resultat].valeur.entier + table_declaration[resultat.valeur.entier].execution];
                    }
                    else{
                        pile[BC + deplacement] = pile[BC + table_declaration[resultat.valeur.entier].execution];
                    }
                }
            }
            if (resultat.type == CELLULE_TYPE_S_T){
                init_var_deplacement_struct_tab(table_declaration[table_declaration[resultat.valeur.entier].description].description);
                int deplacement_resultat = table_declaration[resultat.valeur.entier].execution;
                deplacement_resultat += parcours_arbre(a->fils->frere->fils, num_region_actuelle).valeur.entier;
                int decalage_NIS_resultat = table_regions[num_region_actuelle].NIS - table_regions[table_declaration[resultat.valeur.entier].region].NIS;
                if (decalage_NIS > 0){
                    if (decalage_NIS_resultat > 0){
                        pile[pile[BC+decalage_NIS].valeur.entier + deplacement] = pile[pile[BC+decalage_NIS_resultat].valeur.entier + deplacement_resultat];
                    }
                    else{
                        pile[pile[BC+decalage_NIS].valeur.entier + deplacement] = pile[BC + deplacement_resultat];
                    }
                }
                else{
                    if (decalage_NIS_resultat > 0){
                        pile[BC + deplacement] = pile[pile[BC + decalage_NIS_resultat].valeur.entier + deplacement_resultat];
                    }
                    else{
                        pile[BC + deplacement] = pile[BC + deplacement_resultat];
                    }
                }
            }

            break;

        /*----------------------------------------*
        |                                         |
        | ~~~ T_APPEL_PROCEDURE ~~~
        |                                         |
        *-----------------------------------------*/
        case T_APPEL_PROC :
            /*----------------------------------------*
            | Changement de numéro de région actuelle pour passer la région de la procédure appelé en paramètre (procédure appelante)
            *-----------------------------------------*/
            num_region_actuelle = table_declaration[a->num_declaration].execution;

            /*----------------------------------------*
            | Stockage de la BC de la région appelante pour le chainage dynamique
            *-----------------------------------------*/
            BC_region_appelante = BC;

            /*----------------------------------------*
            | Chainage statique
            *-----------------------------------------*/
            NIS = table_regions[num_region_actuelle].NIS;
            tab_chainage_statique = realloc(tab_chainage_statique, NIS*sizeof(int));
            if (NIS > table_regions[num_region_appelante].NIS && indice_tab_chainage_statique < NIS){
                tab_chainage_statique[indice_tab_chainage_statique] = BC;
                indice_tab_chainage_statique++;
            }
            else{
                indice_tab_chainage_statique = NIS;
            }

            /*----------------------------------------*
            | Mise à jour de la Base Courante
            *-----------------------------------------*/
            deplacement_BC = table_regions[num_region_appelante].taille;
            BC += deplacement_BC;

            /*----------------------------------------*
            | Si la BC est inférieure à l'indice de la BC dispo, on la met à jour
            *-----------------------------------------*/
            if (BC < indice_BC_dispo){
                BC = indice_BC_dispo;
            }
            indice_BC_dispo = BC + table_regions[num_region_actuelle].taille ;

            /*----------------------------------------*
            | Chainage dynamique
            *-----------------------------------------*/
            pile[BC].valeur.entier = BC_region_appelante;
            pile[BC].type = CELLULE_CHAIN_DYN; //y pour l'affichage du chainage en couleur

            /*----------------------------------------*
            | Chainage statique
            *-----------------------------------------*/
            for (int i=NIS-1; i>=0; i--){
                pile[BC + NIS - i].valeur.entier = tab_chainage_statique[i];
                pile[BC + NIS - i].type = CELLULE_CHAIN_STAT; //z pour l'affichage du chainage en couleur
            }

            /*----------------------------------------*
            | On vérifie si la procédure a des arguments et on affecte les valeurs des arguments aux variables correspondantes
            *-----------------------------------------*/
            if (a->fils != NULL){
                num_argument_courant = 1;
                num_description_tmp = table_declaration[a->num_declaration].description;
                num_region_appelante_liste_arguments = num_region_appelante;
                resultat = parcours_arbre(a->fils, num_region_actuelle);
            }

            /*----------------------------------------*
            | Appel récursif pour parcourir l'arbre de la région de la procédure appelée
            *-----------------------------------------*/
            resultat = parcours_arbre(table_regions[num_region_actuelle].arbre, num_region_actuelle);

            /*----------------------------------------*
            | On se replace au bon endroit dans la pile après l'appel d'une autre procédure
            *-----------------------------------------*/
            num_region_actuelle = num_region_appelante;
            BC = BC_region_appelante;

            /*----------------------------------------*
            | On récupère le chainage statique de la région appelante
            *-----------------------------------------*/
            for (int i=1; i<=table_regions[num_region_appelante].NIS; i++){
                tab_chainage_statique[i] = pile[BC + i].valeur.entier;
            }
            indice_tab_chainage_statique ++;

            break;

        /*----------------------------------------*
        |                                         |
        | ~~~ T_APPEL_FONCTION ~~~
        |                                         |
        *-----------------------------------------*/
        case T_APPEL_FCT :
            /*----------------------------------------*
            | Changement de numéro de région actuelle pour passer la région de la fonction appelé en paramètre (procédure appelante)
            *-----------------------------------------*/
            num_region_actuelle = table_declaration[a->num_declaration].execution;

            /*----------------------------------------*
            | Stockage de la BC de la région appelante pour le chainage dynamique
            *-----------------------------------------*/
            BC_region_appelante = BC;

            /*----------------------------------------*
            | Chainage statique
            *-----------------------------------------*/
            NIS = table_regions[num_region_actuelle].NIS;
            tab_chainage_statique = realloc(tab_chainage_statique, NIS*sizeof(int));
            if (NIS > table_regions[num_region_appelante].NIS  && indice_tab_chainage_statique < NIS){
                tab_chainage_statique[indice_tab_chainage_statique] = BC;
                indice_tab_chainage_statique++;
            }
            else{
                indice_tab_chainage_statique = NIS;
            }

            /*----------------------------------------*
            | Mise à jour de la Base Courante
            *-----------------------------------------*/
            deplacement_BC = table_regions[num_region_appelante].taille;
            BC += deplacement_BC;

            /*----------------------------------------*
            | Si la BC est inférieure à l'indice de la BC dispo, on la met à jour
            *-----------------------------------------*/
            if (BC < indice_BC_dispo){
                BC = indice_BC_dispo;
            }
            indice_BC_dispo = BC + table_regions[num_region_actuelle].taille ;

            /*----------------------------------------*
            | Chainage dynamique
            *-----------------------------------------*/
            pile[BC].valeur.entier = BC_region_appelante;
            pile[BC].type = CELLULE_CHAIN_DYN; //y pour l'affichage du chainage en couleur
            
            /*----------------------------------------*
            | Chainage statique
            *-----------------------------------------*/  
            for (int i=NIS-1; i>=0; i--){
                pile[BC + NIS - i].valeur.entier = tab_chainage_statique[i];
                pile[BC + NIS - i].type = CELLULE_CHAIN_STAT; //z pour l'affichage du chainage en couleur
            }      

            /*----------------------------------------*
            | On vérifie si la procédure a des arguments et on affecte les valeurs des arguments aux variables correspondantes
            *-----------------------------------------*/
            if (a->fils != NULL){
                num_argument_courant = 1;
                /*+1 car le premier champ pour une fonction dans la table des types est le type de retour de cette dernière*/
                num_description_tmp = table_declaration[a->num_declaration].description+1;
                num_region_appelante_liste_arguments = num_region_appelante;
                resultat  = parcours_arbre(a->fils, num_region_actuelle);
            }

            /*----------------------------------------*
            | Appel récursif pour parcourir l'arbre de la région de la fonction appelée
            *-----------------------------------------*/
            resultat = parcours_arbre(table_regions[num_region_actuelle].arbre, num_region_actuelle);
            
            /*----------------------------------------*
            | On se replace au bon endroit dans la pile après l'appel d'une autre fonction
            *-----------------------------------------*/
            num_region_actuelle = num_region_appelante;
            BC = BC_region_appelante;

            /*----------------------------------------*
            | On récupère le chainage statique de la région appelante
            *-----------------------------------------*/
            for (int i=1; i<=table_regions[num_region_appelante].NIS; i++){
                tab_chainage_statique[i] = pile[BC + i].valeur.entier;
            }
            indice_tab_chainage_statique ++;
            break;

        /*----------------------------------------*
        |                                         |
        | ~~~ T_LISTE_ARGUMENTS_ECRIRE ~~~
        |                                         |
        *-----------------------------------------*/
        case T_LISTE_ARGUMENTS_ECRIRE :
            /*----------------------------------------*
            | Remplit le tableau des arguments pour ecrire en parcourant la liste des arguments
            *-----------------------------------------*/
            resultat = parcours_arbre(a->fils, num_region_actuelle);
            deplacement = table_declaration[resultat.valeur.entier].execution;

            if (resultat.type == CELLULE_TYPE_S_T){
                /*----------------------------------------*
                | On parcourt la liste des champs
                *-----------------------------------------*/
                /*----------------------------------------*
                | Indice et variables pour récup le déplacement quand c'est une structure ou un tableau
                *-----------------------------------------*/
                init_var_deplacement_struct_tab(table_declaration[table_declaration[resultat.valeur.entier].description].description);
                /*----------------------------------------*/
                deplacement += parcours_arbre(a->fils->fils, num_region_actuelle).valeur.entier;
                decalage_NIS = table_regions[num_region_actuelle].NIS - table_regions[table_declaration[resultat.valeur.entier].region].NIS ;
                
                if (decalage_NIS == 0){
                    switch (pile[BC + deplacement].type){   
                        case CELLULE_ENTIER : 
                            tab_arguments_ecrire[indice_tab_arguments_ecrire].entier = pile[BC + deplacement].valeur.entier;                    
                            break;
                        case CELLULE_REEL :
                            tab_arguments_ecrire[indice_tab_arguments_ecrire].reel = pile[BC + deplacement].valeur.reel;
                            break;
                        case CELLULE_CHAR :
                            tab_arguments_ecrire[indice_tab_arguments_ecrire].caractere = pile[BC + deplacement].valeur.caractere;
                            break;
                        case CELLULE_BOOL : 
                            tab_arguments_ecrire[indice_tab_arguments_ecrire].entier = pile[BC + deplacement].valeur.entier;
                            break;
                        default :
                            break;
                    }
                }
                else{
                    switch (pile[pile[BC+decalage_NIS].valeur.entier+deplacement].type){
                        case CELLULE_ENTIER : 
                            tab_arguments_ecrire[indice_tab_arguments_ecrire].entier = pile[pile[BC+decalage_NIS].valeur.entier + deplacement].valeur.entier;                    
                            break;
                        case CELLULE_REEL :
                            tab_arguments_ecrire[indice_tab_arguments_ecrire].reel = pile[pile[BC+decalage_NIS].valeur.entier + deplacement].valeur.reel;
                            break;
                        case CELLULE_CHAR :
                            tab_arguments_ecrire[indice_tab_arguments_ecrire].caractere = pile[pile[BC+decalage_NIS].valeur.entier + deplacement].valeur.caractere;
                            break;
                        case CELLULE_BOOL :
                            tab_arguments_ecrire[indice_tab_arguments_ecrire].entier = pile[pile[BC+decalage_NIS].valeur.entier + deplacement].valeur.entier;
                            break;
                        default :
                            break;
                    }
                }
            }
            if (resultat.type == CELLULE_IDF){
                decalage_NIS = table_regions[num_region_actuelle].NIS - table_regions[table_declaration[resultat.valeur.entier].region].NIS ;
                if (decalage_NIS == 0){
                    if (table_declaration[resultat.valeur.entier].description == 0){
                        tab_arguments_ecrire[indice_tab_arguments_ecrire].entier = pile[BC + deplacement].valeur.entier;
                    }
                    if (table_declaration[resultat.valeur.entier].description == 1){
                        tab_arguments_ecrire[indice_tab_arguments_ecrire].reel = pile[BC + deplacement].valeur.reel;
                    }
                    if (table_declaration[resultat.valeur.entier].description == 2){
                        tab_arguments_ecrire[indice_tab_arguments_ecrire].entier = pile[BC + deplacement].valeur.entier;
                    }
                    if (table_declaration[resultat.valeur.entier].description == 3){
                        tab_arguments_ecrire[indice_tab_arguments_ecrire].caractere = pile[BC + deplacement].valeur.caractere;
                    }
                }
                else{
                    if (table_declaration[resultat.valeur.entier].description == 0){
                        tab_arguments_ecrire[indice_tab_arguments_ecrire].entier = pile[pile[BC+decalage_NIS].valeur.entier + deplacement].valeur.entier;
                    }
                    if (table_declaration[resultat.valeur.entier].description == 1){
                        tab_arguments_ecrire[indice_tab_arguments_ecrire].reel = pile[pile[BC+decalage_NIS].valeur.entier + deplacement].valeur.reel;
                    }
                    if (table_declaration[resultat.valeur.entier].description == 2){
                        tab_arguments_ecrire[indice_tab_arguments_ecrire].entier = pile[pile[BC+decalage_NIS].valeur.entier + deplacement].valeur.entier;
                    }
                    if (table_declaration[resultat.valeur.entier].description == 3){
                        tab_arguments_ecrire[indice_tab_arguments_ecrire].caractere = pile[pile[BC+decalage_NIS].valeur.entier + deplacement].valeur.caractere;
                    }
                }
            }
            if (resultat.type == CELLULE_ENTIER){
                tab_arguments_ecrire[indice_tab_arguments_ecrire].entier = resultat.valeur.entier;
            }
            if (resultat.type == CELLULE_REEL){
                tab_arguments_ecrire[indice_tab_arguments_ecrire].reel = resultat.valeur.reel;
            }
            if (resultat.type == CELLULE_BOOL){
                tab_arguments_ecrire[indice_tab_arguments_ecrire].entier = resultat.valeur.entier;
            }
            if (resultat.type == CELLULE_CHAR){
                tab_arguments_ecrire[indice_tab_arguments_ecrire].caractere = resultat.valeur.caractere;
            }
            if (a->fils->frere != NULL){
                indice_tab_arguments_ecrire ++;
                resultat = parcours_arbre(a->fils->frere, num_region_actuelle);
            }

            break;

        /*----------------------------------------*
        |                                         |
        | ~~~ T_ECRIRE ~~~
        |                                         |
        *-----------------------------------------*/
        case T_ECRIRE : 
            /*----------------------------------------*
            | Pour le stockage des arguments de ecrire
            *-----------------------------------------*/
            indice_tab_arguments_ecrire = 0; //pour stockage
            tab_arguments_ecrire = realloc(tab_arguments_ecrire, table[a->num_lexico].longueur*sizeof(int));
            memset(tab_arguments_ecrire, 0, table[a->num_lexico].longueur*sizeof(int));

            /*----------------------------------------*
            | Si ecrire a des arguments on va parcourir la liste de ses arguments
            *-----------------------------------------*/
            if (a->fils != NULL){
                resultat = parcours_arbre(a->fils, num_region_actuelle);
            }

            indice_tab_arguments_ecrire = 0; //pour affichage
            /*----------------------------------------*
            | Parcourt de la chaine de caractères et affichage au fur et mesure en utilisant le tableau des arguments si besoin
            *-----------------------------------------*/
            for (int i=1; i<table[a->num_lexico].longueur-1; i++){
                if (lexeme(a->num_lexico)[i] == '\\'){
                    if (lexeme(a->num_lexico)[i+1] == 'n'){
                        printf("\n");
                        i++;
                    }
                }
                else if (lexeme(a->num_lexico)[i] == '%'){
                    switch (lexeme(a->num_lexico)[i+1]){
                        case 'd':
                            printf("%d", tab_arguments_ecrire[indice_tab_arguments_ecrire].entier);
                            indice_tab_arguments_ecrire++;
                            i++;
                            break;
                        case 'f':
                            printf("%.4f", tab_arguments_ecrire[indice_tab_arguments_ecrire].reel);
                            indice_tab_arguments_ecrire++;
                            i++;
                            break;
                        case 'c':
                            printf("%c", tab_arguments_ecrire[indice_tab_arguments_ecrire].caractere);
                            indice_tab_arguments_ecrire++;
                            i++;
                            break;
                        case 'b':
                            if (tab_arguments_ecrire[indice_tab_arguments_ecrire].entier == 1){
                                printf("true");
                            }
                            else{
                                printf("false");
                            }
                            indice_tab_arguments_ecrire++;
                            i++;
                            break;
                        default : 
                            break;
                    }
                }
                else{
                    printf("%c", lexeme(a->num_lexico)[i]);
                }
            }
            break;
        /*----------------------------------------*
        |                                         |
        | ~~~ T_LISTE_ARGUMENTS_LIRE ~~~
        |                                         |
        *-----------------------------------------*/
        case T_LISTE_ARGUMENTS_LIRE :
            /*----------------------------------------*
            | Récupère le déplacement nécessaire pour accéder à la variable qu'on veut affecter
            *-----------------------------------------*/
            resultat = parcours_arbre(a->fils, num_region_actuelle);
            deplacement = table_declaration[resultat.valeur.entier].execution;
            
            /*----------------------------------------*
            | Pour stocker le type de la variable à lire
            *-----------------------------------------*/
            int type = table_declaration[resultat.valeur.entier].description;

            /*----------------------------------------*
            | Si c'est un TYPE_S OU TYPE_T On parcourt la liste des champs et des indices
            *-----------------------------------------*/
            if (resultat.type == CELLULE_TYPE_S_T){
                init_var_deplacement_struct_tab(table_declaration[table_declaration[resultat.valeur.entier].description].description);
                /*----------------------------------------*
                | On ajoute le déplacement pour accéder aux bons champs/indices
                *-----------------------------------------*/
                deplacement += parcours_arbre(a->fils->fils, num_region_actuelle).valeur.entier;
                type = a->fils->fils->num_declaration;
            }
            
            decalage_NIS = table_regions[num_region_actuelle].NIS - table_regions[table_declaration[resultat.valeur.entier].region].NIS;

            /*----------------------------------------*
            | Modifie la valeur de la pile à l'adresse de la variable
            *-----------------------------------------*/
            if (resultat.type == CELLULE_IDF || resultat.type == CELLULE_TYPE_S_T){
                if (decalage_NIS > 0){
                    if (type == 0){
                        printf("Entrez un entier : ");
                        fscanf(stdin, "%d", &pile[pile[BC+decalage_NIS].valeur.entier + deplacement].valeur.entier);
                        pile[pile[BC+decalage_NIS].valeur.entier].type = CELLULE_ENTIER;
                    }
                    if (type == 1){
                        printf("Entrez un réel : ");
                        fscanf(stdin, "%f", &pile[pile[BC+decalage_NIS].valeur.entier + deplacement].valeur.reel);
                        pile[pile[BC+decalage_NIS].valeur.entier].type = CELLULE_REEL;
                    }
                    if (type == 2){
                        printf("Entrez un booléen (1 pour TRUE 0 pour FALSE) : ");
                        fscanf(stdin, "%d", &pile[pile[BC+decalage_NIS].valeur.entier + deplacement].valeur.entier);
                        pile[pile[BC+decalage_NIS].valeur.entier].type = CELLULE_BOOL;
                    }
                    if (type == 3){
                        printf("Entrez un caractère : ");
                        pile[pile[BC+decalage_NIS].valeur.entier + deplacement].valeur.caractere = fgetc(stdin);
                        pile[pile[BC+decalage_NIS].valeur.entier].type = CELLULE_CHAR;
                    }
                }
                else{
                    if (type == 0){
                        printf("Entrez un entier : ");
                        fscanf(stdin, "%d", &pile[BC + deplacement].valeur.entier);
                        pile[BC + deplacement].type = CELLULE_ENTIER;
                    }
                    if (type == 1){
                        printf("Entrez un réel : ");
                        fscanf(stdin, "%f", &pile[BC + deplacement].valeur.reel);
                        pile[BC + deplacement].type = CELLULE_REEL;
                    }
                    if (type == 2){
                        printf("Entrez un booléen (1 pour TRUE 0 pour FALSE) : ");
                        fscanf(stdin, "%d", &pile[BC + deplacement].valeur.entier);
                        pile[BC + deplacement].type = CELLULE_BOOL;
                    }
                    if (type == 3){
                        printf("Entrez un caractère : ");
                        pile[BC + deplacement].valeur.caractere = fgetc(stdin);
                        pile[BC + deplacement].type = CELLULE_CHAR;
                    }
                }
            }

            /*----------------------------------------*
            | Nettoyage de stdin
            *-----------------------------------------*/
            viderBuffer();

            /*----------------------------------------*
            | Si il y a un frère, on continue le parcours de l'arbre 
            *-----------------------------------------*/
            if (a->fils->frere != NULL){
                resultat = parcours_arbre(a->fils->frere, num_region_actuelle);
            }

            return resultat;

            break;
            
        /*----------------------------------------*
        |                                         |
        | ~~~ T_LIRE ~~~
        |                                         |
        *-----------------------------------------*/
        case T_LIRE :
            resultat = parcours_arbre(a->fils, num_region_actuelle);
            break;

        /*----------------------------------------*
        |                                         |
        | ~~~ T_RANDINT ~~~
        |                                         |
        *-----------------------------------------*/
        case T_RANDINT : 
            /*----------------------------------------*
            | Randint possible qu'entre deux entiers donc a->fils et a->fils->frere deux constantes entières 
            *-----------------------------------------*/
            resultat_gauche = parcours_arbre(a->fils, num_region_actuelle);
            resultat_droite = parcours_arbre(a->fils->frere, num_region_actuelle);
            resultat.valeur.entier = rand()%(resultat_droite.valeur.entier - resultat_gauche.valeur.entier + 1) + resultat_gauche.valeur.entier;
            resultat.type = CELLULE_ENTIER;
            break;

        default : 
            break; 
    }

    /*----------------------------------------*
    | Si il y a un frère, on continue le parcours de l'arbre
    *-----------------------------------------*/
    if (a->frere != NULL){
        resultat = parcours_arbre(a->frere, num_region_actuelle);
    }

    return resultat;
}

