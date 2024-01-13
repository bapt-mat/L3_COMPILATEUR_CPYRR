/**
 * @file erreurs.c
 * @author Principal : GUNES Ozan - Secondaires : MATHEVON Baptiste, YILDIZ Tolga
 * @brief Fonctions de gestion des erreurs
 * @date 19-12-2023
*/

#include "erreurs.h"
#include "../TAD_table_declaration/table_declaration.h"
extern int code_erreur;
extern int numero_ligne;
extern tab_declaration table_declaration;

/** --------------------------------------*
* @author : MATHEVON Baptiste
* @brief : Affichage de l'erreur quand erreur d'une expression arithmétique
*-----------------------------------------*/
void erreur_exp_arith(int type1, int type_operation, int type2){
    switch (type_operation){
        case T_PLUS:
            printf("ERREUR [ligne %d]: expression arithmétique (opération entre deux types différents) : <%s> + <%s> \n", numero_ligne, lexeme(type1), lexeme(type2));
            break;
        case T_MOINS:
            printf("ERREUR [ligne %d]: expression arithmétique (opération entre deux types différents) : <%s> - <%s> \n", numero_ligne, lexeme(type1), lexeme(type2));
            break;
        case T_MULT:
            printf("ERREUR [ligne %d]: expression arithmétique (opération entre deux types différents) : <%s> * <%s> \n", numero_ligne, lexeme(type1), lexeme(type2));
            break;
        case T_DIV:
            printf("ERREUR [ligne %d]: expression arithmétique (opération entre deux types différents) : <%s> / <%s> \n", numero_ligne, lexeme(type1), lexeme(type2));
            break;
    }
    exit(0);
} 

/** --------------------------------------*
* @author : MATHEVON Baptiste
* @brief : Affichage de l'erreur quand erreur d'une affectation
* @param type1 : type de l'expression de gauche
* @param type2 : type de l'expression de droite
*-----------------------------------------*/
void erreur_affectation(int type1, int type2){
    printf("ERREUR [ligne %d]: affectation impossible : <%s> = <%s> \n", numero_ligne, lexeme(type1), lexeme(type2));
    exit(0);
}

/**
 * @brief Affichage de l'erreur de l'expression booléenne
 * @author Principal : GUNES Ozan 
 * @param type1 : Le type de l'expression de gauche
 * @param type2 : Le type de l'expression de droite
*/
void erreur_exp_booleenne(int type1, int type2){
    printf("ERREUR [ligne %d]: expression booléenne (comparaison entre deux types différents) : <%s> et <%s> \n", numero_ligne, lexeme(type1), lexeme(type2));
    exit(0);
}

/**
 * @brief Affichage de l'erreur des indices
 * @author Principal : GUNES Ozan 
 * @param type_indice : Le type basique de l'indice utilisé 
*/
void erreur_indice_tab(int type_indice){
    printf("ERREUR [ligne %d]: indice utilisé est de type <%s>,mais doit être un <int> \n", numero_ligne, lexeme(type_indice));
    exit(0);
}

/**
 * @brief Affichage de l'erreur du nombre des arguments 
 * @author Principal : GUNES Ozan 
 * @param nb_arguments_recu : Le nombre d'arguments recus
 * @param nb_arguments_attendu : Le nombre d'arguments attendus
*/
void erreur_declaration_champ_structure(int num_lex_champ){
    printf("ERREUR [ligne %d]: champ <%s> non déclaré \n", numero_ligne, lexeme(num_lex_champ));
    exit(0);
}

/**
 * @brief Affichage de l'erreur du nombre des arguments 
 * @author Principal : GUNES Ozan 
 * @param nb_arguments_recu : Le nombre d'arguments recus
 * @param nb_arguments_attendu : Le nombre d'arguments attendus
*/
void erreur_nb_arguments(int nb_arguements_recu, int nb_arguements_attendu){
    printf("ERREUR [ligne %d]: nombre argument(s) reçu(s): %d | nombre argument(s) attendu(s): %d\n", numero_ligne, nb_arguements_recu, nb_arguements_attendu);
    //exit(0);
}


/** --------------------------------------*
* @author : MATHEVON Baptiste
* @brief : Définition d'un code erreur quand erreur de syntaxe pour affichage au moment de l'appel de yyerror()
* @param code : macro pour le code de l'erreur
*-----------------------------------------*/
void erreur(int code){
    code_erreur=code;
}

/**
 * @brief Affichage du type basique 
 * @author Principal : GUNES Ozan 
 * @param type1: Le type basique utilisé
  * @return char * : int, float, bool ou char
*/
char * type_f (int type1){
    char * resultat;
    switch(type1){
        case 0:
            return resultat = "int";
            break;
        case 1:
            return resultat = "float";
            break;
        case 3:
            return resultat = "char";
            break; 
    }
    exit(0);
}

/**
 * @brief Verifie si l'indice utilisé est bien dans les dimenssion du tableau
 * @author Principal : GUNES Ozan - Secondaire :
 * @param type1: Type de l'expression 1 
 * @param type2 : Type de l'expression 2
 * @param appel ; nom de l'appel (fonction ou procédure)
*/
void erreur_type_argument(int type1, int type2, int appel){
    if(type1 == 0 || type1 == 1 || type1 == 2 || type1 == 3){
        printf("ERREUR [ligne %d]: %s non valide dans l'appel de [%s]: %s attendu \n\n",numero_ligne, type_f(type1),lexeme(appel),type_f(type2));
    }else if (type2 == 0 || type2 == 1 || type2 == 2 || type2 == 3){
                printf("ERREUR [ligne %d]: %s non valide : %s attendu \n\n",numero_ligne, lexeme(type1),type_f(type2));


    }
    else{
        printf("ERREUR [ligne %d]: argument %s (%s) non valide dans l'appel de [%s]: %s attendu \n", numero_ligne, lexeme(type1), type_f(table_declaration[type1].description), lexeme(appel), type_f(type2));

    }
    exit(0);
}

/**
 * @brief Verifie si le retour est celui d'une fonction
 * @author Principal : GUNES Ozan - Secondaire : YILDIZ Tolga
 * @param region :  region du retour 
 * @return int : 1 si est contenue dans une fonction, 0 sinon
*/
int recherche_indice_fct(int region){
    for (int i=0;i<5000;i++){
        if(table_declaration[i].execution == region && table_declaration[i].nature == FCT){
            //si le return est dans une fonction
            return i;
        }
    }
    // si le return n'est pas dans une fonction
    return -1;
}

/**
 * @brief Creer le noeud d'un argument d'une procédure ou d'une fonction
 * @author Principal : GUNES Ozan - Secondaire : YILDIZ Tolga
 * @param expression : noeud qui contient l'argument d'un tableau
 * @param numero_argument : le numéro de positionnement de l'argument
 * @param numero_declaration_appel : numero de déclaration de l'appel (fonction ou procédure)
 * @return arbre ; Le noeud indice avec son fils
*/
arbre creer_noeud_argument(arbre expression, int numero_argument, int numero_declaration_appel){
    arbre resultat;
    if(table_declaration[numero_declaration_appel].nature == FCT){
        if(expression->type == T_IDF){
            if(table_declaration[expression->num_declaration].description != table_types[(table_declaration[numero_declaration_appel].description)+(2*numero_argument+1)]){
                erreur_type_argument(table_declaration[expression->num_declaration].description, table_types[(table_declaration[numero_declaration_appel].description)+2*numero_argument+1], numero_declaration_appel);
            }
        }
        else if(expression->type == T_APPEL_FCT){
            if(table_types[table_declaration[expression->num_declaration].description] != table_types[(table_declaration[numero_declaration_appel].description)+(2*numero_argument+1)]){
                
                //erreur_type_argument(expression->num_declaration, table_types[(table_declaration[numero_declaration_appel].description)+(2*numero_argument+1)], numero_declaration_appel);
            }
        }
        else if(expression->type == T_CSTE_F){
                if(table_types[(table_declaration[numero_declaration_appel].description)+(2*numero_argument+1)] != expression->num_declaration){
                    erreur_type_argument(1, table_types[(table_declaration[numero_declaration_appel].description)+(2*numero_argument+1)],numero_declaration_appel);
                }
        }
        else if(expression->type == T_CSTE_E){
                if(table_types[(table_declaration[numero_declaration_appel].description)+(2*numero_argument+1)] != 0){
                    erreur_type_argument(0, table_types[(table_declaration[numero_declaration_appel].description)+(2*numero_argument+1)],numero_declaration_appel);
                }
        }
        else if(expression->type == T_CSTE_CHAR){
                if(table_types[(table_declaration[numero_declaration_appel].description)+(2*numero_argument+1)] != 3){
                    erreur_type_argument(3, table_types[(table_declaration[numero_declaration_appel].description)+(2*numero_argument+1)],numero_declaration_appel);
                }
        }
        else if(expression->type == T_CSTE_BOOL){
                if(table_types[(table_declaration[numero_declaration_appel].description)+(2*numero_argument+1)] != 2){
                    erreur_type_argument(2, table_types[(table_declaration[numero_declaration_appel].description)+(2*numero_argument+1)],numero_declaration_appel);
                }
        } 
    }
    else{    
        if(expression->type == T_IDF){
            if(table_declaration[expression->num_declaration].description != table_types[(table_declaration[numero_declaration_appel].description)+2*numero_argument]){
                erreur_type_argument(expression->num_declaration, table_types[(table_declaration[numero_declaration_appel].description)+2*numero_argument], numero_declaration_appel);
                exit(0);
            }
        }
        else if(expression->type == T_APPEL_FCT){
            if(table_types[table_declaration[expression->num_declaration].description] != table_types[(table_declaration[numero_declaration_appel].description)+2*numero_argument]){
                erreur_type_argument(expression->num_declaration, table_types[(table_declaration[numero_declaration_appel].description)+2*numero_argument], numero_declaration_appel);
            }
        }
        else if(expression->type == T_CSTE_F){
                if(table_types[(table_declaration[numero_declaration_appel].description)+2*numero_argument] != 1){
                    erreur_type_argument(1, table_types[(table_declaration[numero_declaration_appel].description)+2*numero_argument],numero_declaration_appel);
                }
        }
        else if(expression->type == T_CSTE_E){
                if(table_types[(table_declaration[numero_declaration_appel].description)+2*numero_argument] != 0){
                    erreur_type_argument(0, table_types[(table_declaration[numero_declaration_appel].description)+2*numero_argument],numero_declaration_appel);
                }
        }
        else if(expression->type == T_CSTE_CHAR){
                if(table_types[(table_declaration[numero_declaration_appel].description)+2*numero_argument] != 3){
                    erreur_type_argument(3, table_types[(table_declaration[numero_declaration_appel].description)+2*numero_argument],numero_declaration_appel);
                }
        }
        else if(expression->type == T_CSTE_BOOL){
                if(table_types[(table_declaration[numero_declaration_appel].description)+2*numero_argument] != 2){
                    erreur_type_argument(2, table_types[(table_declaration[numero_declaration_appel].description)+2*numero_argument],numero_declaration_appel);
                }
        }      
    }
    resultat=creer_noeud(T_LISTE_ARGUMENTS, -1, -1); ajouter_fils(resultat, expression);
    return resultat;
}

/**
 * @brief Creer le noeud "RETOURNE" d'une fonction
 * @author Principal : GUNES Ozan - Secondaire : YILDIZ Tolga
 * @param retour : noeud qui contient le retour de la fonction
 * @return arbre ; Le noeud "RETOURNE" avec son fils
*/
arbre creer_noeud_retour(arbre retour){
    arbre resultat;
    // on récupère la region de ce que le return renvoie
    int i = table_declaration[retour->num_declaration].region;
    int indice = recherche_indice_fct(i);
    // si le return est est dans une fonction, on verifie le type de la fonction et du return
    if(indice != -1){
        if(table_declaration[retour->num_declaration].description != table_types[table_declaration[indice].description]){
            printf("ERREUR [ligne %d]: retour fonction (%s) : %s mais un %s renvoyé \n", numero_ligne, lexeme(indice), type_f(table_declaration[retour->num_declaration].description) , type_f(table_types[table_declaration[indice].description]));
            exit(0);
        }
    }
    
    resultat = creer_noeud(T_RETOURNE, -1, -1);
    ajouter_fils(resultat, retour);
    return resultat;
    
}

/**
 * @brief Creer le noeud d'un indice d'un tableau
 * @author Principal : GUNES Ozan - Secondaire : YILDIZ Tolga
 * @param a : noeud qui contient l'indice du tableau
 * @param numero_declaration_tableau : numero de déclaration du tableau
 * @return arbre ; Le noeud indice avec son fils
*/
arbre creer_noeud_indice(arbre expression,int numero_declaration_tableau){
    arbre resultat;
    int description;
    if (expression->type == T_IDF){
        if(table_declaration[expression->num_declaration].description != 0){
            erreur_indice_tab(table_declaration[expression->num_declaration].description);
        }
        else{
            resultat=creer_noeud(T_LISTE_INDICES, -1, expression->num_declaration); ajouter_fils(resultat, expression);
        }
    }else if(expression->type == T_APPEL_FCT){
        if(table_types[table_declaration[expression->num_declaration].description] != 0){
            erreur_indice_tab(expression->num_declaration);
        }
        else{
            resultat=creer_noeud(T_LISTE_INDICES, -1, 0); ajouter_fils(resultat, expression);
        }
    }else if(expression->num_declaration != 0){
        erreur_indice_tab(expression->num_declaration);
    }
    else if(expression->type == T_CSTE_F){
        erreur_indice_tab(expression->num_declaration);
    }else{  
        resultat=creer_noeud(T_LISTE_INDICES, -1, expression->num_declaration); ajouter_fils(resultat, expression);
    }
    return resultat;
}


/**
 * @brief Creer le noeud des expressions arithmétiques avec les cas d'erreurs
 * @author Principal : MATHEVON Baptiste - Secondaire : YILDIZ Tolga, GUNES Ozan
 * @param expression_gauche : noeud qui contient l'expression de gauche de l'expression arithmétique
 * @param expression_droite : noeud qui contient l'expression de droite de l'expression arithmétique
 * @param type_operation : Le type de l'opération à faire 
 * @return arbre ; Le noeud de l'expression avec son fils et frere
*/
arbre creer_noeud_expression_arithmetique(arbre expression_gauche, arbre expression_droite, int type_operation){
    arbre resultat;
    int type_gauche, type_droite;
    /*----------------------------------------*
    | Si les deux expressions sont des variables on vérifie que leurs types soient les mêmes sinon erreur
    *-----------------------------------------*/
    if (expression_gauche->type == T_IDF && expression_droite->type == T_IDF){
        type_gauche = table_declaration[expression_gauche->num_declaration].description;
        type_droite = table_declaration[expression_droite->num_declaration].description;
        /*----------------------------------------*
        | Si l'idf de gauche est en fait une structure ou un tableau on récupère son type (stocké dans num_declaration de la liste_champs ou liste_indices)
        *-----------------------------------------*/
        if (expression_gauche->fils != NULL){
            if (expression_gauche->fils->type == T_LISTE_CHAMPS || expression_gauche->fils->type == T_LISTE_INDICES){
                type_gauche = expression_gauche->fils->num_declaration;
            }
        }
        /*----------------------------------------*
        | Idem pour l'idf de droite
        *-----------------------------------------*/
        if (expression_droite->fils != NULL){
            if (expression_droite->fils->type == T_LISTE_CHAMPS || expression_droite->fils->type == T_LISTE_INDICES){
                type_droite = expression_droite->fils->num_declaration;
            }
        }
        if (type_gauche != type_droite){
            erreur_exp_arith(table_declaration[expression_gauche->num_declaration].description, type_operation, table_declaration[expression_droite->num_declaration].description);
        }
        else{
            resultat=creer_noeud(type_operation, -1, type_gauche); ajouter_frere(expression_gauche, expression_droite); ajouter_fils(resultat, expression_gauche);
        }
    }
    /*----------------------------------------*
    | Si la premiere expression est une variable on vérifie que son type soit du même type que la deuxieme expression sinon erreur
    *-----------------------------------------*/
    else if (expression_gauche->type == T_IDF){
        type_gauche = table_declaration[expression_gauche->num_declaration].description;
        /*----------------------------------------*
        | Si l'idf de gauche est en fait une structure ou un tableau on récupère son type (stocké dans num_declaration de la liste_champs ou liste_indices)
        *-----------------------------------------*/
        if (expression_gauche->fils != NULL){
            if (expression_gauche->fils->type == T_LISTE_CHAMPS || expression_gauche->fils->type == T_LISTE_INDICES){
                type_gauche = expression_gauche->fils->num_declaration;
            }
        }
        if (expression_droite->type == T_APPEL_FCT){
            if (type_gauche != table_types[table_declaration[expression_droite->num_declaration].description]){
                erreur_exp_arith(type_gauche, type_operation, table_types[table_declaration[expression_droite->num_declaration].description]);
            }
            else{
                resultat=creer_noeud(type_operation, -1, type_gauche); ajouter_frere(expression_gauche, expression_droite); ajouter_fils(resultat, expression_gauche);
            }
        }
        else if (type_gauche != expression_droite->num_declaration){
            erreur_exp_arith(type_gauche, type_operation, expression_droite->num_declaration);
        }
        else{
            resultat=creer_noeud(type_operation, -1, type_gauche); ajouter_frere(expression_gauche, expression_droite); ajouter_fils(resultat, expression_gauche);
        }
    }
    /*----------------------------------------*
    | Idem si c'est la deuxieme expression qui est une variable
    *-----------------------------------------*/
    else if (expression_droite->type == T_IDF){
        type_droite = table_declaration[expression_droite->num_declaration].description;
        /*----------------------------------------*
        | Si l'idf de droite est en fait une structure ou un tableau on récupère son type
        *-----------------------------------------*/
        if (expression_droite->fils != NULL){
            if (expression_droite->fils->type == T_LISTE_CHAMPS || expression_droite->fils->type == T_LISTE_INDICES){
                type_droite = expression_droite->fils->num_declaration;
            }
        }
        if (expression_gauche->type == T_APPEL_FCT){
            if (type_droite != table_types[table_declaration[expression_gauche->num_declaration].description]){
                erreur_exp_arith(table_types[table_declaration[expression_gauche->num_declaration].description], type_operation, type_droite);
            }
            else{
                resultat=creer_noeud(type_operation, -1, table_types[table_declaration[expression_gauche->num_declaration].description]); ajouter_frere(expression_gauche, expression_droite); ajouter_fils(resultat, expression_gauche);
            }
        }
        else if (type_droite != expression_gauche->num_declaration){
            erreur_exp_arith(expression_gauche->num_declaration, type_operation, type_droite);
        }
        else{
            resultat=creer_noeud(type_operation, -1, type_droite); ajouter_frere(expression_gauche, expression_droite); ajouter_fils(resultat, expression_gauche);
        }
    }
    /*----------------------------------------*
    | Si les deux expressions sont des appels a des fonctions on vérifie que leurs type de retour soit les mêmes sinon erreur
    *-----------------------------------------*/
    else if (expression_gauche->type == T_APPEL_FCT && expression_droite->type == T_APPEL_FCT){
        if (table_types[table_declaration[expression_gauche->num_declaration].description] != table_types[table_declaration[expression_droite->num_declaration].description]){
            erreur_exp_arith(table_types[table_declaration[expression_gauche->num_declaration].description], type_operation, table_types[table_declaration[expression_droite->num_declaration].description]);
        }
        else{
            resultat=creer_noeud(type_operation, -1, table_types[table_declaration[expression_gauche->num_declaration].description]); ajouter_frere(expression_gauche, expression_droite); ajouter_fils(resultat, expression_gauche);
        }
    }
    /*----------------------------------------*
    | Si la premiere expression est un appel de fonction on vérifie que son type de retour soit du même type que la deuxieme expression sinon erreur
    *-----------------------------------------*/
    else if (expression_gauche->type == T_APPEL_FCT){
        if (expression_droite->num_declaration != table_types[table_declaration[expression_gauche->num_declaration].description]){
            erreur_exp_arith(table_types[table_declaration[expression_gauche->num_declaration].description], type_operation, expression_droite->num_declaration);
        }
        else{
            resultat=creer_noeud(type_operation, -1, table_types[table_declaration[expression_gauche->num_declaration].description]); ajouter_frere(expression_gauche, expression_droite); ajouter_fils(resultat, expression_gauche);
        }
    }
    /*----------------------------------------*
    | Idem si c'est la deuxieme expression qui est un appel de fonction
    *-----------------------------------------*/
    else if (expression_droite->type == T_APPEL_FCT){
        if (expression_gauche->num_declaration != table_types[table_declaration[expression_droite->num_declaration].description]){
            erreur_exp_arith(expression_gauche->num_declaration, type_operation, table_types[table_declaration[expression_droite->num_declaration].description]);
        }
        else{
            resultat=creer_noeud(type_operation, -1, table_types[table_declaration[expression_droite->num_declaration].description]); ajouter_frere(expression_gauche, expression_droite); ajouter_fils(resultat, expression_gauche);
        }
    }
    /*----------------------------------------*
    | Sinon on vérifie que les deux expressions ont bien le même type sinon erreur
    *-----------------------------------------*/
    else{
        if (expression_gauche->num_declaration != expression_droite->num_declaration){
            erreur_exp_arith(expression_gauche->num_declaration, type_operation, expression_droite->num_declaration);
        }
        else{
            resultat=creer_noeud(type_operation, -1, expression_droite->num_declaration); ajouter_frere(expression_gauche, expression_droite); ajouter_fils(resultat, expression_gauche);   
        }
    }
    return resultat;
}


/**
 * @brief Creer le noeud des expressions booléennes avec les cas d'erreurs
 * @author Principal : GUNES Ozan - Secondaire : YILDIZ Tolga
 * @param expression_gauche : noeud qui contient l'expression de gauche de l'expression booléenne
 * @param expression_droite : noeud qui contient l'expression de droite de l'expression booléenne
 * @param type_comparaison : Le noeud du type de comparaison à faire 
 * @return arbre ; Le noeud de l'expression avec son fils et frère
*/
arbre creer_noeud_expression_booleenne_compare(arbre expression_gauche, arbre expression_droite, arbre type_comparaison){
    arbre resultat;
    
    if (expression_gauche->type == T_IDF && expression_droite->type == T_IDF){
       if (expression_droite->fils != NULL && expression_gauche->fils != NULL) {
        if(expression_droite->fils->type == T_LISTE_INDICES && expression_gauche->fils->type == T_LISTE_INDICES ){
            int j = table_declaration[expression_droite->num_declaration].description;
            int i = table_declaration[expression_gauche->num_declaration].description;
            if(table_types[table_declaration[i].description] != table_types[table_declaration[j].description]){
                erreur_exp_booleenne(table_types[table_declaration[i].description],table_types[table_declaration[j].description]);
            }
        }
       }else
    
        if (expression_droite->fils != NULL){
        if(expression_droite->fils->type == T_LISTE_INDICES ){
            int i = table_declaration[expression_droite->num_declaration].description;
            if(table_types[table_declaration[i].description]!= table_declaration[expression_gauche->num_declaration].description)
                erreur_exp_booleenne(table_declaration[expression_gauche->num_declaration].description, table_types [table_declaration[i].description] );
              
            }
    }else
    if (expression_gauche->fils != NULL){
        if(expression_gauche->fils->type == T_LISTE_INDICES ){
            int i = table_declaration[expression_gauche->num_declaration].description;
            if(table_types[table_declaration[i].description]!= table_declaration[expression_droite->num_declaration].description)
                erreur_exp_booleenne(table_declaration[i].description, table_declaration[expression_droite->num_declaration].description  );
               
            }
    }else
        
        if (table_declaration[expression_gauche->num_declaration].description != table_declaration[expression_droite->num_declaration].description){
            
            erreur_exp_booleenne(table_declaration[expression_gauche->num_declaration].description, table_declaration[expression_droite->num_declaration].description);
        }
    }
    else if(expression_gauche->type == T_IDF){
            if(expression_droite->type == T_APPEL_FCT){
           
    if (expression_gauche->fils != NULL){
        if(expression_gauche->fils->type == T_LISTE_INDICES ){
            int i = table_declaration[expression_gauche->num_declaration].description;
            if(table_types[table_declaration[i].description]!= table_types[table_declaration[expression_droite->num_declaration].description])
                erreur_exp_booleenne(table_types[table_declaration[i].description], table_types[table_declaration[expression_droite->num_declaration].description] );
                
            }
    }else
                if(table_declaration[expression_gauche->num_declaration].description != table_types[table_declaration[expression_droite->num_declaration].description]){
                    
                    erreur_exp_booleenne(table_declaration[expression_gauche->num_declaration].description, table_types[table_declaration[expression_droite->num_declaration].description]);
                }
            }
        }else if(expression_droite->type == T_IDF){
                if(expression_gauche->type == T_APPEL_FCT){
                     if (expression_droite->fils != NULL){
        if(expression_droite->fils->type == T_LISTE_INDICES ){
            int i = table_declaration[expression_droite->num_declaration].description;
             if(table_types[table_declaration[i].description]!= table_types[table_declaration[expression_gauche->num_declaration].description]){
                erreur_exp_booleenne(table_types[table_declaration[expression_gauche->num_declaration].description], table_types[table_declaration[i].description] );
             }
            }
    }else
                    if(table_declaration[expression_droite->num_declaration].description != table_types[table_declaration[expression_gauche->num_declaration].description]){
                        
                        erreur_exp_booleenne(table_types[table_declaration[expression_gauche->num_declaration].description], table_declaration[expression_droite->num_declaration].description);
                    }
                }
            }
         else if (expression_droite->type == T_IDF){
                if (table_declaration[expression_gauche->num_declaration].description != expression_droite->num_declaration){
                   
                    erreur_exp_booleenne(table_declaration[expression_droite->num_declaration].description, expression_gauche->num_declaration);
                }
            }
        else if (expression_gauche->type == T_IDF){
                if (expression_gauche->num_declaration != table_declaration[expression_droite->num_declaration].description){
                    
                    erreur_exp_booleenne(expression_gauche->num_declaration, table_declaration[expression_droite->num_declaration].description);
                }
            }
        else if(expression_gauche->type == T_APPEL_FCT && expression_droite->type == T_APPEL_FCT){
                if (table_types[table_declaration[expression_gauche->num_declaration].description] != table_types[table_declaration[expression_droite->num_declaration].description]){
                    
                    erreur_exp_booleenne(table_types[table_declaration[expression_gauche->num_declaration].description], table_types[table_declaration[expression_droite->num_declaration].description]);
                }
            }
        else if (expression_droite->type == T_APPEL_FCT){
                if (expression_gauche->num_declaration != table_types[table_declaration[expression_droite->num_declaration].description]){
                    
                    erreur_exp_booleenne(expression_gauche->num_declaration,table_types[table_declaration[expression_droite->num_declaration].description]);         
                }
            }  
        else if (expression_gauche->type == T_APPEL_FCT){
                if (expression_droite->num_declaration != table_types[table_declaration[expression_gauche->num_declaration].description]){
                
                    erreur_exp_booleenne( table_types[table_declaration[expression_gauche->num_declaration].description], expression_droite->num_declaration );         
                }
             }
        else if(expression_gauche->num_declaration != expression_droite->num_declaration){
               
               erreur_exp_booleenne(expression_gauche->num_declaration, expression_droite->num_declaration);
            }
    resultat=type_comparaison; ajouter_frere(expression_gauche,expression_droite), ajouter_fils(resultat,expression_gauche);
                
    return resultat;
}



/** --------------------------------------*
* @author : MATHEVON Baptiste
* @brief : Vérification de la déclaration d'un champ dans une structure (et ses sous-structures -> récursif)
*-----------------------------------------*/
int verif_declaration_champ(int num_decl_struct, int num_lex_champ){
    int indice_table_types = 1;
    int nb_champs = table_types[num_decl_struct];
    int retour = -1;
    
    for (int i=0; i<nb_champs; i++){
        if (table_types[num_decl_struct + indice_table_types] == num_lex_champ){
            return table_types[num_decl_struct + indice_table_types + 1];
        }
        if (table_types[num_decl_struct + indice_table_types + 1] > 3){
            retour = verif_declaration_champ(table_declaration[table_types[num_decl_struct + indice_table_types + 1]].description, num_lex_champ);
            if (retour != -1){
                return retour;
            }
        }
        indice_table_types += 3;
    }
    return retour;
}




